#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdio.h>
#include "ej3_parser.h"

using namespace std;

Ej3Parser::Ej3Parser(Opciones opt){

	this->archivo_entrada = opt.archivo_entrada;
	this->archivo_salida = opt.archivo_salida;
	this->poda_habilitada = opt.poda_habilitada;
	this->mostrar_info = opt.mostrar_info;

	if (this->archivo_salida.empty()){
		cout << "No se especificó archivo de salida, se usa: " << endl;
		cout << "recursos/output" << endl << endl;
		this->archivo_salida = "recursos/output";
	}

	fstream output(archivo_salida, ios::trunc);

	/*if( remove( archivo_salida.c_str() ) != 0 )
    	cout << "Error deleting file" << endl;
  	else
    	cout <<  "File successfully deleted" << endl;*/

}


void Ej3Parser::resolver(){

	// Se carga el archivo
	ifstream file(this->archivo_entrada);
	string line;
	cout << "# Carga archivo : " << this->archivo_entrada << endl << endl;

	int n;
	int M;

	getline(file, line);
	istringstream iss(line);
	iss >> n;

	while (n != 0){
		iss >> M;
		if (this->mostrar_info) cout << "n: " << n << " M: " << M  << endl;

		vector<int> aux(n, 0);
    	vector<vector<int> > peligrosidad(n, aux);

		for (int i = 0; i < n-1; ++i){
			getline(file, line);
			istringstream iss(line);
			for (int j = i+1; j < n; j++){
				iss >> peligrosidad[i][j];
				peligrosidad[j][i] = peligrosidad[i][j];
				if (this->mostrar_info) cout << "h" << i  << j << ": " <<peligrosidad[i][j] << ";  ";
			}
			if (this->mostrar_info) cout << endl;
		}
		if (this->mostrar_info) cout << endl;

		Ej3 ej3 = Ej3(n, M, peligrosidad, this->poda_habilitada, this->mostrar_info);
		double time = ej3.resolverBiohazard();
		ej3.mostrarSolucion();
		
		guardarTiempoEjecucion(n, time);
		guardarSolucion(ej3.dameSolucion());

		getline(file, line);
		istringstream iss(line);
		iss >> n;
	}

	file.close();
}

void Ej3Parser::guardarSolucion(string solucion){
	fstream output(archivo_salida, ios::out | ios::app);
	output << solucion << endl;
	output.close();
}

void Ej3Parser::guardarTiempoEjecucion(int n, double time){
	string path = "recursos/timeOutput";
	fstream output(path, ios::out | ios::app);
	output << n << " " << time << endl;
	output.close();
}
