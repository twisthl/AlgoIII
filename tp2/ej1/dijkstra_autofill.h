#ifndef _DIJKSTRA_AUTOFILL_H_
#define _DIJKSTRA_AUTOFILL_H_

#include <list>
#include "tipos.h"

// REQUERIMIENTO, G debe ser conexo.
class Dijkstra {
	public:
		Dijkstra(unsigned int cantVertices, Vertice v, vector<Enlace> *enlaces);
		~Dijkstra();

		int dameCosto(Vertice v, Vertice u);
		int dameIdArista(Vertice v, Vertice u);
		Vertice damePredecesor(Vertice v);

	private:
		void generarGrafoSinAristas();
		void completarAristas(Vertice v, Horario horarioLlegada);

		int n;
		Grafo G;
		Vertice *pre;
		vector<Enlace> *enlaces;
};

#endif
