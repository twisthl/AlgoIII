#ifndef EJ2_H
#define EJ2_H

#include <list>
#include <utility>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <fstream>
#include "vector"
#include "iterator"
#include <queue>
#include <list>
#include <math.h>

using namespace std;

struct Casillero{
	Casillero(int a, int b){
		x = a;
		y = b;
	};
	Casillero(){};
	int x;
	int y;
};

typedef std::list<Casillero> ListaAdyacencia;
typedef std::vector<Casillero> Caballos;

struct Nodo{
	Nodo(){
		movimientosNecesarios = -1;
	};
	Nodo(int a, int b){
		x = a;
		y = b;
		movimientosNecesarios = 0;
		caballosLlegaron = 0;
		distancia = 0;
	}
	int x;
	int y;
	int movimientosNecesarios;
	int caballosLlegaron;
	ListaAdyacencia adyacentes;
	int distancia;
};

typedef std::vector< vector<Nodo*> > MatrizDeNodos;

struct Solucion{
	Solucion(int a, int b, int c){
		x = a;
		y = b;
		movimientos = c;
	}
	int x;
	int y;
	int movimientos;
};


MatrizDeNodos* modelar(int n);

Nodo resolver(MatrizDeNodos& matriz, int n, Caballos& caballos, int k);

void bfs(MatrizDeNodos& matriz, int n, Casillero& c);

#endif