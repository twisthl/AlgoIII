#include "clock.h"
#include <iostream>
#include "tipos.h"
#include "opciones.h"
#include "grasp.h"

#define TAB "\t"

using namespace std;

int main(int argc, char * argv[]){

	int n = 15;

	for (int k = 2; k <= n; k+= 3){
		for (int m = 3; m <= n*(n-1)/2; m+=3){
			Grafo* G = generarGrafoRandom(n, k, m);
			Exacto exacto(G, k, true, false);
			double mejorPeso = cuantoPesa(exacto.dameKParticion());
			tiempoExacto = exacto.resolver();

			PeorSolucion peorSolucion(G, k, false);
			double peorPeso = cuantoPesa(peorSolucion.dameKParticion());

			for (double alpha =0; alpha+=0.05; alpha <= 1){
				

			}
			
		}
	}

	


	return 0;
}
