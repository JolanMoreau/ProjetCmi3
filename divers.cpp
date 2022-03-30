#include "divers.h"

/// Convertit les entiers saisis en char
std::string int_str(int a){
	std::string R = "";
	do{
		R = char(48 + (a%10))+R;
		a = div_euclid(a,10);
	} while (a != 0);
	return R;
}
#include <unistd.h>
/// Division euclidienne
int div_euclid(int a, int d){
	return ((a-(a%d))/d);
}

/// Écrit la commande 'cmd' dans le fichier "ttyUSB0" afin de l'exécuter
int exec_cmd(std::string cmd){
    std::ofstream flux("/dev/ttyUSB0\0"); // '\0' = fin du string. Précisé car ofstream doit savoir où s'arrêter
    if (!flux)
        return -1; // Si ttyUSB0 n'est pas trouvé, arrête la fonction
    flux << cmd << std::endl;
    return 0;
}
int go_home(){
	if (exec_cmd("#0P1500#1P1500#2P1500#3P1500T3000\r") == -1) {
			std::cout << "ttyUSB0 introuvable";
			return -1;
		}
	return 0;
	}
	
int balayage (){
	std::string code="#0P500#1P1550#2P2000#3P1100T3000\r";
	if (exec_cmd(code) == -1) {
		std::cout << "ttyUSB0 introuvable";
		return -1;
	}	
	int x=141006548;
	int P1=1550;
	int P2=2000;
	while(x!=0)
		x--;
	int P0=500;
	for(int i=0;i<2500;i+=20){
		P0+=20;
		code="#0P"+int_str(P0)+"T1000";
		if (exec_cmd(code) == -1) {
			std::cout << "ttyUSB0 introuvable";
			return -1;
		}
		lire_bus(P0,P1,P2);
	}
	code="#0P2500#1P1100#2P1500#3P1100T500\r";
	P1=1100;
	P2=1500;
	if (exec_cmd(code) == -1) {
		std::cout << "ttyUSB0 introuvable";
		return -1;
	}	

	for(int i=0;i<2500;i+=20){
		P0+=20;
		code="#0P"+int_str(P0)+"T1000";
		if (exec_cmd(code) == -1) {
			std::cout << "ttyUSB0 introuvable";
			return -1;
		}
		lire_bus(P0,P1,P2);
	}
	return 0;
}



void lire_bus(int p0,int p1, int p2) {
	std::ifstream bus;
	system("python3 pc.py");
	do{
		bus.open("bus.txt",std::ios::in);
	}
	while (!bus);
	char ch;
	bus >> ch;
	if (ch == 'r')
		std::cout << "r\n";
		/*exec_cmd("#0P"+int_str(p0+50)+"#1"+int_str(p1+50)+"#2"+int_str(p2+50)+"\r");*/
		/*exec_cmd("#OP500#1P1500#2P2000");*/
	if (ch == 'g')
		std::cout << "g\n";
		/*exec_cmd("#0P"+int_str(p0+50)+"#1"+int_str(p1+50)+"#2"+int_str(p2+50)+"\r");
		exec_cmd("#OP500#1P1200#2P1700");*/
	if (ch == 'b')
		std::cout << "b\n";
		/*exec_cmd("#0P"+int_str(p0+50)+"#1"+int_str(p1+50)+"#2"+int_str(p2+50)+"\r");
		exec_cmd("#OP500#1P1200#2P1300");*/
	bus.close();
}
