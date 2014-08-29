#include "ej1.h"
#include <time.h>
#include <cmath>
#include <fstream>

using namespace std;

/**
 * La función main toma el listado de trabajos por std input:
 */
int main(int argc, char *argv[])
{
	int seed = (int) *argv[1]; // Semilla para los rand()
	int cantTablones;
	int saltoMaximo;
	int tablonEstado;
	LTablonesEstado* tablonesEstado;
	
	if(seed>0){
				
		srand(seed);

		ofstream fileTiempos("tiempos.out");
		
		// Tests aleatorios	
		for(int i=0;i<100;i++){
			cantTablones = rand() % 100000000;
			saltoMaximo = rand() % 100000;
			tablonesEstado = new LTablonesEstado();
			saltoMaximo = rand() % 1000000 + 1;

			for(int k=0;k<cantTablones;k++){
				tablonEstado = rand() % 2;
				tablonesEstado->push_back(tablonEstado);
			}

			LSaltos res;

			clock_t t = clock();
			res = resolver(cantTablones, saltoMaximo, *tablonesEstado);
			t = clock() - t;

			fileTiempos << cantTablones << "\t" << t << endl;
			imprimirResultadoAFile(res, "resultados");
			cout << cantTablones << "\t" << t << endl;
			
			delete tablonesEstado;	
		}

		fileTiempos.close();
	}
	
	return 0;
	
}
