#ifndef _BUSQUEDA_LOCAL_H
#define _BUSQUEDA_LOCAL_H

#include "tipos.h"

using namespace std;

class BusquedaLocal {
	public:
		BusquedaLocal(Grafo *G, list<Particion> k_particion_inicial, int k, bool mostrarInfo);
		~BusquedaLocal(){};
		double resolver();
		vector<int> dameSolucion();
		list<Particion> dameKParticion();

	private:
		bool mejorar();
		void mostrarMejoraVecino(vector<int> &ubicacion, double peso);

		Grafo *G; 
		int k;
		bool mostrarInfo;

		list<Particion> k_particion;
		vector<int> ubicacion;
};

#endif