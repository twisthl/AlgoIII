#include "tipos.h"
#include <string.h>

Arista::Arista(Vertice v, Vertice w){
	this->v = v;
	this->w = w;
	this->peso = 0;
}

Arista::Arista(Vertice v, Vertice w, double peso){
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

double Arista::getPeso(){
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

Arista* Grafo::getArista(Vertice v, Vertice w){vector<Particion> k_particion;
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

double Camino::getPeso(){
	return this->peso;
}

int Camino::getCantVertices(){
	return this->vertices->size();
}

bool Camino::vacio(){
	return this->vertices->empty();
}

Particion::Particion(int nro){
	this->nro = nro;
	this->peso = 0.0;
	this->verticeX = -1;
}

double Particion::cuantoPesariaCon(Grafo *G, Vertice vertice){
	double pesaria = this->getPeso();
	for (list<Vertice>::iterator it = this->vertices.begin(); it != this->vertices.end(); it++){
		Arista* pArista =  G->getArista(vertice, *it);
		if (pArista != NULL) 
			pesaria += pArista->getPeso();
	}
	this->verticeX = vertice;
	this->pesoConVerticeX = pesaria;
	return pesaria;
}

double Particion::cuantoPesariaSin(Grafo *G, Vertice vertice){
	double pesaria = this->getPeso();
	for (list<Vertice>::iterator it = this->vertices.begin(); it != this->vertices.end(); it++){
		Arista* pArista =  G->getArista(vertice, *it);
		if (pArista != NULL) 
			pesaria -= pArista->getPeso();
	}
	return pesaria;
}

double Particion::cuantoPesariaSwaping(Grafo *G, Vertice verticeMetido, Vertice verticeSacado){
	double pesaria = this->cuantoPesariaSin(G, verticeSacado);
	for (list<Vertice>::iterator it = this->vertices.begin(); it != this->vertices.end(); it++){
		if (*it != verticeSacado){
			Arista* pArista =  G->getArista(verticeMetido, *it);
			if (pArista != NULL) 
				pesaria += pArista->getPeso();
		}
	}
	return pesaria;
}

void Particion::agregar(Grafo *G, Vertice vertice){
	if (vertice == verticeX){
		this->peso = pesoConVerticeX;
	}else{
		this->peso = this->cuantoPesariaCon(G, vertice);
	}
	agregarSinActualizarPeso(vertice);
}

void Particion::agregarSinActualizarPeso(Vertice vertice){
	this->vertices.push_back(vertice);
	this->verticeX = -1;
}

void Particion::quitar(Grafo *G, Vertice vertice){
	double nuevoPeso = cuantoPesariaSin(G, vertice);
	this->vertices.remove(vertice);
	this->peso = nuevoPeso;
}

void Particion::quitarUltimo(Grafo *G){
	Vertice vertice = this->vertices.back();
	double nuevoPeso = cuantoPesariaSin(G, vertice);
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

double Particion::getPeso(){
	return this->peso;
}

void Particion::setPeso(double peso){
	this->peso = peso;
}

list<Vertice> Particion::getVertices(){
	return this->vertices;
}

vector<int> toUbicacion(int cantVertices, list<Particion> &k_particion){
	vector<int> ubicacion(cantVertices);
	list<Particion>::iterator itParticion;
	for (itParticion = k_particion.begin(); itParticion != k_particion.end(); itParticion++){
		list<Vertice> vertices = itParticion->getVertices();
		for (list<Vertice>::iterator it = vertices.begin(); it != vertices.end(); it++){
			Vertice vertice = *it;
			ubicacion[vertice] = itParticion->getNro();
		}
	}
	return ubicacion;
}

double cuantoPesa(list<Particion> &k_particion){
	double peso = 0.0;
	list<Particion>::iterator itParticion;
	for (itParticion = k_particion.begin(); itParticion != k_particion.end(); itParticion++){
		//cout << "peso particion " << itParticion->getNro() << " = " << itParticion->getPeso() << endl;
		peso += itParticion->getPeso();
	}
	return peso;
}