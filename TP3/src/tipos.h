#ifndef _TIPOS_H_
#define _TIPOS_H_

#include <iostream>
#include <list>
#include <limits>
#include <vector>
#include "clock.h"

using namespace std;

#define INF numeric_limits<int>::max()

typedef int Vertice;

class Arista {
	public:
		Arista(Vertice v, Vertice w);
		Arista(Vertice v, Vertice w, double peso);
		Vertice getVertice1();
		Vertice getVertice2();
		double getPeso();

	private:
		Vertice v;
		Vertice w;
		double peso;
};

class Grafo{
	public:
		Grafo(int n, list<Arista> aristas);
		Arista* getArista(Vertice v, Vertice w);
		Arista** getAristas(Vertice v);
		list<Arista*>* getAristas();
		int getCantVertices();

	private:
		Arista *** ady;
		list<Arista*>* aristaList;
		int n; // |V| := cantidad de vértices 
};

class Camino{
	public:
		Camino();
		Camino(list<Vertice> &vertices);
		list<Vertice>* getVerticesOrdenados();
		double getPeso();
		int getCantVertices();
		bool vacio();

	private:
		list<Vertice> *vertices;
		double peso;
};

class Particion{
	public:
		Particion(int nro);
		double cuantoPesariaCon(Grafo *G, Vertice vertice);
		double cuantoPesariaSin(Grafo *G, Vertice vertice);
		void agregar(Grafo *G, Vertice vertice);
		void agregarSinActualizarPeso(Vertice vertice);
		void quitar(Grafo *G, Vertice vertice);
		void quitarUltimo(Grafo *G);
		void quitarUltimoSinActualizarPeso();
		int getNro();
		double getPeso();
		void setPeso(double peso);
		list<Vertice> getVertices();

	private:
		int nro;
		list<Vertice> vertices;
		double peso;
		double pesoConVerticeX;
		Vertice verticeX;
};

vector<int> toUbicacion(int cantVertices, list<Particion> &k_particion);
double cuantoPesa(list<Particion> &k_particion);

#endif