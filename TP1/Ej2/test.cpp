#include "ej2.h"
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


	//int cantInstancias;
	int cantEdificios;
	int comienzo;
	int fin;
	int altura;
	
	//Ciudad* ciudad;
	
	if(seed>0){
				
		srand(seed);

		//cin >> cantInstancias;

		ofstream fileTiempos("tiemposEdificios2.out");
		
		// Tests aleatorios	
		for(int i=0;i<50;i++){
			Edificio* edificio;
			Edificios* edificios;

			cantEdificios = rand() % 1000000 + 1;
			edificios = new Edificios();
		
			for(int k=0;k<cantEdificios;k++){
				comienzo = rand() % 300;
				fin = (rand() % 300) + comienzo;
				altura = rand() % 1000;

				edificio = new Edificio(comienzo,fin,altura);

				edificios->push_back(*edificio);
			}

			Ciudad* ciudad;

			clock_t t = clock();
			ciudad = edificar(cantEdificios, *edificios);
			t = clock() - t;

			ciudad = ciudad;

//			fileTiempos << saltoMaximo << "\t" << t << endl;
//			cout << saltoMaximo << "\t" << t << endl;
			fileTiempos << cantEdificios << "\t" << t << endl;
			cout << cantEdificios << "\t" << t << endl;
//			imprimirResultadoAFile(res, "resultados");
			
			
			//delete edificios;	
		}

		fileTiempos.close();
	}
	
	return 0;
	
}
