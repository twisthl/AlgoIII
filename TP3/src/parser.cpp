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
	this->poda_habilitada = opt.poda_habilitada;
	this->max_iteraciones = opt.max_iteraciones;
	this->mostrar_info = opt.mostrar_info;
	this->silence = opt.silence;
	this->mejora2 = opt.mejora2;
}


void Parser::resolver(){

	// Se carga el archivo
	ifstream file(this->archivo_entrada);
	string line;
	if (this->silence == false)
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
			list<Particion> k_particion = exacto.dameKParticion();
			guardarPesoSolucion("EXACTO", cuantoPesa(k_particion));
			this->solucion = exacto.dameSolucion();
			break;
		}
		case GREED:{
			Greed greed(G, k, this->mostrar_info);
			time = greed.resolver();
			list<Particion> k_particion = greed.dameKParticion();
			guardarPesoSolucion("GREED", cuantoPesa(k_particion));
			this->solucion = greed.dameSolucion();
			break;
		}
		case BUSQUEDA_LOCAL:{
			Greed greed(G, k, false);
			time = greed.resolver();
			list<Particion> ini_k_particion = greed.dameKParticion();
			BusquedaLocal busquedaLocal(G, ini_k_particion, k, this->mejora2, this->mostrar_info);

			time += busquedaLocal.resolver();
			list<Particion> k_particion = busquedaLocal.dameKParticion();
			guardarPesoSolucion("BUSQUEDA", cuantoPesa(k_particion));
			this->solucion = busquedaLocal.dameSolucion();
			break;
		}
		case GRASP:{
			int iteraciones;
			int itSinCambios;
			if (max_iteraciones != -1){
				iteraciones = this->max_iteraciones;
				itSinCambios = this->max_iteraciones;
			}else{
				iteraciones = 20;
				itSinCambios = 6;
			}
			Grasp grasp(G, k, this->mostrar_info, 0.4, 3, iteraciones, itSinCambios);
			time = grasp.resolver();
			list<Particion> k_particion = grasp.dameKParticion();
			guardarPesoSolucion("GRASP"+to_string(iteraciones), cuantoPesa(k_particion));
			this->solucion = grasp.dameSolucion();
			break;
		}
		case PEOR_SOLUCION:{
			PeorSolucion peorSolucion(G, k, this->mostrar_info);
			time = peorSolucion.resolver();
			list<Particion> k_particion = peorSolucion.dameKParticion();
			guardarPesoSolucion("PEOR_SOLUCION", cuantoPesa(k_particion));
			this->solucion = peorSolucion.dameSolucion();
			break;
		}
		case RANDOM_SOLUCION:{
			RandomSolucion randomSolucion(G, k, this->mostrar_info);
			time = randomSolucion.resolver();
			list<Particion> k_particion = randomSolucion.dameKParticion();
			guardarPesoSolucion("RANDOM_SOLUCION", cuantoPesa(k_particion));
			this->solucion = randomSolucion.dameSolucion();
			break;
		}
	}

	guardarSolucion();
	guardarTiempoEjecucion(n, time);
	if (this->silence == false){
		cout << "Tiempo de ejecucion: " << endl;
		cout << time << " sec" << endl;
		cout << endl;
	}
	
	file.close();
}

	
void Parser::guardarPesoSolucion(string archivoPeso, double pesoSolucion){
	string path = "../recursos/comparando/" + archivoPeso;
	fstream output(path, ios::out | ios::app);
	output << pesoSolucion << endl;
	output.close();
}

void Parser::mostrarSolucion(){
	cout << "Solucion: ";
	for (int i = 0; i < this->solucion.size(); i++){
		cout << solucion[i] << " ";
	}
	cout << endl << endl;
}

void Parser::guardarSolucion(){
	if (this->archivo_salida.empty())
		this->archivo_salida = "../recursos/solucion";

	fstream output(this->archivo_salida, ios::out | ios::app);
	for (int i = 0; i < this->solucion.size(); i++){
		output << solucion[i] << " ";
	}
	output << endl;
	output.close();
}

void Parser::guardarTiempoEjecucion(int n, double time){
	string path = "../recursos/times";
	fstream output(path, ios::out | ios::app);
	output << time << endl;
	output.close();
}
