#include "greed.h"
#include "clock.h"
#include <algorithm>
#include <time.h>

Greed::Greed(Grafo *G, int k, bool mostrarInfo){
	this->G = G;
	this->k = k;
	this->mostrarInfo = mostrarInfo;

	for (int i=0; i<G->getCantVertices(); i++){
		this->ubicacion.push_back(-1);
	}
}

vector<int> Greed::resolver(){
	
	vector<Particion> k_particion;

	seleccionarTopK(k_particion);

	if (this->k - k_particion.size() > 0){
		ubicarNodosSinAristasEnNuevaParticion(k_particion);
	}else{
		ubicarNodosLibres(k_particion);
	}

	return this->ubicacion;
}

void Greed::ubicarNodosSinAristasEnNuevaParticion(vector<Particion> &k_particion){
	//Si todavia quedan k libres, quiere decir que no hay mas aristas. Por lo tanto podriamos ubicar todos los nodos restantes
	//en cualquier particion. Por si no hay particiones creadas, creamos una particion nueva.
	Particion particionNueva(k_particion.size());
	k_particion.push_back(particionNueva);
	for (Vertice v=0; v<this->G->getCantVertices(); v++){
		if (this->ubicacion[v] == -1){
			k_particion[k_particion.size()-1].agregarSinActualizarPeso(*(this->G), v);
			this->ubicacion[v] = particionNueva.getNro();
		}
	}
}

void Greed::ubicarNodosLibres(vector<Particion> &k_particion){
	for (Vertice v=0; v < this->ubicacion.size(); v++){
		if (this->ubicacion[v] == -1)
			agregarAMejorParticion(k_particion, v);
	}
}


void Greed::agregarAMejorParticion(vector<Particion> &k_particion, Vertice v){
	double menorDifPeso = INF;
	int indiceMejorParticion;
	for (int i=0; i < k_particion.size(); i++){
		double difPeso = k_particion[i].cuantoPesariaCon(*(this->G), v) - k_particion[i].getPeso();
		if (difPeso < menorDifPeso){
			menorDifPeso = difPeso;
			indiceMejorParticion = i;
			if (difPeso == 0) break;
		}
	}
	k_particion[indiceMejorParticion].agregarSinActualizarPeso(*(this->G), v);
	k_particion[indiceMejorParticion].setPeso(k_particion[indiceMejorParticion].getPeso()+menorDifPeso);
	this->ubicacion[v] = k_particion[indiceMejorParticion].getNro();

}

void Greed::seleccionarTopK(vector<Particion> &k_particion){

	vector<Arista*> aristasPesoDesc = this->getVectorDeAristasOrdenadoPorPesoDesc(G->getAristas());

	for (int i=0; i < aristasPesoDesc.size(); i++){

		if (this->k - k_particion.size() == 0) break;
		agregarVerticeOff(k_particion, aristasPesoDesc[i]->getVertice1());

		if (this->k - k_particion.size() == 0) break;
		agregarVerticeOff(k_particion, aristasPesoDesc[i]->getVertice2());
	}

}

void Greed::agregarVerticeOff(vector<Particion> &k_particion, Vertice v){
	if (this->ubicacion[v] == -1){
		Particion particion(k_particion.size());
		particion.agregarSinActualizarPeso(*(this->G), v);
		k_particion.push_back(particion);
		this->ubicacion[v] = particion.getNro();
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

vector<int> Greed::dameSolucion(){	
	return this->ubicacion;
}