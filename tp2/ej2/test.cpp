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
	

	int n = 70;
	int k = 100;
	
	if(seed>0){
		ofstream fileTiempos("tiemposN70.out");

		// Tests aleatorios	
		for(int i=1;i< k;i++){				
			srand(seed + i);

			clock_t t = clock();

			Caballos caballos;
			for(int j=0; j<i; j++){
				int x = (rand() % n) + 1;
				int y = (rand() % n) + 1;
				Casillero casilla(x,y);
				caballos.push_back(casilla);
			}

			MatrizDeNodos* matriz = modelar(n);

			Nodo solucion = resolver(*matriz, n, caballos, i);
		
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
