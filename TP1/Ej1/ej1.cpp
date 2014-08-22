#include "ej1.h"

using namespace std;

int main(){
	int cantTablones;
	int saltoMaximo;
	int tablonI;
	int endEntry;

	while(true){

		//Si termina de leer el archivo, fin.
		if(cin.eof()){
			break;
		}

		//1er y 2do params cantidad de tablas del puente y salto maximo.
		cin >> cantTablones;
		cin >> saltoMaximo;

		cout << "cantidad de tablas: " << cantTablones << endl;
		cout << "salto maximo: " << saltoMaximo << endl;

		LTablonesEstado* tablones = new LTablonesEstado();
		LSaltos res = LSaltos();

		//Armo la lista de estado de Tablas del puente
		for(int i=0; i<cantTablones;i++){
			cin >> tablonI;

			tablones->push_back(tablonI);
		}
		cin >> endEntry;

		res = resolver(cantTablones, saltoMaximo, *tablones);
	


	}
}
