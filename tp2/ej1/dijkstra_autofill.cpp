#include "dijkstra_autofill.h"
#include <cstdlib>
//#include "io.h"


using namespace std;

Dijkstra::Dijkstra(unsigned int cantVertices, Vertice v, vector<Enlace> *enlaces){
	
	this->enlaces = enlaces;
	this->n = cantVertices;

	generarGrafoSinAristas();

	int *pi = new int[this->G.n];
	this->pre = new Vertice[G.n];
	
	// T : Vertices que no estan en la solucion todavia. a medida que avanza el algoritmo T va decrementando vertices.`
	list<Vertice> T;

	pi[v] = 0;
	
	for (Vertice i=0; i < cantVertices; i++){
		this->pre[i] = -1;
	}

	completarAristas(v, pi[v]);

	for (Vertice u=0; u < G.n; u++){
		if(u==v) continue;
		T.push_back(u);
		if(!G[v][u].completa){
			pi[u] = INF;
		} else {
			pi[u] = G[v][u].costo;
			this->pre[u] = v;
		}
	}
	
	while (!T.empty()){
		Vertice w;
		list<Vertice>::iterator it_w;
		double min = INF;

		for (list<Vertice>::iterator it = T.begin(); it != T.end(); ++it){
			Vertice u = *it;
			if (pi[u] < min){
				w = u;
				it_w = it;
				min = pi[u];
			}
		}

		if (min < INF)
			T.erase(it_w);
		else 
			break; 	
			// El algoritmo termina tambien en caso de que no se encuentren mas nodos que se conecten a los nodos de la solucion.
			// El grafo en este caso no es conexo.

		completarAristas(w, pi[w]);

		for (list<Vertice>::iterator it = T.begin(); it != T.end(); ++it){
			Vertice u = *it;
			if (G[w][u].completa){
				if (pi[u] > pi[w] + G[w][u].costo){
					pi[u] = pi[w] + G[w][u].costo;
					this->pre[u] = w;
				}
			}
		}
	}
}


Dijkstra::~Dijkstra(){
	for (Vertice u=0; u < this->n; u++){
		delete this->pre;
	}
}

void Dijkstra::generarGrafoSinAristas(){

	this->G.n = this->n;
	this->G.ady = new Arista*[this->G.n];

	for (unsigned int i = 0; i < this->G.n; ++i){
		this->G.ady[i] = new Arista[this->G.n];
		for (unsigned int y = 0; y < this->G.n; ++y){
			this->G.ady[i][y].completa = false;
			this->G.ady[i][y].costo = INF;
		}
	}
}


void Dijkstra::completarAristas(Vertice v, Horario horarioLlegada){

	for (list<Vuelo>::iterator it = (*this->enlaces)[v].vuelos.begin(); it != (*this->enlaces)[v].vuelos.end(); it++){
		Vuelo vuelo = *it;
		if (horarioLlegada + 2 <= vuelo.inicio || horarioLlegada == 0){

			G[v][vuelo.idEnlaceDestino].completa = true;
			//cout << "G[" << v << "][" << vuelo.idEnlaceDestino << "].completa <- true" << endl;


			int costo = vuelo.fin - horarioLlegada;
			if (costo < G[v][vuelo.idEnlaceDestino].costo){
				G[v][vuelo.idEnlaceDestino].id = vuelo.id;
				G[v][vuelo.idEnlaceDestino].costo = costo;
				//cout << "G[" << v << "][" << vuelo.idEnlaceDestino << "].id <-" << vuelo.id << endl;
				//cout << "G[" << v << "][" << vuelo.idEnlaceDestino << "].costo <-" << costo << endl;
			}
			//cout << endl;
		}

	}
}

int Dijkstra::dameCosto(Vertice v, Vertice u){
	return this->G[v][u].costo;
}

int Dijkstra::dameIdArista(Vertice v, Vertice u){
	return this->G[v][u].id;
}

Vertice Dijkstra::damePredecesor(Vertice v){
	return this->pre[v];
}
