#include "ej2.h"

using namespace std;

//int ejercicio2(){
int main(){
	//cout << "Comenzando el algoritmo..." << endl << endl;
	int cantEdificios = 0;
	int cantCiudades = 0;
	Edificio* edificio;
	Edificios* edificios;
	Ciudad* ciudad;

	int salida;
	while(true){
		//Si termina de leer el archivo, fin.
		if(cin.eof()){
			break;
		}
		//1er parametro cantidad de edificios que tiene la ciudad.
		cin >> cantEdificios;
		if (cantEdificios == 0) {
			break;
		}
		//cout << "Cantidad de edificios: " << cantEdificios << endl;
		edificios = new Edificios();
		//Armo el Vector<Edificio> (edificios) parseando la entrada.
		for(int i=0; i<cantEdificios;i++){
			int comienzo,fin,altura;
			cin >> comienzo;
			cin >> altura;
			cin >> fin;

			edificio = new Edificio(comienzo,fin,altura);
			edificios->push_back(*edificio);
			//cout << "Edificio " << i + 1 << ":" << endl <<" Comienza en " << comienzo <<	", su altura es de " << altura << " y termina en " << fin << endl;
		}
		//cout << endl;
		ciudad = edificar(cantEdificios, *edificios);
		cantCiudades++;
		//cout << "Ciudad Numero " << cantCiudades << endl;
		salida = imprimirCiudad(*ciudad);
	}
	return salida;
}
