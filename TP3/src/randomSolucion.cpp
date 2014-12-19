#include "randomSolucion.h"


RandomSolucion::RandomSolucion(Grafo *G, int k, bool mostrarInfo, int seed){
	this->G = G;
	this->k = k;
	this->mostrarInfo = mostrarInfo;

	if (seed == -1) {
		struct timespec ts;
    	clock_gettime(CLOCK_MONOTONIC, &ts);
	    /* using nano-seconds instead of seconds */
	    srand((time_t)ts.tv_nsec);
	}else 
		srand(seed);
}

double RandomSolucion::resolver(){

	timespec ts_beg, ts_end;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts_beg);

	//BEGIN
	for (Vertice v=0; v<G->getCantVertices(); v++){
		int iRand = (rand() % (k_particion.size()+1));
		list<Particion>::iterator it = k_particion.begin();
    	advance(it, iRand);
    	if (it == k_particion.end()){
    		Particion particion(k_particion.size());
    		particion.agregar(G, v);
			this->k_particion.push_back(particion);
    	}else{
    		it->agregar(G, v);
    	}
    }
	this->peso = cuantoPesa(this->k_particion);
	if (this->mostrarInfo) mostrarSolucion(this->k_particion, this->peso);
	//END

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts_end);
	double time = (ts_end.tv_sec - ts_beg.tv_sec) + (ts_end.tv_nsec - ts_beg.tv_nsec) / 1e9;

	return time;
}

vector<int> RandomSolucion::dameSolucion(){
	return toUbicacion(G->getCantVertices(), this->k_particion);
}

list<Particion> RandomSolucion::dameKParticion(){
	return this->k_particion;
}

void RandomSolucion::mostrarSolucion(list<Particion> &k_particion, double peso){

	vector<int> ubicacion = toUbicacion(G->getCantVertices(), k_particion);
	cout << "Peor Solucion: ";
	for (int i = 0; i < ubicacion.size(); i++){
		cout << ubicacion[i] << " ";
	}
	cout << " (Peso = " << peso << ") " << endl << endl;
}