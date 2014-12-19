#ifndef _PARSER_H_
#define _PARSER_H_

#include "tipos.h"
#include "opciones.h"
#include "exacto.h"
#include "greed.h"
#include "busqueda_local.h"
#include "grasp.h"
#include "peorSolucion.h"

using namespace std;


class Parser {
	public:
		Parser(Opciones opt);
		~Parser(){};
		void resolver();
		void guardarTiempoEjecucion(int n, double time);
		void mostrarSolucion();

	private:
		void guardarPesoSolucion(string archivoPeso, double pesoSolucion);

		int exercise;
		vector<int> solucion;
		string archivo_entrada;
		string archivo_salida;
		bool mostrar_info;
		bool poda_habilitada;
};

#endif
