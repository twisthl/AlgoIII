#ifndef _EJ1PARSER_H_
#define _EJ1PARSER_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include "opciones.h"
#include "tipos.h"
#include "ej1.h"

using namespace std;

class Ej1Parser {
	public:
		Ej1Parser(Opciones opt);
		~Ej1Parser(){};
		void resolver();

	private:
		int obtainIdEnlace(vector<Enlace> &enlaces, string nombreEnlace);
		void guardarTiempoEjecucion(int n, double time);
		void guardarSolucion(string solucion);
		
		string archivo_entrada;
		string archivo_salida;
		bool mostrar_info;
};

#endif
