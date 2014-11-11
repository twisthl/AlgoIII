#ifndef EJ3_H
#define EJ3_H

#include <list>
#include <utility>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <fstream>
#include "vector"
#include "iterator"
#include <math.h>

using namespace std;

struct Enlace {
		int compu1;
		int compu2;
		int costo;
};


typedef std::vector< vector<int> > MatrizAdyacencia;
typedef std::vector<Enlace> Red;
typedef std::vector< vector<int> > ListaAdyacencia;

/*struct Vertice{
	bool visitado;
	int distancia = INFINITY;
	Vertice predecesor;
};
*/
void resolver(int cantCompus, int cantEnlaces, Red& red);

bool esMayorEnlace(const Enlace& a, const Enlace& b);

MatrizAdyacencia kruskal(int cantCompus, int cantTotalAristas, Red& red, Enlace& menorEnlaceExcluido, ListaAdyacencia& agmL, int* costoTotal);

void imprimirResultado(int costoTotal, int cantEnlacesEnCamino, int cantEnlacesFuera, Red anilloServidores, Red compusEnRed);

vector<int> bfs(ListaAdyacencia agm, int desde, int cantAristas);

void obtenerServidoresYRed(Red& anilloServidores, Red& compusEnRed, vector<int> conexionesAnillo, int desde, int hasta);

// class RedAnillo{

// 	private:
// 		int costoTotal;
// 		int cantEnlacesEnAnillo;
// 		int cantEnlacesFuera;
// 		std::vector<Enlace> enlacesEnAnillo;
// 		std::vector<Enlace> enlacesFuera;

// 	public:
// 		RedAnillo();
// 		~RedAnillo();

// 		/* data */
// };


#endif