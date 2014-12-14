#include "greed.h"
#include "clock.h"
#include <algorithm>
#include <time.h>

Greed::Greed(Grafo *G, int k, bool mostrarInfo){
	this->G = G;
	this->k = k;
	this->mostrarInfo = mostrarInfo;
}

vector<int> Greed::resolver(){
	vector<Arista*> aristasPesoDesc = this->getVectorDeAristasOrdenadoPorPesoDesc(G->getAristas());




}

bool Greed::wayToSort(Arista* a1, Arista* a2) { 
	return a1->getPeso() > a2->getPeso(); 
}

vector<Arista*> Greed::getVectorDeAristasOrdenadoPorPesoDesc(list<Arista*> *aristaList){

	vector<Arista*> aristaVectorOrdenado;
	for (list<Arista*>::iterator it = aristaList->begin(); it != aristaList->end(); it++){
		aristaVectorOrdenado.push_back(*it);
	}
	sort(aristaVectorOrdenado.begin(), aristaVectorOrdenado.end(), wayToSort);

	return aristaVectorOrdenado;
}