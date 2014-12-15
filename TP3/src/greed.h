#ifndef _GREED_H
#define _GREED_H

#include <list>
#include <iostream>
#include <vector>
#include "tipos.h"

using namespace std;

class Greed {
	public:
		Greed(Grafo *G, int k, bool mostrarInfo);
		~Greed(){};
		vector<int> resolver();
		vector<int> dameSolucion();

	private:
		vector<Arista*> getVectorDeAristasOrdenadoPorPesoDesc(list<Arista*> *aristaList);
		void ubicarNodosLibres(vector<Particion> &k_particion);
		void ubicarNodosSinAristasEnNuevaParticion(vector<Particion> &k_particion);
		void agregarAMejorParticion(vector<Particion> &k_particion, Vertice v);
		void seleccionarTopK(vector<Particion> &k_particion);
		void agregarVerticeOff(vector<Particion> &k_particion, Vertice v);

		Grafo *G; 
		int k;
		bool mostrarInfo;

		vector<int> ubicacion;
};

#endif