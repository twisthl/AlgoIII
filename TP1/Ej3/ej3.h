/* Resolucion del ejercicio 3*/
#ifndef _EJ3_H_
#define _EJ3_H_

#include <list>
#include <iostream>
#include <vector>
#include <limits>
#include "ej3_parser.h"
#include "opciones.h"


typedef int Quimico;
typedef int Camion;

#define INF numeric_limits<int>::max()

using namespace std;

class Ej3 {
	public:
		Ej3(Opciones opt);
		~Ej3(){};
		void resolverBiohazard();
		void mostrarMejorSolucion();

	private:
		Ej3Parser parser;

		int n;
		int M;
		vector<vector<int> > peligrosidad;
		vector<Camion> cargaMinima;
		int minCamiones;

		void combinar(Camion camion, Quimico ultimaCarga, int peligrosidad, vector<Camion> &carga, int noCargados);
		int calcularPeligrosidadAgregada(vector<Camion> &carga, Camion camion, Quimico quimicoA);
		void mostrarSolucion(vector<Camion> &carga, int cantCamiones);
};

#endif