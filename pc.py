import RPi.GPIO as GPIO
import time


s2 = 26
s3 = 27
signal = 25
NUM_CYCLES = 10


def setup():
  GPIO.setwarnings(False)
  GPIO.setmode(GPIO.BCM)
  GPIO.setup(signal,GPIO.IN, pull_up_down=GPIO.PUD_UP)
  GPIO.setup(s2,GPIO.OUT)
  GPIO.setup(s3,GPIO.OUT)
  print("\n")
  GPIO.setup(12,GPIO.OUT)
  GPIO.setup(13,GPIO.OUT)
  GPIO.output(12,GPIO.LOW) #S0
  GPIO.output(13,GPIO.HIGH) #S1



def loop():
    temp = 1
    GPIO.output(s2,GPIO.LOW)
    GPIO.output(s3,GPIO.LOW)
    start = time.time()
    for impulse_count in range(NUM_CYCLES):
      GPIO.wait_for_edge(signal, GPIO.FALLING)
    duration = time.time() - start      #seconds to run for loop
    red  = NUM_CYCLES*2.7 / duration   #in Hz
    print("red value - ",red)

    GPIO.output(s2,GPIO.LOW)
    GPIO.output(s3,GPIO.HIGH)
    start = time.time()
    for impulse_count in range(NUM_CYCLES):
      GPIO.wait_for_edge(signal, GPIO.FALLING)
    duration = time.time() - start
    blue = NUM_CYCLES*1.4 / duration
    print("blue value - ",blue)

    GPIO.output(s2,GPIO.HIGH)
    GPIO.output(s3,GPIO.HIGH)
    start = time.time()
    for impulse_count in range(NUM_CYCLES):
      GPIO.wait_for_edge(signal, GPIO.FALLING)
    duration = time.time() - start
    green = NUM_CYCLES*1.5 / duration
    print("green value - ",green)
    if ((blue<1000 and red<1000 and green<1000)or(abs(red-green)<250 and abs(green-blue)<250)):
        #print("vide")
        resultat = "v"
    elif(red>blue and red>green):
        #print("red")
        resultat = "r"
    elif(green>blue and green>red):
        #print("green")
        resultat = "g"
    elif (blue>red and green):
        #print("blue")
        resultat = "b"
    else:
        print("unsure")
        resultat = "u"
    fichier = open("bus.txt","w")
    fichier.write(resultat)
    fichier.close()
       
def endprogram():
    GPIO.cleanup()

if __name__=='__main__':
    
    setup()
    loop()
