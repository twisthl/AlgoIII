#ifndef _GREED_H
#define _GREED_H

#include "tipos.h"
#include <algorithm>

using namespace std;

class Greed {
	public:
		Greed(Grafo *G, int k, bool mostrarInfo);
		~Greed(){};
		double resolver();
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