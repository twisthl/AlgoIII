#include "ej2.h"
#include <time.h>
#include <cmath>
#include <fstream>

using namespace std;

/**
 * La función main toma el listado de trabajos por std input:
 */

int main(int argc, char *argv[]){
	int seed = (int) *argv[1]; // Semilla para los rand()
	

	int n = 100;
	int k = 50;
	
	if(seed>0){
		ofstream fileTiempos("tiemposK50.out");

		// Tests aleatorios	
		for(int i=2;i< n;i++){				
			srand(seed + i);

			clock_t t = clock();

			Caballos caballos;
			for(int j=0; j<k; j++){
				int x = (rand() % i) + 1;
				int y = (rand() % i) + 1;
				Casillero casilla(x,y);
				caballos.push_back(casilla);
			}

			MatrizDeNodos* matriz = modelar(i);

			Nodo solucion = resolver(*matriz, i, caballos, k);
		
			if(solucion.movimientosNecesarios != -1){
				cout << solucion.x + 1 << " " << solucion.y + 1 << " " << solucion.movimientosNecesarios << endl;
			} else {
				cout << "no" << endl;
			}
		
			t = clock() - t;

			fileTiempos << i << "\t" << t << endl;

			cout << i << "\t" << t << endl;
		}
	
	return 0;
	}
}
