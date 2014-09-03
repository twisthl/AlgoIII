#ifndef _EJ3PARSER_H_
#define _EJ3PARSER_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>

using namespace std;

class Ej3Parser {
	public:
		Ej3Parser();
		~Ej3Parser(){}
		void cargar(string path);
		int getN(){return this->n;}
		int getM(){return this->M;}
		vector<vector<int> > getPeligrosidad(){return this->peligrosidad;}

		void setOutputFile(string archivo){archivo_salida = archivo;}
		void guardarTiempoEjecucion(int n, double time);

	private:
		int n;
		int M;
		vector<vector<int> > peligrosidad;
		string archivo_salida;
};

#endif
