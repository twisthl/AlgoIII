#ifndef _PARSER_H_
#define _PARSER_H_

#include "tipos.h"
#include "opciones.h"
#include "exacto.h"
#include "greed.h"
#include "busqueda_local.h"
#include "grasp.h"
#include "peorSolucion.h"
#include "randomSolucion.h"

using namespace std;


class Parser {
	public:
		Parser(Opciones opt);
		~Parser(){};
		void resolver();
		void guardarTiempoEjecucion(int n, double time);
		void mostrarSolucion();

	private:
		void guardarSolucion();
		void guardarPesoSolucion(string archivoPeso, double pesoSolucion);

		int exercise;
		vector<int> solucion;
		string archivo_entrada;
		string archivo_salida;
		int max_iteraciones;
		bool poda_habilitada;
		bool mostrar_info;
		bool silence;
};

#endif
