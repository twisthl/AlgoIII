#ifndef _GREED_H
#define _GREED_H

#include <list>
#include <iostream>
#include <vector>
#include "tipos.h"

using namespace std;

class Greed {
	public:
		Greed(Grafo *G, int k, bool mostrarInfo);
		~Greed(){};
		vector<int> resolver();
		vector<int> dameSolucion();

	private:
		bool wayToSort(Arista* a1, Arista* a2);
		vector<Arista*> getVectorDeAristasOrdenadoPorPesoDesc(list<Arista*> *aristaList);

		Grafo *G; 
		int k;
		bool mostrarInfo;
};

#endif