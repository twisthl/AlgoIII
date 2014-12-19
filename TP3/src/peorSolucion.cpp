#include "peorSolucion.h"


PeorSolucion::PeorSolucion(Grafo *G, int k, bool mostrarInfo){
	this->G = G;
	this->k = k;
	this->mostrarInfo = mostrarInfo;
}

double PeorSolucion::resolver(){

	timespec ts_beg, ts_end;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts_beg);

	//BEGIN
	Particion particion(0);
	for (Vertice v=0; v<G->getCantVertices();v++){
		particion.agregar(G, v);
	}
	this->k_particion.push_back(particion);
	this->peorPeso = cuantoPesa(this->k_particion);
	if (this->mostrarInfo) mostrarSolucion(this->k_particion, this->peorPeso);
	//END

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts_end);
	double time = (ts_end.tv_sec - ts_beg.tv_sec) + (ts_end.tv_nsec - ts_beg.tv_nsec) / 1e9;

	return time;
}

vector<int> PeorSolucion::dameSolucion(){
	return toUbicacion(G->getCantVertices(), this->k_particion);
}

list<Particion> PeorSolucion::dameKParticion(){
	return this->k_particion;
}

void PeorSolucion::mostrarSolucion(list<Particion> &k_particion, double peso){

	vector<int> ubicacion = toUbicacion(G->getCantVertices(), k_particion);
	cout << "Peor Solucion: ";
	for (int i = 0; i < ubicacion.size(); i++){
		cout << ubicacion[i] << " ";
	}
	cout << " (Peso = " << peso << ") " << endl << endl;
}