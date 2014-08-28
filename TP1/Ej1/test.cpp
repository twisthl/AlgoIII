#include "ej1.h"
#include <time.h>
#include <cmath>

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

		cantTablones = rand() % 1000000;
		saltoMaximo = rand() % 100000;
		
		// Tests aleatorios	
		for(int i=0;i<100;i++){
			tablonesEstado = new LTablonesEstado();
			saltoMaximo = rand() % 1000000 + 1;

			for(int k=0;k<cantTablones;k++){
				tablonEstado = rand() % 2;
				tablonesEstado->push_back(tablonEstado);
			}
			clock_t t = clock();
			resolver(cantTablones, saltoMaximo, *tablonesEstado);
			t = clock() - t;
		
			cout << cantTablones << "\t" << t << endl;
			
			delete tablonesEstado;	
		}
	}
	
	return 0;
	
}
