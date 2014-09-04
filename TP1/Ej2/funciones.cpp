#include "ej2.h"

#typdef std::map<int,int> MapAlturas;

struct PuntoCritico{
	PuntoCritico(bool s, Edificio& e){
		sube = s;
		edificio = &e;
		altura = edificio->altura;
		if (s){
			posicion = edificio->comienzo;
		} else {
			posicion = edificio->fin;
		}

	}
	bool sube;
	int altura, posicion;
	Edificio *edificio;
};

struct orden_PuntoCritico{
	bool operator()(const PuntoCritico& a, const PuntoCritico& b) const{
		if(a.posicion == b.posicion){
			if (a.sube == b.sube){
				return a.altura > b.altura;
			} else {
				return a.sube > b.sube;
			}
		} else {
			return a.posicion > b.posicion;
		}
	};
};

// Mi igual entre PuntosCriticos es si comparten la posicion y si son la misma pared...
// La altura la analizo en el algoritmo
bool operator==(PuntoCritico & a,PuntoCritico & b){
	return a.posicion == b.posicion && a.sube == b.sube;
}

Ciudad* edificar(int cantEdificios, Edificios& edificios){

	/*
	Desdoblar la informacion para tener los puntos criticos a analizar.
	*/

	//Inicializo un vector del doble de tamanio
	std::vector<PuntoCritico> puntos(2*cantEdificios);

	//Recorrer los edificios para definir los PuntosCriticos a analizar
	Edificios::iterator itEdificios = edificios.begin();
	for(;itEdificios!=edificios.end();++itEdificios){
		Edificio edificio = *itEdificios;
	
		PuntoCritico pc = new PuntoCritico(true,edificio);
		puntos.push_back(pc);

		pc = new PuntoCritico(false,edificio);
		puntos.push_back(pc);
	}

	//Ordenar los puntos criticos para luego analizar en orden realizando una barrida lineal
	orden_PuntoCritico ord_functor;
	sort(puntos.begin(), puntos.end(), ord_functor);

	//Recorrer los puntos criticos en orden e ir generando la salida.
	Ciudad* ciudad = new Ciudad();
	
	int nivelActual = 0;
	MapAlturas edificiosAbiertos;

	std::vector<PuntoCritico>::iterator itPuntos = puntos.begin();
	for(;itPuntos!=puntos.end();++itPuntos){
		if (itPuntos->sube){
			//agregar al mapa el edificio abierto
			edificiosAbiertos.insert(make_pair(itPuntos->altura,itPuntos->altura));
			std::vector<PuntoCritico>::iterator itCopy = itPuntos;
 			if(*(++itCopy) == *itPuntos){
				continue;
			} else {
			
			}
		} else {
			//Sacar del mapa el edificio
		}

	}

	
	Ciudad* ciudad2 = new Ciudad();
	ciudad2->push_back(9);
	ciudad2->push_back(8);
	ciudad2->push_back(7);
	ciudad2->push_back(6);
	ciudad2->push_back(5);
	ciudad2->push_back(4);
	ciudad2->push_back(3);
	ciudad2->push_back(2);
	ciudad2->push_back(1);
	ciudad2->push_back(0);

	return ciudad2;
}

int imprimirCiudad(Ciudad& ciudad){

	Ciudad::iterator it = ciudad.begin();

	for(;it != ciudad.end();++it){
		cout << *it << " ";
	}

	cout << endl << "-------------------------" << endl;
	return 0;
}
