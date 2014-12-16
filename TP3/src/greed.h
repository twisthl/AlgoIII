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
		list<Particion>	dameKParticion();

	private:
		vector<Arista*> getVectorDeAristasOrdenadoPorPesoDesc(list<Arista*> *aristaList);
		void ubicarNodosLibres();
		void ubicarNodosSinAristasEnNuevaParticion();
		void agregarAMejorParticion(Vertice v);
		void seleccionarTopK();
		void agregarVerticeOff(Vertice v);

		Grafo *G; 
		int k;
		bool mostrarInfo;

		vector<int> ubicacion;
		list<Particion> k_particion;
};

#endif