#include "grasp.h"

Grasp::Grasp(Grafo *G, int k, bool mostrarInfo, double alpha, int beta, int itSinMejora, int maxIteraciones){
	this->G = G;
	this->k = k;
	this->mostrarInfo = mostrarInfo;
	this->alpha = alpha;
	this->beta = beta;
	this->itSinMejora = itSinMejora;
	this->maxIteraciones = maxIteraciones;
	this->mejorPeso = INF;

	struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
	/* using nano-seconds instead of seconds */
	srand((time_t)ts.tv_nsec);
}

double Grasp::resolver(){

	timespec ts_beg, ts_end;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts_beg);


	//BEGIN
	int ultimasNoMejoradas = 0;
	for (int i=0; i<maxIteraciones; i++){
		
		list<Particion> k_particion_inicial = greedyRandomizado();

		BusquedaLocal busquedaLocal(this->G, k_particion_inicial, this->k, false);
		busquedaLocal.resolver();
		list<Particion> posibleSolucion = busquedaLocal.dameKParticion();

		double peso = cuantoPesa(posibleSolucion);
		if (peso < this->mejorPeso){
			this->mejorKParticion = posibleSolucion;
			this->mejorPeso = peso;
			if (this->mostrarInfo) mostrarNuevaMejorSolucion(this->mejorKParticion, this->mejorPeso, i+1);
			ultimasNoMejoradas = 0;
		}else{
			ultimasNoMejoradas++;
		}
		if (ultimasNoMejoradas==this->itSinMejora) {
			if (this->mostrarInfo) 
				cout << "Finaliza en Iteracion = " << i+1 << endl << endl;
			break;
		}
	}
	//END

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts_end);
	double time = (ts_end.tv_sec - ts_beg.tv_sec) + (ts_end.tv_nsec - ts_beg.tv_nsec) / 1e9;

	return time;
}

list<Particion> Grasp::greedyRandomizado(){

	list<Particion> k_particion;
	for (int i=0; i<k; i++){
		Particion particion(i);
		k_particion.push_back(particion);
	}

	for (Vertice v=0; v < this->G->getCantVertices(); v++){
		agregarVertice(k_particion, v);
	}

	return k_particion;
}

bool mejorCandidato(Candidato &c1, Candidato &c2){
	return (c1.difPeso < c2.difPeso);
}

void Grasp::agregarVertice(list<Particion> &k_particion, Vertice v){

	double menorDifPeso = INF;
	double mayorDifPeso = -1;

	list<Candidato> RCL;

	list<Particion>::iterator itParticion;
	for (itParticion = k_particion.begin(); itParticion != k_particion.end(); itParticion++){
		double difPeso = itParticion->cuantoPesariaCon(G, v) - itParticion->getPeso();
		if (difPeso < menorDifPeso) menorDifPeso = difPeso;
		if (difPeso > mayorDifPeso) mayorDifPeso = difPeso;

		//Metemos en RCL los mejores beta candidatos.
		Candidato candidato(itParticion, difPeso);
		list<Candidato> candidatoList;
		candidatoList.push_back(candidato);
		RCL.merge(candidatoList, mejorCandidato);
		if (RCL.size() > this->beta)
			RCL.pop_back();	
	}

	// mayorDifPesoAdmitida es el peso maximo que se le permite tener a un candidato
	// Es el porcentaje alpha de los mejores casos en el rango de peso posible
	double mayorDifPesoAdmitida = menorDifPeso + ((mayorDifPeso - menorDifPeso) * (1 - this->alpha));
	list<Candidato>::iterator itCandidato;
	for (itCandidato = RCL.begin(); itCandidato != RCL.end(); itCandidato++){
		double difPeso = itCandidato->difPeso;
		if (difPeso > mayorDifPesoAdmitida)
			break;
	}
	// Desde itCandidato en adelante no son realmente candidatos. Los eliminamos
	if (itCandidato != RCL.end())
		RCL.erase(itCandidato, RCL.end());

	int iRand = (rand() % RCL.size());
	list<Candidato>::iterator itCS = RCL.begin();
    advance(itCS, iRand);

    itCS->itParticionDestino->agregarSinActualizarPeso(v);
	itCS->itParticionDestino->setPeso(itCS->itParticionDestino->getPeso()+itCS->difPeso);
}

vector<int> Grasp::dameSolucion(){
	return toUbicacion(G->getCantVertices(), this->mejorKParticion);
}

list<Particion> Grasp::dameKParticion(){
	return this->mejorKParticion;
}

void Grasp::mostrarNuevaMejorSolucion(list<Particion> &k_particion, double peso, int numIteracion){

	vector<int> ubicacion = toUbicacion(G->getCantVertices(), this->mejorKParticion);

	cout << "Nueva mejor solucion: ";
	for (int i = 0; i < ubicacion.size(); i++){
		cout << ubicacion[i] << " ";
	}
	cout << " (Peso=" << peso << "; Iteracion=" << numIteracion << ") " << endl << endl;
}