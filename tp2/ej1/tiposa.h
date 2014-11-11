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

typedef int Vertice;
typedef double Costo;

struct Arista{
	Arista(){
		costo = 0;
	}
	bool completa;
	double costo;
};

struct Grafo{
	Arista ** ady;
	int n; // |V| := cantidad de vértices 
	Arista * operator[](int);
};

#endif //_TIPOS_
