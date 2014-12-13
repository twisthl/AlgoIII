#ifndef _TIPOS_H_
#define _TIPOS_H_

#include <iostream>
#include <list>
#include <limits>
#include <vector>

using namespace std;

#define INF numeric_limits<int>::max()

typedef int Vertice;
typedef list<Vertice> particion;
typedef list<Particion> k_particion;

class Arista {
	public:
		Arista(Arista &arista);
		Arista(Vertice v, Vertice w);
		Arista(Vertice v, Vertice w, int peso);
		Vertice getVertice1();
		Vertice getVertice2();
		int getPeso();

	private:
		Vertice v;
		Vertice w;
		int peso;
};

class Grafo{
	public:
		Grafo(int n, list<Arista> aristas);
		Arista* getArista(Vertice v, Vertice w);
		Arista** getAristas(Vertice v);
		int getCantVertices();

	private:
		Arista *** ady;
		int n; // |V| := cantidad de vértices 
};

class Camino{
	public:
		Camino();
		Camino(list<Vertice> &vertices);
		list<Vertice>* getVerticesOrdenados();
		int getPeso();
		int getCantVertices();
		bool vacio();

	private:
		list<Vertice> *vertices;
		int peso;
};


struct Opciones{
	Opciones(int argc, char * argv[]);
	bool exacto; 	// -x --exacto 
	bool greed; // -g --greed;
	bool busqueda_local; // -bl --busquedaLocal
	bool grasp; //-gr --grasp
	bool clock; //-t --tiempo
};

#endif