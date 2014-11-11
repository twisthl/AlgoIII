#include "tipos.h"

Vuelo::Vuelo(int id, int idEnlaceOrigen, int idEnlaceDestino, Horario inicio, Horario fin){
	this->id = id;
	this->idEnlaceOrigen = idEnlaceOrigen;
	this->idEnlaceDestino = idEnlaceDestino;
	this->inicio = inicio;
	this->fin = fin;
}

Enlace::Enlace(int id, string nombre){
	this->id = id;
	this->nombre = nombre;
}

Arista::Arista(){
	completa = false;
	id = -1;
	costo = 0;
}

Arista * Grafo::operator[](int i){ 
	return ady[i]; 
}
