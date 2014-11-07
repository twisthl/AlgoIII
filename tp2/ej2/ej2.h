ifndef EJ2_H
#define EJ2_H

#include <list>
#include <utility>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <fstream>
#include "vector"
#include "iterator"
#include <math.h>

using namespace std

typedef std::vector< vector<Nodo> > MatrizDeNodos;
typedef std::vector<Casillero> ListaAdyacencia;

typedef std::vector<Casillero> Caballos;


struct Casillero{
	Casillero(int a, int b){
		x = a;
		y = b;
	}
	int x;
	int y;
}

struct Nodo{
	Nodo(int x, int y){
		casillero = new Casillero(x,y);
		movimientosNecesarios = 0;
		caballosLlegaron = 0;
		adyacentes = new ListaAdyacencia;
	}
	Casillero casillero;
	int movimientosNecesarios;
	int caballosLlegaron;
	ListaAdyacencia adyacentes;
}

struct Solucion{
	Solucion(int a, int b, int c){
		x = a;
		y = b;
		movimientos = c;
	}
	int x;
	int y;
	int movimientos;
}

MatrizDeNodos modelar(int n);

int resolver(MatrizDeNodos matriz, Caballos caballos);


#endif