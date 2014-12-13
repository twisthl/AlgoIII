#include "exacto.h"


void mostrarPotencialSolucion(vector<int> &ubicacion){
	cout << "Potencial Solucion: ";
	for (int i = 0; i < ubicacion.size(); i++){
		cout << ubicacion[i] << " ";
	}
	cout << endl << endl;
}


void combinar(Grafo &G, int k, list<Particion> &k_particion, Vertice verticeAUbicar, vector<int> &ubicacion, 
	vector<int> &mejorUbicacion, int &pesoAcumulado, int &mejorPeso, bool podaHabilitada, bool mostrarInfo){

	//Lo siguiente equipara a decir: Si no hay mas quimicos para cargar..
	if (verticeAUbicar == G.getCantVertices()) {
		if (pesoAcumulado < mejorPeso){
			mejorPeso = pesoAcumulado;
			mejorUbicacion = ubicacion;
			if (mostrarInfo) mostrarPotencialSolucion(mejorUbicacion);
		}
		return;
	}

	list<Particion>::iterator itParticion;
	for (itParticion = k_particion.begin(); itParticion != k_particion.end(); itParticion++){

		int pesoOld = itParticion->getPeso();
		int pesoNew = itParticion->cuantoPesariaCon(G, verticeAUbicar);
		int difPeso = pesoNew - pesoOld;

		if (!podaHabilitada || (mejorPeso > pesoAcumulado+difPeso)) {

			// 'agregar' no vuelve a calcular el peso. Ya lo calcul'o en cuantoPesariaCon donde se cachea.
			itParticion->agregar(G, verticeAUbicar);

			pesoAcumulado += difPeso;

			ubicacion[verticeAUbicar] = itParticion->getNro();

			combinar(G, k, k_particion, verticeAUbicar+1, ubicacion, mejorUbicacion, pesoAcumulado, mejorPeso, podaHabilitada, mostrarInfo);
			ubicacion[verticeAUbicar] = -1;

			pesoAcumulado -= difPeso;

			itParticion->quitarUltimoSinActualizarPeso();
			itParticion->setPeso(pesoOld);
		}
	}
	

	// Si hay menos de k particiones el vertice se puede ubicar en una particion nueva.
	if (k_particion.size() < k) {
		Particion particionNueva(k_particion.size());
		particionNueva.agregar(G, verticeAUbicar);
		k_particion.push_back(particionNueva);
		ubicacion[verticeAUbicar] = particionNueva.getNro();
		//No hace falta fijarse que pesoAcumulado sea menor a mejorPeso porque el pesoAcumulado no se modifica al hacer una particion nueva sin aristas.
		combinar(G, k, k_particion, verticeAUbicar+1, ubicacion, mejorUbicacion, pesoAcumulado, mejorPeso, podaHabilitada, mostrarInfo);
		ubicacion[verticeAUbicar] = -1;
		k_particion.pop_back();
	}

}

vector<int> exacto(Grafo &G, int k, bool podaHabilitada, bool mostrarInfo){
	
	// BEGIN EXACTO
	vector<int> ubicacion;
	for (int i = 0; i < G.getCantVertices(); i++){
		ubicacion.push_back(-1);
	} 

	list<Particion> k_particion;

	Vertice primerVertice = 0;
	Particion particionNueva(0);
	particionNueva.agregar(G, primerVertice);
	k_particion.push_back(particionNueva);

	ubicacion[primerVertice] = particionNueva.getNro();

	int pesoAcumulado = 0;
	int mejorPeso = INF;
	vector<int> mejorUbicacion;

	combinar(G, k, k_particion, primerVertice+1, ubicacion, mejorUbicacion, pesoAcumulado, mejorPeso, podaHabilitada, mostrarInfo);

	return mejorUbicacion;
	// END EXACTO

}