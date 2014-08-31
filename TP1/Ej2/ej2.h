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

using namespace std;

struct Edificio{
	Edificio(int x, int y, int z){
		comienzo = x;
		fin = y;
		altura = z;
	}
	int comienzo;
	int altura;
	int fin;
};

typedef std::vector<Edificio> Edificios;

typedef std::vector<int> Ciudad;

Ciudad* edificar(int cantEdificios, Edificios& edificios);

int imprimirCiudad(Ciudad& ciudad);


#endif