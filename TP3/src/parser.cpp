#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdio.h>
#include "parser.h"

using namespace std;
typedef int Vertice;

Parser::Parser(Opciones opt){

	this->exercise = opt.exercise;
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

}


void Parser::resolver(){

	// Se carga el archivo
	ifstream file(this->archivo_entrada);
	string line;
	cout << "# Carga archivo : " << this->archivo_entrada << endl << endl;

	int n;
	int m;
	int k;

	getline(file, line);
	istringstream iss(line);
	iss >> n;
	iss >> m;
	iss >> k;

	if (this->mostrar_info) cout << "n: " << n << " m: " << m << " k: " << k << endl;

	list<Arista> aristaList;
	for (int i=0; i < m; i++){

		for (Vertice i = 0; i < n-1; ++i){
			getline(file, line);
			istringstream iss(line);
			for (int j = i+1; j < n; j++){
				int peso;
				iss >> peso;
				Arista arista(i, j, peso);

				if (this->mostrar_info) cout << "e" << i  << j << ": " <<peso << ";  ";
			}
			if (this->mostrar_info) cout << endl;
		}
		if (this->mostrar_info) cout << endl;
	}

	Grafo* G = new Grafo(n, aristaList);
	switch (this->exercise){
		case EXACTO:{
			Exacto exacto(G, k, this->poda_habilitada, this->mostrar_info);
			this->solucion = exacto.resolver();
			break;
		}
		case GREED:{
			//Greed greed(G, k, this->mostrar_info);
			//vector<int> solucion = greed.resolver();
			break;
		}
		case BUSQUEDA_LOCAL:{
			//BusquedaLocal busquedaLocal(G, k, this->mostrar_info);
			//vector<int> solucion = busquedaLocal.resolver();
			break;
		}
		case GRASP:{
			//Grasp grasp(G, k, this->mostrar_info);
			//vector<int> solucion = grasp.resolver();
			break;
		}
	}

	file.close();
}

	

void Parser::mostrarSolucion(){
	cout << "Solucion: ";
	for (int i = 0; i < this->solucion.size(); i++){
		cout << solucion[i] << " ";
	}
	cout << endl << endl;
}

void Parser::guardarTiempoEjecucion(int n, double time){
	string path = "recursos/times";
	fstream output(path, ios::out | ios::app);
	output << time << endl;
	output.close();
}
