#ifndef _EJ3PARSER_H_
#define _EJ3PARSER_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include "opciones.h"
#include "ej3.h"

using namespace std;

class Ej3Parser {
	public:
		Ej3Parser(Opciones opt);
		~Ej3Parser(){};
		void resolver();

		void guardarTiempoEjecucion(int n, double time);
		void guardarSolucion(string solucion);


	private:
		string archivo_entrada;
		string archivo_salida;
		bool mostrar_info;
		bool poda_habilitada;
};

#endif
