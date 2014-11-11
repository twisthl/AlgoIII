/* Resolucion del ejercicio 1*/
#ifndef _EJ1_H_
#define _EJ1_H_

#include <list>
#include <iostream>
#include <vector>
#include <limits>
#include "tipos.h"
#include "dijkstra_autofill.h"

#define INF numeric_limits<int>::max()

using namespace std;

class Ej1 {
	public:
		Ej1(int idOrigen, unsigned int cantEnlaces, vector<Enlace> &enlaces);
		~Ej1(){};
		double resolverPlanDeVuelos(int idDestino);
		void mostrarSolucion();
		string dameSolucion();

	private:
		void calcularSolucion(int idDestino);

		int idOrigen;
		unsigned int cantEnlaces;
		vector<Enlace> enlaces;
		
		string solucion;
		Dijkstra *dijkstra;
};

#endif