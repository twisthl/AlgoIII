#include "greed.h"
#include "clock.h"
#include <algorithm>
#include <time.h>

k_particion greed(Grafo &G, int k){

	vector<Arista*> aristasPesoDesc = getVectorDeAristasOrdenadoPorPesoDesc(G.getAristas());
	
}


vector<Arista*> getVectorDeAristasOrdenadoPorPesoDesc(list<Arista*> *aristaList){

	Vector<Arista*> aristaVectorOrdenado;
	for (list<Arista*>::iterator it = aristaList->begin(); it != aristaList->end(); it++){
		aristaVectorOrdenado.push_back(*it);
	}

	bool wayToSort(Arista* a1, Arista* a2) { return a1->getPeso() > a2->getPeso(); }
	std::sort(aristaVectorOrdenado->begin(), aristaVectorOrdenado->end(), wayToSort);

	return 
}