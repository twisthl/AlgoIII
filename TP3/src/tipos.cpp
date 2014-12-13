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
    this->aristaList = new list<Arista*>;
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
		this->aristaList->push_back(pArista);
	}

}

Arista* Grafo::getArista(Vertice v, Vertice w){
	return this->ady[v][w];
}

Arista** Grafo::getAristas(Vertice v){
	return this->ady[v];
}

list<Arista*>* Grafo::getAristas(){
	return this->aristaList;
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


Particion::Particion(int nro){
	this->nro = nro;
	this->peso = 0;
	this->verticeX = -1;
}

int Particion::cuantoPesariaCon(Grafo &G, Vertice vertice){
	int pesaria = this->getPeso();
	for (list<Vertice>::iterator it = this->vertices.begin(); it != this->vertices.end(); it++){
		Arista* pArista =  G.getArista(vertice, *it);
		if (pArista != NULL) 
			pesaria += pArista->getPeso();
	}
	this->verticeX = vertice;
	this->pesoConVerticeX = pesaria;
	return pesaria;
}

int Particion::cuantoPesariaSin(Grafo &G, Vertice vertice){
	int pesaria = this->getPeso();
	for (list<Vertice>::iterator it = this->vertices.begin(); it != this->vertices.end(); it++){
		Arista* pArista =  G.getArista(vertice, *it);
		if (pArista != NULL) 
			pesaria -= pArista->getPeso();
	}
	return pesaria;
}

void Particion::agregar(Grafo &G, Vertice vertice){
	this->vertices.push_back(vertice);
	if (vertice == verticeX){
		peso = pesoConVerticeX;
	}else{
		this->peso = this->cuantoPesariaCon(G, vertice);
	}
	verticeX = -1;
}

void Particion::quitarUltimo(Grafo &G){
	Vertice vertice = this->vertices.back();
	int nuevoPeso = cuantoPesariaSin(G, vertice);
	this->quitarUltimoSinActualizarPeso();
	this->peso = nuevoPeso;
}

void Particion::quitarUltimoSinActualizarPeso(){
	this->vertices.pop_back();
	this->verticeX = -1;
}

int Particion::getNro(){
	return this->nro;
}

int Particion::getPeso(){
	return this->peso;
}

int Particion::setPeso(int peso){
	return this->peso = peso;
}