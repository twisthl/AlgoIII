#include "ej2.h"

//El orden está establecido por: Posicion,Sube o Baja, Altura
struct orden_PuntoCritico{
	bool operator()(const PuntoCritico& a, const PuntoCritico& b) const{
		if(a.posicion == b.posicion){
			if (a.sube == b.sube){
				return a.altura < b.altura;
			} else {
				return a.sube > b.sube;
			}
		} else {
			return a.posicion < b.posicion;
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
	std::vector<PuntoCritico> puntos;

	//Recorrer los edificios para definir los PuntosCriticos a analizar
	Edificios::iterator itEdificios = edificios.begin();
	for(;itEdificios!=edificios.end();++itEdificios){
		Edificio edificio = *itEdificios;
	
		PuntoCritico* pc = new PuntoCritico(true,edificio);
		puntos.push_back(*pc);
		pc = new PuntoCritico(false,edificio);
		puntos.push_back(*pc);
	}

	//Ordenar los puntos criticos para luego analizar en orden realizando una barrida lineal
	orden_PuntoCritico ord_functor;
	sort(puntos.begin(), puntos.end(), ord_functor);

	//Recorrer los puntos criticos en orden e ir generando la salida.
	Ciudad* ciudad = new Ciudad();
	int nivelActual = 0;
	MapAlturas edificiosAbiertos;
	Edificio* edificioPrueba = new Edificio(0,0,0);
	PuntoCritico* pc = new PuntoCritico(true,*edificioPrueba);
	edificiosAbiertos.insert(make_pair(0,*pc));

	std::vector<PuntoCritico>::iterator itPuntos = puntos.begin();
	for(;itPuntos!=puntos.end();++itPuntos){
		//cout << endl;
		//cout << "AlturaActual: " << nivelActual << endl;
		//cout << "PuntoCritico: " << (*itPuntos).sube << " " << (*itPuntos).posicion << " " << (*itPuntos).altura << endl;
		if (itPuntos->sube){
			//agregar al mapa el edificio abierto
			//cout << "Agregue un par :" << itPuntos->altura << " " << itPuntos->posicion << endl;
			edificiosAbiertos.insert(make_pair(itPuntos->altura,*itPuntos));
			std::vector<PuntoCritico>::iterator itCopy = itPuntos;
 			if(*(++itCopy) == *itPuntos){
				continue;
			} else if (itPuntos->altura > nivelActual){
				ciudad->push_back(itPuntos->posicion);
				ciudad->push_back(itPuntos->altura);
				//cout << "AlturaAnterior: " << nivelActual << endl;
				nivelActual = itPuntos->altura;
				//cout << "AlturaActual: " << nivelActual << endl;
			}
		} else {
			//Sacar del mapa el edificio
			//cout << "VOY A BORRAR!!!!!!!!!!!" << endl;
			MapAlturas::iterator it = edificiosAbiertos.find(itPuntos->altura);
			//cout << "MaP: " << it->first << " " << it->second.posicion << endl;
			//cout << "FIND!!!!!!!!!!!" << endl;
			edificiosAbiertos.erase (it);
			//cout << "Saque una altura: " << itPuntos->altura << endl;
			MapAlturas::iterator itEdificiosAbiertos = --edificiosAbiertos.end();
			int alturaMaximoEdificio = (*itEdificiosAbiertos).first;
			if(itPuntos->altura == nivelActual && alturaMaximoEdificio < itPuntos->altura){
				//cout << "Maximo edificio: " << (*itEdificiosAbiertos).first << endl;
				ciudad->push_back(itPuntos->posicion);
				ciudad->push_back(alturaMaximoEdificio);
				//cout << "AlturaAnterior: " << nivelActual << endl;
				nivelActual = alturaMaximoEdificio;
				//cout << "AlturaActual: " << nivelActual << endl;
			}
		}

	}
	cout << endl;
	return ciudad;
}

int imprimirCiudad(Ciudad& ciudad){

	Ciudad::iterator it = ciudad.begin();

	for(;it != ciudad.end();++it){
		cout << *it << " ";
	}

	cout << endl << "-------------------------" << endl;
	return 0;
}
