#include "ej3.h"
#include "aux.h"
#include <algorithm>
#include <time.h>
#include <iostream>

Ej3::Ej3(Opciones opt){

	parser.cargar(opt.archivo_entrada);

	parser.setOutputFile(opt.archivo_salida);

	this->n = parser.getN();
	this->M = parser.getM();
	this->peligrosidad = parser.getPeligrosidad();

	this->minCamiones = INF;
}

void Ej3::resolverBiohazard(){
	timespec ts_beg, ts_end;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts_beg);

	vector<Camion> carga;
	for (int i = 0; i < n; i++){
		carga.push_back(-1);
	} 

	// BEGIN BIOHAZARD
	carga[0] = 0;
	combinar(0, 0, 0, carga, this->n-1);
	// END BIOHAZARD

	cout << "Tiempo de ejecucion: " << endl;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts_end);
	double time = (ts_end.tv_sec - ts_beg.tv_sec) + (ts_end.tv_nsec - ts_beg.tv_nsec) / 1e9;
	cout << time << " sec" << endl;
	cout << endl;

	parser.guardarTiempoEjecucion(this->n, time);
}

void Ej3::combinar(Camion camion, Quimico ultimaCarga, int peligrosidad, vector<Camion> &carga, int noCargados){

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
	
}

// Calcula la peligrosidad que agrega el combinar un nuevo quimico a un camion con una cierta distribucion.
int Ej3::calcularPeligrosidadAgregada(vector<Camion> &carga, Camion camion, Quimico quimicoA){
	int peligrosidadAgregada = 0;
	for (Quimico quimicoB = 0; quimicoB < this->n; quimicoB++){
		if (carga[quimicoB] == camion)
			peligrosidadAgregada += peligrosidad[quimicoA][quimicoB];
	}
	return peligrosidadAgregada;
}

void Ej3::mostrarMejorSolucion(){
	cout << "Mejor solucion: " << endl;
	mostrarSolucion(cargaMinima, minCamiones);
}

void Ej3::mostrarSolucion(vector<Camion> &carga, int cantCamiones){
	cout << cantCamiones << " ";
	for (int i = 0; i < this->n; i++){
		cout << carga[i] << " ";
	}
	cout << endl << endl;
}