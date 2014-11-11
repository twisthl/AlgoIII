#include "ej1.h"

Ej1::Ej1(int idOrigen, unsigned int cantEnlaces, vector<Enlace> &enlaces){

	this->idOrigen = idOrigen;
	this->cantEnlaces = cantEnlaces;
	this->enlaces = enlaces;
	this->dijkstra = NULL;

}

double Ej1::resolverPlanDeVuelos(int idDestino){
	timespec ts_beg, ts_end;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts_beg);


	// BEGIN BIOHAZARD
	if (this->dijkstra == NULL)
		this->dijkstra = new Dijkstra(this->cantEnlaces, this->idOrigen, &(this->enlaces));
	this->calcularSolucion(idDestino);
	this->mostrarSolucion();
	// END BIOHAZARD

	cout << "Tiempo de ejecucion: " << endl;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts_end);
	double time = (ts_end.tv_sec - ts_beg.tv_sec) + (ts_end.tv_nsec - ts_beg.tv_nsec) / 1e9;
	cout << time << " sec" << endl;
	cout << endl;

	return time;
}

void Ej1::calcularSolucion(int idDestino){

	list<int> vuelosTomados;
	int costoTotal = 0;
	Vertice vertice = idDestino;
	while (dijkstra->damePredecesor(vertice) != -1){
		Vertice predecesor = dijkstra->damePredecesor(vertice);
		vuelosTomados.push_front(this->dijkstra->dameIdArista(predecesor,vertice));
		costoTotal += this->dijkstra->dameCosto(predecesor,vertice);
		vertice = predecesor;
	}

	if (vertice == this->idOrigen){
		this->solucion = std::to_string(costoTotal) + " " + std::to_string(vuelosTomados.size());

		for (list<int>::iterator it = vuelosTomados.begin(); it != vuelosTomados.end(); it++){
			this->solucion += " " + std::to_string(*it);
		}
	}else{
		this->solucion = "no";
	}

}

void Ej1::mostrarSolucion(){
	cout << this->solucion << endl << endl;
};

string Ej1::dameSolucion(){
	return this->solucion;
}
	//Vertice origen = idOrigen;
	//Vertice destino = idDestino;