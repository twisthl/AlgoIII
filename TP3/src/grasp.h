#ifndef _GRASP_H
#define _GRASP_H

#include "tipos.h"
#include "busqueda_local.h"
#include <stdlib.h> 
#include <time.h>

using namespace std;

class Grasp {
	public:
		Grasp(Grafo *G, int k, bool mostrarInfo, int iteraciones, double alpha, int beta);
		~Grasp(){};
		double resolver();
		vector<int> dameSolucion();
		list<Particion> dameKParticion();

	private:
		list<Particion> greedyRandomizado();
		void agregarVertice(list<Particion> &k_particion, Vertice v);
		void mostrarNuevaMejorSolucion(list<Particion> &k_particion, double peso);

		Grafo *G;
		int k;
		bool mostrarInfo;
		list<Particion> mejorKParticion;
		double mejorPeso;
		int iteraciones;
		double alpha;
		int beta;

};

bool mejorCandidato(Candidato &c1, Candidato &c2);

#endif