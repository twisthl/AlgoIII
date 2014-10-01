#include "ej3.h"
#include "clock.h"
#include <algorithm>
#include <time.h>
#include <iostream>

Ej3::Ej3(int n, int M, vector<vector<int> > peligrosidad, bool podaHabilitada, bool mostrarInfo){

	this->n = n;
	this->M = M;
	this->peligrosidad = peligrosidad;

	this->podaHabilitada = podaHabilitada;
	this->mostrarInfo = mostrarInfo;

	this->minCamiones = INF;
}

double Ej3::resolverBiohazard(){
	timespec ts_beg, ts_end;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts_beg);


	// BEGIN BIOHAZARD
	vector<unsigned int> carga;
	for (int i = 0; i < n; i++){
		carga.push_back(-1);
	} 
	list<Camion> camiones;
	Quimico primerQuimico = 0;
	Camion camionNuevo(0, primerQuimico);
	camiones.push_back(camionNuevo);
	carga[primerQuimico] = camionNuevo.nro;
	combinar2(camiones, primerQuimico+1, carga);
	// END BIOHAZARD

	cout << "Tiempo de ejecucion: " << endl;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts_end);
	double time = (ts_end.tv_sec - ts_beg.tv_sec) + (ts_end.tv_nsec - ts_beg.tv_nsec) / 1e9;
	cout << time << " sec" << endl;
	cout << endl;

	return time;
}

void Ej3::combinar2(list<Camion> &camiones, Quimico quimicoACargar, vector<unsigned int> &carga){

	//Lo siguiente equipara a decir: Si no hay mas quimicos para cargar..
	if (quimicoACargar == this->n) {
		if (minCamiones > camiones.size()){
			if (this->mostrarInfo) mostrarSolucion(carga, camiones.size());
			this->minCamiones = camiones.size();
			this->cargaMinima = carga;	
		}
		return;
	}

	list<Camion>::iterator itCamion;
	for (itCamion = camiones.begin(); itCamion != camiones.end(); itCamion++){
		int peligrosidadAgregada = calcularPeligrosidadAgregada(*itCamion, quimicoACargar);
		if (this->M >= (itCamion->peligrosidad + peligrosidadAgregada)){

			itCamion->quimicos.push_back(quimicoACargar);
			itCamion->peligrosidad += peligrosidadAgregada;
			carga[quimicoACargar] = itCamion->nro;
			combinar2(camiones, quimicoACargar+1, carga);
			carga[quimicoACargar] = -1;
			itCamion->peligrosidad -= peligrosidadAgregada;
			itCamion->quimicos.pop_back();
		}
	}
	
	// Podamos las combinaciones de carga de quimicos que ya no pueden superar a la mejor solucion obtenida hasta ahora
	if (!podaHabilitada || camiones.size() + 1 < this->minCamiones) {
		Camion camionNuevo(camiones.size(), quimicoACargar);
		camiones.push_back(camionNuevo);
		carga[quimicoACargar] = camionNuevo.nro;
		combinar2(camiones, quimicoACargar+1, carga);
		carga[quimicoACargar] = -1;
		camiones.pop_back();
	}
}

// Calcula la peligrosidad que agrega el combinar un nuevo quimico a un camion con una cierta distribucion.
int Ej3::calcularPeligrosidadAgregada(Camion &camion, Quimico quimico){
	int peligrosidadAgregada = 0;
	list<Quimico>::iterator it;
	for (it = camion.quimicos.begin(); it != camion.quimicos.end(); it++){
		peligrosidadAgregada += this->peligrosidad[quimico][*it];
	}
	return peligrosidadAgregada;
}

void Ej3::mostrarSolucion(){
	cout << "Mejor solucion: " << endl;
	mostrarSolucion(this->cargaMinima, this->minCamiones);
}

void Ej3::mostrarSolucion(vector<unsigned int> &carga, unsigned int cantCamiones){
	cout << cantCamiones << " ";
	for (int i = 0; i < this->n; i++){
		cout << carga[i] << " ";
	}
	cout << endl << endl;
}

string Ej3::dameSolucion(){
	string solucion = std::to_string(this->minCamiones) + " ";
	for (int i = 0; i < this->n; i++){
		solucion += std::to_string(this->cargaMinima[i]) + " ";
	}
	return solucion;
}


/*void Ej3::combinar(Camion camion, Quimico ultimaCarga, int peligrosidad, vector<Camion> &carga, int noCargados){

	if (noCargados == 0) {
		if (minCamiones > camion + 1){
			mostrarSolucion(carga, camion + 1);
			this->minCamiones = camion + 1;
			this->cargaMinima = carga;
			
		}
		return;
	}

	// Se buscan quimicos siempre para adelante del ultimo cargado. De esta manera se evitan colecciones de igual distribucion de quimicos.
	for (Quimico quimico = ultimaCarga++; quimico < this->n; quimico++){

		if (carga[quimico] != -1) continue; // Si el quimico ya esta cargado entonces busco otro para cargar

		int nuevaPeligrosidad = peligrosidad + calcularPeligrosidadAgregada(carga, camion, quimico);
		if (this->M >= nuevaPeligrosidad){
			carga[quimico] = camion;
			combinar(camion, quimico, nuevaPeligrosidad, carga, noCargados-1);
			carga[quimico] = -1;
		}
	}

	// Podamos las combinaciones de carga de quimicos que ya no pueden superar a la mejor solucion obtenida hasta ahora
	if (camion + 1 + 1 < minCamiones) {
		for (Quimico quimico = 0; quimico < this->n; quimico++){ 
			bool encontre = false;
			if (carga[quimico] == -1 && !encontre){
				//El quimico obligatoriamente se ubica en el proximo camion. Esto se hace para no repetir combinaciones.
				carga[quimico] = camion + 1;
				combinar(camion+1, quimico, 0, carga, noCargados-1);
				carga[quimico] =  -1;
				encontre = true;
			}
		}
	}
	
}*/