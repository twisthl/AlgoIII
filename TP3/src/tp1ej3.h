/* Resolucion del ejercicio 3*/
#ifndef _EJ3_H_
#define _EJ3_H_

#include <list>
#include <iostream>
#include <vector>
#include <limits>
#include "ej3_parser.h"


typedef int Quimico;
//typedef int Camion;

#define INF numeric_limits<int>::max()

using namespace std;

class Ej3 {
	public:
		Ej3(int n, int M, vector<vector<int> > peligrosidad, bool podaHabilitada = true, bool mostrarInfo = true);
		~Ej3(){};
		double resolverBiohazard();
		void mostrarSolucion();
		string dameSolucion();

	private:

		struct Camion{
			Camion(unsigned int nro, Quimico quimico){
				this->nro = nro;
				this->peligrosidad = 0;
				this->quimicos.push_back(quimico);
			}
			unsigned int nro;
			list<Quimico> quimicos;
			int peligrosidad;
		};

		//void combinar(Camion camion, Quimico ultimaCarga, int peligrosidad, vector<Camion> &carga, int noCargados);
		void combinar2(list<Camion> &camiones, Quimico quimicoACargar, vector<unsigned int> &carga);
		//int calcularPeligrosidadAgregada(vector<Camion> &carga, Camion camion, Quimico quimicoA);
		int calcularPeligrosidadAgregada(Camion &camion, Quimico quimico);
		void mostrarSolucion(vector<unsigned int> &carga, unsigned int cantCamiones);

		int n;
		int M;
		vector<vector<int> > peligrosidad;
		vector<unsigned int> cargaMinima;
		unsigned int minCamiones;
		bool podaHabilitada;
		bool mostrarInfo;
};

#endif