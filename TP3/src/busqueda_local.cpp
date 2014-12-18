#include "busqueda_local.h"

BusquedaLocal::BusquedaLocal(Grafo *G, list<Particion> k_particion_inicial, int k, bool mostrarInfo){
	this->G = G;
	this->k = k;
	this->mostrarInfo = mostrarInfo;

	this->k_particion = k_particion_inicial;

	//toUbicacion devuelve una vector con indice VERTICE resultado nro de particion en la que esta ubicado
	this->ubicacion = toUbicacion(G->getCantVertices(), k_particion_inicial);
}

double BusquedaLocal::resolver(){

	timespec ts_beg, ts_end;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts_beg);

	//BEGIN
	bool hayMejora;
	do {
		hayMejora = mejorar();
	} while (hayMejora);
	//END
	
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts_end);
	double time = (ts_end.tv_sec - ts_beg.tv_sec) + (ts_end.tv_nsec - ts_beg.tv_nsec) / 1e9;

	return time;
}

bool BusquedaLocal::mejorar(){

	bool haMejorado = false;
	Vertice verticeAMover = -1;
	list<Particion>::iterator itParticionFuente;
	list<Particion>::iterator itParticionDestino;
	double mayorPesoPerdido = 0.0;

	for (Vertice vertice = 0; vertice < G->getCantVertices(); vertice++){

		list<Particion>::iterator deDondeSeMoveria;
		list<Particion>::iterator dondeSeMoveria;
		double cuantoPesoPerderia;
		double cuantoPesoSumaria = INF;

		list<Particion>::iterator itParticion;
		for (itParticion = this->k_particion.begin(); itParticion != this->k_particion.end(); itParticion++){
			if (this->ubicacion[vertice] == itParticion->getNro()){
				cuantoPesoPerderia = itParticion->getPeso() - itParticion->cuantoPesariaSin(G, vertice);
				deDondeSeMoveria = itParticion;
			}else{
				double cuantoPesoSumariaAca = itParticion->cuantoPesariaCon(G, vertice) - itParticion->getPeso();
				if (cuantoPesoSumariaAca < cuantoPesoSumaria) {
					cuantoPesoSumaria = cuantoPesoSumariaAca;
					dondeSeMoveria = itParticion;
				}
			}	
		}
		double cuantoMenosPesaria = cuantoPesoPerderia - cuantoPesoSumaria;
		if (cuantoMenosPesaria > mayorPesoPerdido){
			mayorPesoPerdido = cuantoMenosPesaria;
			itParticionFuente = deDondeSeMoveria;
			itParticionDestino = dondeSeMoveria;
			verticeAMover = vertice;
		}
	}

	if (verticeAMover != -1){
		haMejorado = true;
		itParticionFuente->quitar(G, verticeAMover);
		itParticionDestino->agregar(G, verticeAMover);
		this->ubicacion[verticeAMover] = itParticionDestino->getNro();

		if (this->mostrarInfo) {
			double nuevoPeso = cuantoPesa(k_particion);
			mostrarMejoraVecino(this->ubicacion, nuevoPeso);
		}
	}
	return haMejorado;
}

vector<int> BusquedaLocal::dameSolucion(){	
	return this->ubicacion;
}

list<Particion> BusquedaLocal::dameKParticion(){	
	return this->k_particion;
}

void BusquedaLocal::mostrarMejoraVecino(vector<int> &ubicacion, double peso){

	cout << "Mejorado a vecino: ";
	for (int i = 0; i < ubicacion.size(); i++){
		cout << ubicacion[i] << " ";
	}
	cout << " (Peso = " << peso << ") " << endl << endl;
}