#include "exacto.h"


Exacto::Exacto(Grafo *G, int k, bool podaHabilitada, bool mostrarInfo){
	
	this->G = G;
	this->k = k;
	this->podaHabilitada = podaHabilitada;
	this->mostrarInfo = mostrarInfo;

}

vector<int> Exacto::resolver(){

	// BEGIN EXACTO
	vector<int> ubicacion;
	for (int i = 0; i < G->getCantVertices(); i++){
		ubicacion.push_back(-1);
	} 

	list<Particion> k_particion;

	Vertice primerVertice = 0;
	Particion particionNueva(0);
	particionNueva.agregar(*G, primerVertice);
	k_particion.push_back(particionNueva);

	ubicacion[primerVertice] = particionNueva.getNro();

	this->mejorPeso = INF;

	this->combinar(k_particion, primerVertice+1, ubicacion, 0);

	return this->mejorUbicacion;
	// END EXACTO

}

void Exacto::combinar(list<Particion> &k_particion, Vertice verticeAUbicar, vector<int> &ubicacion, int pesoAcumulado){

	//Lo siguiente equipara a decir: Si no hay mas quimicos para cargar..
	if (verticeAUbicar == G->getCantVertices()) {
		if (pesoAcumulado < this->mejorPeso){
			this->mejorPeso = pesoAcumulado;
			this->mejorUbicacion = ubicacion;
			if (mostrarInfo) mostrarPotencialSolucion(this->mejorUbicacion);
		}
		return;
	}

	list<Particion>::iterator itParticion;
	for (itParticion = k_particion.begin(); itParticion != k_particion.end(); itParticion++){

		int pesoOld = itParticion->getPeso();
		int pesoNew = itParticion->cuantoPesariaCon((*this->G), verticeAUbicar);
		int difPeso = pesoNew - pesoOld;

		if (!podaHabilitada || (this->mejorPeso > pesoAcumulado+difPeso)) {

			// 'agregar' no vuelve a calcular el peso. Ya lo calcul'o en cuantoPesariaCon donde se cachea.
			itParticion->agregar((*this->G), verticeAUbicar);

			pesoAcumulado += difPeso;

			ubicacion[verticeAUbicar] = itParticion->getNro();

			combinar(k_particion, verticeAUbicar+1, ubicacion, pesoAcumulado);
			ubicacion[verticeAUbicar] = -1;

			pesoAcumulado -= difPeso;

			itParticion->quitarUltimoSinActualizarPeso();
			itParticion->setPeso(pesoOld);
		}
	}
	

	// Si hay menos de k particiones el vertice se puede ubicar en una particion nueva.
	if (k_particion.size() < k) {
		Particion particionNueva(k_particion.size());
		particionNueva.agregar((*this->G), verticeAUbicar);
		k_particion.push_back(particionNueva);
		ubicacion[verticeAUbicar] = particionNueva.getNro();
		//No hace falta fijarse que pesoAcumulado sea menor a mejorPeso porque el pesoAcumulado no se modifica al hacer una particion nueva sin aristas.
		combinar(k_particion, verticeAUbicar+1, ubicacion, pesoAcumulado);
		ubicacion[verticeAUbicar] = -1;
		k_particion.pop_back();
	}

}

void Exacto::mostrarPotencialSolucion(vector<int> &ubicacion){
	cout << "Potencial Solucion: ";
	for (int i = 0; i < ubicacion.size(); i++){
		cout << ubicacion[i] << " ";
	}
	cout << endl << endl;
}

vector<int> Exacto::dameSolucion(){
	return this->mejorUbicacion;
}


