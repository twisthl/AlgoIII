#include "ej3.h"

using namespace std;

int main(){
	int cantCompus;	
	int cantEnlaces;

	int compu1;
	int compu2;
	int costoEnlace;

	int endEntry;

	while(true){

		//Si termina de leer el archivo, fin.
		if(cin.eof()){
			break;
		}

		//1er y 2do params cantidad de tablas del puente y salto maximo.
		cin >> cantCompus;
		cin >> cantEnlaces;

		cout << "cantidad de computadoras en red: " << cantCompus << endl;
		cout << "cantidad de enlaces: " << cantEnlaces << endl;

		list<Enlace> listaEnlaces = list<Enlace>();
		
		//Creo mi estructura de vuelos

		//Armo la lista de estado de Tablas del puente
		for(int i=0; i<cantEnlaces;i++){
			Enlace enlace = Enlace();

			cin >> enlace.compu1;
			cin >> enlace.compu2;
			cin >> enlace.costo;

			listaEnlaces->push_back(enlace);
			cout << "Enlace desde: " << enlace.compu1 << "; hasta: " << enlace.compu2 << "; con costo: " << enlace.costo << endl;
		}

		//agrego un uno al final para simular haber terminado el puente, este lugar es siempre valido.
		tablones->push_back(1);
		cin >> endEntry;


		res = resolver();

// 		cout << "termino algoritmo, imprimo resultados" << endl;

		imprimirResultado(res);

// 		cout << "termino de imprimir resultado" << endl;

		delete(tablones);
	}
}
