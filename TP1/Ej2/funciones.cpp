#include "ej2.h"


struct PuntoCritico{
	bool sube;
	int altura, posicion;
	Edificio edificio;
};

Ciudad* edificar(int cantEdificios, Edificios& Edificios){
	Ciudad* ciudad = new Ciudad();
	ciudad->push_back(9);
	ciudad->push_back(8);
	ciudad->push_back(7);
	ciudad->push_back(6);
	ciudad->push_back(5);
	ciudad->push_back(4);
	ciudad->push_back(3);
	ciudad->push_back(2);
	ciudad->push_back(1);
	ciudad->push_back(0);

	return ciudad;
}

int imprimirCiudad(Ciudad& ciudad){

	Ciudad::iterator it = ciudad.begin();

	for(;it != ciudad.end();++it){
		cout << *it << " ";
	}

	cout<< endl;

	return 0;
}