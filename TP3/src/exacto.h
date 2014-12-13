#ifndef _EXACTO_H
#define _EXACTO_H

#include <list>
#include <iostream>
#include <vector>
#include "tipos.h"

using namespace std;

class Exacto {
	public:
		Exacto(Grafo *G, int k, bool podaHabilitada, bool mostrarInfo);
		~Exacto(){};
		vector<int> resolver();
		vector<int> dameSolucion();

	private:
		void combinar(list<Particion> &k_particion, Vertice verticeAUbicar, vector<int> &ubicacion, int pesoAcumulado);
		void mostrarPotencialSolucion(vector<int> &ubicacion);

		Grafo *G; 
		int k;
		bool podaHabilitada;
		bool mostrarInfo;
		vector<int> mejorUbicacion;
		int mejorPeso;
};

#endif