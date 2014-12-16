#ifndef _EXACTO_H
#define _EXACTO_H

#include "tipos.h"

using namespace std;

class Exacto {
	public:
		Exacto(Grafo *G, int k, bool podaHabilitada, bool mostrarInfo);
		~Exacto(){};
		double resolver();
		vector<int> dameSolucion();
		list<Particion> dameKParticion();

	private:
		void combinar(list<Particion> &k_particion, Vertice verticeAUbicar, double pesoAcumulado);
		void mostrarPotencialSolucion(list<Particion> &k_particion, double peso);

		Grafo *G; 
		int k;
		bool podaHabilitada;
		bool mostrarInfo;
		list<Particion> mejorKParticion;
		double mejorPeso;
};

#endif