#ifndef _GRASP_H
#define _GRASP_H

#include "tipos.h"
#include "busqueda_local.h"
#include <stdlib.h> 
#include <time.h>

using namespace std;

class Grasp {
	public:
		Grasp(Grafo *G, int k, bool mostrarInfo, double alpha, int beta, int itSinMejora, int maxIteraciones);
		~Grasp(){};
		double resolver();
		vector<int> dameSolucion();
		list<Particion> dameKParticion();

	private:
		list<Particion> greedyRandomizado();
		void agregarVertice(list<Particion> &k_particion, Vertice v);
		void mostrarNuevaMejorSolucion(list<Particion> &k_particion, double peso, int numIteracion);

		Grafo *G;
		int k;
		bool mostrarInfo;
		list<Particion> mejorKParticion;
		double mejorPeso;
		int itSinMejora;
		int maxIteraciones;
		double alpha;
		int beta;

};

bool mejorCandidato(Candidato &c1, Candidato &c2);

#endif