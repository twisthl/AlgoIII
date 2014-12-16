#include "exacto.h"


Exacto::Exacto(Grafo *G, int k, bool podaHabilitada, bool mostrarInfo){
	
	this->G = G;
	this->k = k;
	this->podaHabilitada = podaHabilitada;
	this->mostrarInfo = mostrarInfo;

}

double Exacto::resolver(){

	timespec ts_beg, ts_end;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts_beg);

	//BEGIN
	list<Particion> k_particion;

	Vertice primerVertice = 0;
	Particion particionNueva(0);
	particionNueva.agregar(*G, primerVertice);
	k_particion.push_back(particionNueva);

	this->mejorPeso = INF;

	this->combinar(k_particion, primerVertice+1, 0);
	//END

	cout << "Tiempo de ejecucion: " << endl;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts_end);
	double time = (ts_end.tv_sec - ts_beg.tv_sec) + (ts_end.tv_nsec - ts_beg.tv_nsec) / 1e9;
	cout << time << " sec" << endl;
	cout << endl;

	return time;
}

void Exacto::combinar(list<Particion> &k_particion, Vertice verticeAUbicar, double pesoAcumulado){

	//Lo siguiente equipara a decir: Si no hay mas quimicos para cargar..
	if (verticeAUbicar == G->getCantVertices()) {
		if (pesoAcumulado < this->mejorPeso){
			this->mejorPeso = pesoAcumulado;
			this->mejorKParticion = k_particion;
			if (mostrarInfo) mostrarPotencialSolucion(this->mejorKParticion, this->mejorPeso);
		}
		return;
	}

	list<Particion>::iterator itParticion;
	for (itParticion = k_particion.begin(); itParticion != k_particion.end(); itParticion++){

		double pesoOld = itParticion->getPeso();
		double pesoNew = itParticion->cuantoPesariaCon((*this->G), verticeAUbicar);
		double difPeso = pesoNew - pesoOld;

		if (this->podaHabilitada && (this->mejorPeso <= pesoAcumulado+difPeso))
			continue;

		// 'agregar' no vuelve a calcular el peso. Ya lo calcul'o en cuantoPesariaCon donde se cachea.
		itParticion->agregar((*this->G), verticeAUbicar);
		pesoAcumulado += difPeso;

		combinar(k_particion, verticeAUbicar+1, pesoAcumulado);

		pesoAcumulado -= difPeso;
		itParticion->quitarUltimoSinActualizarPeso();
		itParticion->setPeso(pesoOld);
	}
	

	// Si hay menos de k particiones el vertice se puede ubicar en una particion nueva.
	if (k_particion.size() < k) {
		Particion particionNueva(k_particion.size());
		particionNueva.agregar((*this->G), verticeAUbicar);
		k_particion.push_back(particionNueva);
		//No hace falta fijarse que pesoAcumulado sea menor a mejorPeso porque el pesoAcumulado no se modifica al hacer una particion nueva sin aristas.
		combinar(k_particion, verticeAUbicar+1, pesoAcumulado);
		k_particion.pop_back();
	}

}

void Exacto::mostrarPotencialSolucion(list<Particion> &k_particion, double peso){

	vector<int> ubicacion = toUbicacion(G->getCantVertices(), k_particion);
	cout << "Potencial Solucion: ";
	for (int i = 0; i < ubicacion.size(); i++){
		cout << ubicacion[i] << " ";
	}
	cout << " (Peso = " << peso << ") " << endl << endl;
}

vector<int> Exacto::dameSolucion(){
	return toUbicacion(G->getCantVertices(), this->mejorKParticion);
}
