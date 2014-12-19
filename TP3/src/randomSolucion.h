#ifndef _RANDOM_SOLUCION_H
#define _RANDOM_SOLUCION_H

#include "tipos.h"
#include <stdlib.h> 
#include <time.h>

using namespace std;

class RandomSolucion {
	public:
		RandomSolucion(Grafo *G, int k, bool mostrarInfo, int seed = -1);
		~RandomSolucion(){};
		double resolver();
		vector<int> dameSolucion();
		list<Particion> dameKParticion();

	private:
		void mostrarSolucion(list<Particion> &k_particion, double peso);

		Grafo *G; 
		int k;
		bool mostrarInfo;
		list<Particion> k_particion;
		double peso;
};

#endif