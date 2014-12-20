#include "busqueda_local.h"

BusquedaLocal::BusquedaLocal(Grafo *G, list<Particion> k_particion_inicial, int k, bool mejora2, bool mostrarInfo){
	this->G = G;
	this->k = k;
	this->mostrarInfo = mostrarInfo;

	this->k_particion = k_particion_inicial;

	//toUbicacion devuelve una vector con indice VERTICE resultado nro de particion en la que esta ubicado
	this->ubicacion = toUbicacion(G->getCantVertices(), k_particion_inicial);

	if (mejora2)
		this->vecindad = 2;
	else
		this->vecindad = 1;
}

double BusquedaLocal::resolver(){

	timespec ts_beg, ts_end;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts_beg);

	//BEGIN
	bool hayMejora;
	do {
		if (this->vecindad == 1)
			hayMejora = mejorar();
		else
			hayMejora = mejorar2();
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

bool BusquedaLocal::mejorar2(){

	bool haMejorado = false;
	Vertice vertice1AMover = -1;
	Vertice vertice2AMover = -1;
	list<Particion>::iterator itP1Seleccionada;
	list<Particion>::iterator itP2Seleccionada;
	double mayorPesoPerdido = 0.0;

	list<Particion>::iterator itParticion1;
	
	list<Vertice>::iterator itVerticesP1;
	list<Vertice>::iterator itVerticesP2;

	for (itParticion1 = this->k_particion.begin(); itParticion1 != this->k_particion.end(); itParticion1++){
		list<Vertice> verticesP1 = itParticion1->getVertices();

		list<Particion>::iterator itParticion2Begin = itParticion1;
		itParticion2Begin++;
		list<Particion>::iterator itParticion2;
		for (itParticion2 = itParticion2Begin; itParticion2 != this->k_particion.end(); itParticion2++){

			list<Vertice> verticesP2 = itParticion2->getVertices();
			for (itVerticesP1 = verticesP1.begin(); itVerticesP1 != verticesP1.end(); itVerticesP1++){
				Vertice vertice1 = *itVerticesP1;
				for (itVerticesP2 = verticesP2.begin(); itVerticesP2 != verticesP2.end(); itVerticesP2++){
					Vertice vertice2 = *itVerticesP2;
					int pesoViejo = itParticion1->getPeso() + itParticion2->getPeso();
					int pesoNuevo = itParticion1->cuantoPesariaSwaping(G, vertice2, vertice1) + itParticion2->cuantoPesariaSwaping(G, vertice1, vertice2);
					int pesoPerdido = pesoViejo - pesoNuevo;
					if (pesoPerdido > mayorPesoPerdido){
						haMejorado = true;
						mayorPesoPerdido = pesoPerdido;
						itP1Seleccionada = itParticion1;
						itP2Seleccionada = itParticion2;
						vertice1AMover = vertice1;
						vertice2AMover = vertice2;
					}

				}
			}
		}
	}

	if (haMejorado){
		itP1Seleccionada->quitar(G, vertice1AMover);
		itP1Seleccionada->agregar(G, vertice2AMover);
		itP2Seleccionada->quitar(G, vertice2AMover);
		itP2Seleccionada->agregar(G, vertice1AMover);

		this->ubicacion[vertice1AMover] = itP2Seleccionada->getNro();
		this->ubicacion[vertice2AMover] = itP1Seleccionada->getNro();

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