#include "ej2.h"


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


	//Recorrer los puntos criticos en orden e ir generando la salida.
	Ciudad* ciudad = new Ciudad();
	
	std::vector<PuntoCritico>::iterator itPuntos = puntos.begin();
	for(;itPuntos!=puntos.end();++itPuntos){
		if (itPuntos->sube){
			//agregar al mapa el edificio abierto


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