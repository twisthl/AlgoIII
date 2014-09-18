#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "ej3_parser.h"

using namespace std;

void Ej3Parser::cargar(string path){

	// Se carga el archivo
	ifstream file(path);
	string line;
	cout << "# Carga archivo : " << path << endl << endl;

	// Primera Linea: n M
	while(getline(file, line)){
		if(line.find("#") != line.npos || line.empty()) continue;

		istringstream iss(line);
		iss >> this->n;
		iss >> this->M;

		cout << "n: " << this->n << " M: " << this->M  << endl;

		break;
	}


	vector<int> aux(this->n, 0);
    this->peligrosidad.resize(this->n, aux);

	//this->peligrosidad.resize(this->n);
	//for (int i=0; i <= n; i ++){
	//	this->peligrosidad[i].resize(this->n, 0);
	//}

	// Datos
	int i = 0;
	while(getline(file, line)){
		if(line.find("#") != line.npos || line.empty()) continue;

		istringstream iss(line);

		for (int j = i+1; j < this->n; j++){
			iss >> this->peligrosidad[i][j];
			this->peligrosidad[j][i] = this->peligrosidad[i][j];
			cout << "h" << i  << j << ": " <<this->peligrosidad[i][j] << ";  ";
		}
		i++;
		cout << endl;
	}
	cout << endl;

	//// Se cierra el archivo
	file.close();
}

void Ej3Parser::guardarTiempoEjecucion(int n, double time){
	if (archivo_salida.empty()){
		cout << "No se especificó archivo de salida, se usa: " << endl;
		cout << "../recursos/ej3/output" << endl << endl;
	}
	archivo_salida = "../recursos/ej3/output";
	fstream output(archivo_salida, ios::out | ios::app);
	output << n << " " << time << endl;
	output.close();
}
