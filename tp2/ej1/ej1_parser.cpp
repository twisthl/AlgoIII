#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdio.h>
#include "ej1_parser.h"

using namespace std;

Ej1Parser::Ej1Parser(Opciones opt){

	this->archivo_entrada = opt.archivo_entrada;
	this->archivo_salida = opt.archivo_salida;
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


void Ej1Parser::resolver(){

	// Se carga el archivo
	ifstream file(this->archivo_entrada);
	string line;
	cout << "# Carga archivo : " << this->archivo_entrada << endl << endl;

	vector<Enlace> enlaces;

	string A;
	string B;
	int n;

	getline(file, line);
	istringstream iss(line);
	iss >> A;
	iss >> B;
	iss >> n;

	obtainIdEnlace(enlaces, A);
	obtainIdEnlace(enlaces, B);

	for (int i=0; i < n; i++){
		getline(file, line);
		istringstream iss(line);

		string ori, des;
		Horario ini, fin;

		iss >> ori;
		iss >> des;
		iss >> ini;
		iss >> fin;

		int idOri = obtainIdEnlace(enlaces, ori);
		int idDes = obtainIdEnlace(enlaces, des);

		Vuelo nuevoVuelo(i+1, idOri, idDes, ini, fin);
		enlaces[idOri].vuelos.push_back(nuevoVuelo);
	}

	unsigned int cantEnlaces = enlaces.size();

	if (this->mostrar_info){
		for (unsigned int i=0; i < cantEnlaces; i++){
			cout << enlaces[i].nombre << ":" << endl;

			bool hayVuelos = false;
			for (list<Vuelo>::iterator it = enlaces[i].vuelos.begin(); it != enlaces[i].vuelos.end(); it++){
				hayVuelos = true;
				Vuelo vuelo = *it;
				cout << " hacia " << enlaces[vuelo.idEnlaceDestino].nombre << " de " << vuelo.inicio << " a " << vuelo.fin << endl;
			}

			if (!hayVuelos) cout << " No posee vuelos disponibles";
			cout << endl;
		}
	}


	Ej1 ej1 = Ej1(0, cantEnlaces, enlaces);
	double time = ej1.resolverPlanDeVuelos(1);
	ej1.mostrarSolucion();
		
	guardarTiempoEjecucion(n, time);
	guardarSolucion(ej1.dameSolucion());

	file.close();
}

int Ej1Parser::obtainIdEnlace(vector<Enlace> &enlaces, string nombreEnlace){

	int idEnlace = -1;

	for (unsigned int i=0; i < enlaces.size(); i++){
		if (nombreEnlace.compare(enlaces[i].nombre) == 0){
			idEnlace = i;
			break;
		}
	}
	if (idEnlace == -1) {
		idEnlace = enlaces.size();
		Enlace nuevoEnlace(idEnlace, nombreEnlace);
		enlaces.push_back(nuevoEnlace);
	}

	return idEnlace;
}


void Ej1Parser::guardarSolucion(string solucion){
	fstream output(archivo_salida, ios::out | ios::app);
	output << solucion << endl;
	output.close();
}

void Ej1Parser::guardarTiempoEjecucion(int n, double time){
	string path = "recursos/times";
	fstream output(path, ios::out | ios::app);
	output << time << endl;
	output.close();
}
