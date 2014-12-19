#ifndef _PEOR_SOLUCION_H
#define _PEOR_SOLUCION_H

#include "tipos.h"

using namespace std;

class PeorSolucion {
	public:
		PeorSolucion(Grafo *G, int k, bool mostrarInfo);
		~PeorSolucion(){};
		double resolver();
		vector<int> dameSolucion();
		list<Particion> dameKParticion();

	private:
		void mostrarSolucion(list<Particion> &k_particion, double peso);

		Grafo *G; 
		int k;
		bool mostrarInfo;
		list<Particion> k_particion;
		double peorPeso;
};

#endif