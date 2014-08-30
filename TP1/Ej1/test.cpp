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

		ofstream fileTiempos("tiempos3.out");
		
//		cantTablones = 	rand() % 100000000;

		// Tests aleatorios	
		for(int i=0;i<150;i++){
			cantTablones = rand() % 100000000;
			saltoMaximo = rand() % cantTablones;
			tablonesEstado = new LTablonesEstado();
			
			for(int k=0;k<cantTablones;k++){
				tablonEstado = rand() % 2;
				tablonesEstado->push_back(tablonEstado);
			}

			LSaltos res;

			clock_t t = clock();
			res = resolver(cantTablones, saltoMaximo, *tablonesEstado);
			t = clock() - t;

//			fileTiempos << saltoMaximo << "\t" << t << endl;
//			cout << saltoMaximo << "\t" << t << endl;
			fileTiempos << cantTablones << "\t" << t << endl;
			cout << cantTablones << "\t" << t << endl;
//			imprimirResultadoAFile(res, "resultados");
			
			
			delete tablonesEstado;	
		}

		fileTiempos.close();
	}
	
	return 0;
	
}
