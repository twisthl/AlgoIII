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
		cout << "..recursos/output" << endl << endl;
		this->archivo_salida = "..recursos/output";
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
		int u;
		int v;
		double w;

		getline(file, line);
		istringstream iss(line);
		iss >> u;
		iss >> v;
		iss >> w;

		Arista arista(u-1, v-1, w);

		aristaList.push_back(arista);

		if (this->mostrar_info) cout << "e" << u  << v << ": " << w << endl;
	}
	if (this->mostrar_info) cout << endl;

	Grafo* G = new Grafo(n, aristaList);

	double time;
	switch (this->exercise){
		case EXACTO:{
			Exacto exacto(G, k, this->poda_habilitada, this->mostrar_info);
			time = exacto.resolver();
			this->solucion = exacto.dameSolucion();
			break;
		}
		case GREED:{
			Greed greed(G, k, this->mostrar_info);
			time = greed.resolver();
			this->solucion = greed.dameSolucion();
			break;
		}
		case BUSQUEDA_LOCAL:{
			Greed greed(G, k, false);
			time = greed.resolver();
			list<Particion> ini_k_particion = greed.dameKParticion();
			BusquedaLocal busquedaLocal(G, ini_k_particion, k, this->mostrar_info);
			time += busquedaLocal.resolver();
			this->solucion = busquedaLocal.dameSolucion();
			break;
		}
		case GRASP:{
			Grasp grasp(G, k, this->mostrar_info, 100, 0, 3);
			time = grasp.resolver();
			this->solucion = grasp.dameSolucion();
			break;
		}
	}

	guardarTiempoEjecucion(n, time);
	cout << "Tiempo de ejecucion: " << endl;
	cout << time << " sec" << endl;
	cout << endl;

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
	string path = "..recursos/times";
	fstream output(path, ios::out | ios::app);
	output << time << endl;
	output.close();
}
