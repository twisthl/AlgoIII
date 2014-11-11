#ifndef _TIPOS_H_
#define _TIPOS_H_

#include <iostream>
#include <list>
#include <limits>
#include <vector>

using namespace std;

#define INF numeric_limits<int>::max()
#define INF_F numeric_limits<float>::max()
#define INF_D numeric_limits<double>::max()

typedef int Horario;
typedef int Vertice;

struct Vuelo{
	Vuelo(int id, int idEnlaceOrigen, int idEnlaceDestino, Horario inicio, Horario fin);
	int id;
	int idEnlaceOrigen, idEnlaceDestino;
	Horario inicio, fin;
};

struct Enlace{
	Enlace(int id, string nombre);
	int id;
	string nombre;
	list<Vuelo> vuelos;
};

struct Arista{
	Arista();
	bool completa;
	int id;
	int costo;
};

struct Grafo{
	Arista ** ady;
	unsigned int n; // |V| := cantidad de vértices 
	Arista * operator[](int);
};

#endif //_TIPOS_
