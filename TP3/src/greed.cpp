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
	
	vector<Particion> k_particion;

	seleccionarTopK(k_particion);
	ubicarNodosLibres(k_particion);



	if (this->k - k_particion.size() < 0){
		
	}else{
		
	}
	//Si todavia quedan k libres, quiere decir que no hay mas aristas. Por lo tanto podriamos ubicar todos los nodos restantes
	//en cualquier 
}
void Greed::ubicarNodosLibres(vector<Particion> &k_particion)){
	for (Vertice v=0; v < this->ubicacion.size(); v++){
		if (this->ubicacion[v] == -1)
			agregarAMejorParticion(k_particion, v);
	}
}


void Greed::agregarAMejorParticion(vector<Particion> &k_particion, Vertice v){
	double menorPeso = INF;
	int nroMejorParticion;
	for (int i=0; i < k_particion.size(); i++){
		double peso = k_particion[i].cuantoPesariaCon(v);
		if (peso == 0) {
			k_particion.agregar(v);
		}else{
			if (peso < menorPeso){
				menorPeso = peso;
				nroMejorParticion = particion.getNro();
			}
		}
	}
}

void Greed::seleccionarTopK(vector<Particion> &k_particion){

	vector<Arista*> aristasPesoDesc = this->getVectorDeAristasOrdenadoPorPesoDesc(G->getAristas());

	for (int i=0; i < aristasPesoDesc.size(); i++){
		
		if (this->k - k_particion.size() == 0) break;

		agregarVerticeOff(aristasPesoDesc[i].getVertice1());

		if (this->k - k_particion.size() == 0) break;

		agregarVerticeOff(aristasPesoDesc[i].getVertice2());
	}

}

void Greed::agregarVerticeOff(vector<Particion> &k_particion, Vertice v){
	if (this->ubicacion[v] == -1){
		Particion particion(k_particion.size());
		particion.agregar(this->G, v);
		k_particion.push_back(particion);
		this->ubicacion[v] = particion.nro();
	}
}


bool wayToSort(Arista* a1, Arista* a2) { 
	return (a1->getPeso() > a2->getPeso()); 
}

vector<Arista*> Greed::getVectorDeAristasOrdenadoPorPesoDesc(list<Arista*> *aristaList){
	vector<Arista*> res;
	for (list<Arista*>::iterator it = aristaList->begin(); it != aristaList->end(); it++){
		res.push_back(*it);
	}
	sort(res.begin(), res.end(), wayToSort);

	return res;
}