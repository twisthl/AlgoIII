#include "tipos.h"
#include <string.h>

Arista::Arista(Arista &arista){
	this->v = arista.getVertice1();
	this->w = arista.getVertice2();
	this->peso = arista.getPeso();
}

Arista::Arista(Vertice v, Vertice w){
	this->v = v;
	this->w = w;
	this->peso = 0;
}

Arista::Arista(Vertice v, Vertice w, int peso){
	this->v = v;
	this->w = w;
	this->peso = peso;
}

Vertice Arista::getVertice1(){
	return this->v;
}

Vertice Arista::getVertice2(){
	return this->w;
}

int Arista::getPeso(){
	return this->peso;
}


Grafo::Grafo(int n, list<Arista> aristas){

    this->n = n;

    this->ady = new Arista**[n];
	for (int i = 0; i < n ; i++) {
		this->ady[i] = new Arista*[n];
		for (int j = 0; j < n; j++) {
			this->ady[i][j] = NULL;
		}
	}

	for (list<Arista>::iterator it = aristas.begin(); it != aristas.end(); it++){
		Arista* pArista = new Arista(*it);
		Vertice v = pArista->getVertice1();
		Vertice w = pArista->getVertice2();
		this->ady[v][w] = pArista;
		this->ady[w][v] = pArista;
	}

}

Arista* Grafo::getArista(Vertice v, Vertice w){
	return this->ady[v][w];
}

Arista** Grafo::getAristas(Vertice v){
	return this->ady[v];
}

int Grafo::getCantVertices(){
	return this->n;
}


Camino::Camino(){
	this->vertices = new list<Vertice>();
}

Camino::Camino(list<Vertice> &vertices){
	this->vertices = &vertices;
}

list<Vertice>* Camino::getVerticesOrdenados(){
	return this->vertices;
}

int Camino::getPeso(){
	return this->peso;
}

int Camino::getCantVertices(){
	return this->vertices->size();
}

bool Camino::vacio(){
	return this->vertices->empty();
}


Opciones::Opciones(int argc, char * argv[]){
	exacto = false;
	greed = false;
	busqueda_local = false;
	grasp = false;
	clock = false;
	
	for(int i = 0; i < argc; i++){
		
		if( !strcmp(argv[i], "-x") || !strcmp(argv[i], "--exacto") ){
			exacto = true;
		}
		else if( !strcmp(argv[i], "-g") || !strcmp(argv[i], "--greed") ){
			greed = true;
		}
		else if( !strcmp(argv[i], "-bl") || !strcmp(argv[i], "--busquedaLocal") ){
			busqueda_local = true;
		}
		else if( !strcmp(argv[i], "-gp") || !strcmp(argv[i], "--grasp") ){
			grasp = true;
		}
		if( !strcmp(argv[i], "-t") || !strcmp(argv[i], "--tiempo") ){
			clock = true;
		}

	}

}