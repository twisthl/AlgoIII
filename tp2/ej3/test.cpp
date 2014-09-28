#include "ej3.h"
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
	

	int cantComputadoras;
	int cantEnlaces;
	
	Red* red;
	
	if(seed>0){
				
		srand(seed);

		ofstream fileTiempos("tiempos1.out");
		
//		cantComputadoras = 	rand() % 100000000;

		// Tests aleatorios	
		for(int i=0;i<150;i++){
			cantComputadoras = rand() % 100000000;
			cantEnlaces = rand() % 100000000; 
			red = new Red();
			
			for(int k=0;k<cantEnlaces;k++){
				Enlace enlace;

				enlace.compu1 = rand() % cantComputadoras;
				enlace.compu2 = rand() % cantComputadoras;
				enlace.costo = rand() % 50;

				red->push_back(enlace);
			}

			//LSaltos res;

			clock_t t = clock();
			res = resolver(cantComputadoras, cantEnlaces, *red);
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
