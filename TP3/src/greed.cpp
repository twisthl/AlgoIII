#include "greed.h"

Greed::Greed(Grafo *G, int k, bool mostrarInfo){
	this->G = G;
	this->k = k;
	this->mostrarInfo = mostrarInfo;

	for (int i=0; i<G->getCantVertices(); i++){
		this->ubicacion.push_back(-1);
	}
}

double Greed::resolver(){

	timespec ts_beg, ts_end;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts_beg);

	//BEGIN
	seleccionarTopK();
	if (this->k - this->k_particion.size() > 0){
		ubicarNodosSinAristasEnNuevaParticion();
	}else{
		ubicarNodosLibres();
	}
	//END

	cout << "Tiempo de ejecucion: " << endl;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts_end);
	double time = (ts_end.tv_sec - ts_beg.tv_sec) + (ts_end.tv_nsec - ts_beg.tv_nsec) / 1e9;
	cout << time << " sec" << endl;
	cout << endl;

	return time;
}

void Greed::ubicarNodosSinAristasEnNuevaParticion(){
	//Si todavia quedan k libres, quiere decir que no hay mas aristas. Por lo tanto podriamos ubicar todos los nodos restantes
	//en cualquier particion. Por si no hay particiones creadas, creamos una particion nueva.
	Particion particionNueva(this->k_particion.size());
	this->k_particion.push_back(particionNueva);
	for (Vertice v=0; v<this->G->getCantVertices(); v++){
		if (this->ubicacion[v] == -1){
			this->k_particion.back().agregarSinActualizarPeso(*(this->G), v);
			this->ubicacion[v] = particionNueva.getNro();
		}
	}
}

void Greed::ubicarNodosLibres(){
	for (Vertice v=0; v < this->ubicacion.size(); v++){
		if (this->ubicacion[v] == -1)
			agregarAMejorParticion(v);
	}
}


void Greed::agregarAMejorParticion(Vertice v){
	double menorDifPeso = INF;
	list<Particion>::iterator itMejorParticion;

	list<Particion>::iterator itParticion;
	for (itParticion = this->k_particion.begin(); itParticion != this->k_particion.end(); itParticion++){
		double difPeso = itParticion->cuantoPesariaCon(*(this->G), v) - itParticion->getPeso();
		if (difPeso < menorDifPeso){
			menorDifPeso = difPeso;
			itMejorParticion = itParticion;
			if (difPeso == 0) break;
		}
	}
	itMejorParticion->agregarSinActualizarPeso(*(this->G), v);
	itMejorParticion->setPeso(itMejorParticion->getPeso()+menorDifPeso);
	this->ubicacion[v] = itMejorParticion->getNro();

}

void Greed::seleccionarTopK(){

	vector<Arista*> aristasPesoDesc = this->getVectorDeAristasOrdenadoPorPesoDesc(G->getAristas());

	for (int i=0; i < aristasPesoDesc.size(); i++){

		if (this->k - this->k_particion.size() == 0) break;
		agregarVerticeOff(aristasPesoDesc[i]->getVertice1());

		if (this->k - this->k_particion.size() == 0) break;
		agregarVerticeOff(aristasPesoDesc[i]->getVertice2());
	}

}

void Greed::agregarVerticeOff(Vertice v){
	if (this->ubicacion[v] == -1){
		Particion particion(this->k_particion.size());
		particion.agregarSinActualizarPeso(*(this->G), v);
		this->k_particion.push_back(particion);
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