#include "clock.h"
#include <iostream>
#include "tipos.h"
#include "opciones.h"
#include "grasp.h"
#include "exacto.h"
#include "peorSolucion.h"
#include <stdlib.h> 
#include <time.h>

#define TAB "\t"

using namespace std;

list<Arista> obtenerListaMRandomAristas(int n, int m){
	list<Arista> aristasOrdenadas;
	for (Vertice v=0; v<n; v++){
		for (Vertice w=v+1; w<n; w++){
			double peso = (rand() % 4000 + 1)/10;
			Arista arista (v, w, peso);
			aristasOrdenadas.push_back(arista);
		}
	}
	list<Arista> aristasDesordenadas;
	while (aristasDesordenadas.size() != m){
		int iRand = rand() % aristasOrdenadas.size();
		list<Arista>::iterator it = aristasOrdenadas.begin();
		advance(it,iRand);
		aristasDesordenadas.push_back(*it);
		aristasOrdenadas.erase(it);
	}
	return aristasDesordenadas;
}


Grafo* generarGrafoRandom(int n, int k, int  m){
	list<Arista> aristaList = obtenerListaMRandomAristas(n, m);
	Grafo* G = new Grafo(n, aristaList);
	return G;
}

struct Calidad{
	Calidad(double alpha, int beta, int cantidad, double calidad){
		this->alpha = this->alpha;
		this->beta = this->beta;
		this->cantidad = cantidad;
		this->calidad = calidad;
	}
	double alpha;
	int beta;
	int cantidad;
	double calidad;
};

bool mejorCalidad(Calidad &c1, Calidad &c2){
	return (c1.calidad > c2.calidad);
}

int main(int argc, char * argv[]){

	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
    /* using nano-seconds instead of seconds */
    srand((time_t)ts.tv_nsec);

	Calidad calidad(0.0, 0, 0, 0.0);
	vector<Calidad> aux(21, calidad);
    vector<vector<Calidad> > tablaResultados(21, aux);

    for (int n = 5; n <= 40; n+=4){
    	double porcentajeRealizado = (n-5);
		porcentajeRealizado = porcentajeRealizado / 40;
		porcentajeRealizado = porcentajeRealizado * 100;
		//cout << "porcentaje Realizado = " << porcentajeRealizado << "%" << endl;
		for (int k = 2; k < n; k+= 2){
			double porcentajeRealizado2 = (k-2);
			porcentajeRealizado2 = porcentajeRealizado2 / n ;
			porcentajeRealizado2 = porcentajeRealizado2 * 100;
			porcentajeRealizado2 = porcentajeRealizado + porcentajeRealizado2 / 8;
			cout << "porcentaje Realizado = " << porcentajeRealizado2 << "%" << endl;
			for (int m = 3; m <= n*(n-1)/2; m+=3){
				//100 grafos aleatorios con mismo m y k
				//double aux = (m-3);
				//aux = aux / (n*(n-1)/2) * (2*100);
				//aux = aux / n / 3;
				//double porcentajeRealizado3 = porcentajeRealizado2 + aux;
				//cout << "porcentaje Realizado = " << porcentajeRealizado3 << "%" <<endl;

				for (int i = 1; i<= 5; i++){
					Grafo* G = generarGrafoRandom(n, k, m);
					Exacto exacto(G, k, true, false);
					double tiempoExacto = exacto.resolver();
					list<Particion> k_particion = exacto.dameKParticion();
					double mejorPeso = cuantoPesa(k_particion);
					

					PeorSolucion peorSolucion(G, k, false);
					peorSolucion.resolver();
					k_particion = peorSolucion.dameKParticion();
					double peorPeso = cuantoPesa(k_particion);

					//Probamos
					for (int gamma = 0; gamma <= 20; gamma++){
						double alpha = gamma;
						alpha = alpha / 20;
						for (int beta = 1; beta <=16; beta++){
							//5 pruebas con el mismo grafo para cada combinacion de alpha y beta
							for (int j=0; j<5; j++){
								Grasp grasp(G, k, false, alpha, beta, 1, 1);
								grasp.resolver();
								k_particion = grasp.dameKParticion();
								double peso = cuantoPesa(k_particion);
								double calidad;
								if (peorPeso != mejorPeso){
									//cout << "mejor peso = " << mejorPeso <<  "; peor peso = " << peorPeso << endl;
									//cout << "peso obtenido = " << peso << endl;
									calidad = peso-mejorPeso;
									calidad = calidad / (peorPeso-mejorPeso);
									calidad = 1-calidad;
									//cout << "calidad= " << calidad << endl;
									calidad = calidad * calidad;
									//cout << "calidad2= " << calidad << endl << endl;
									//calidad = 1-((peso-mejorPeso)/(peorPeso-mejorPeso));
									//calidad = calidad * calidad;
									double nuevaCalidad = tablaResultados[gamma][beta].calidad / (tablaResultados[gamma][beta].cantidad + 1); 
									nuevaCalidad = nuevaCalidad * tablaResultados[gamma][beta].cantidad;
									//cout << "nuevaCalidad += " << (calidad * tablaResultados[gamma][beta].cantidad) << "/" << (tablaResultados[gamma][beta].cantidad+1) << endl;
									double aux2 = calidad / (tablaResultados[gamma][beta].cantidad + 1);
									nuevaCalidad += aux2;
									
									tablaResultados[gamma][beta].cantidad = tablaResultados[gamma][beta].cantidad+1;
									tablaResultados[gamma][beta].calidad = nuevaCalidad;
									tablaResultados[gamma][beta].alpha = alpha;
									tablaResultados[gamma][beta].beta = beta;
									//cout << "nuevaCalidad = " << calidad ;
									//cout << "/" << (tablaResultados[gamma][beta].cantidad + 1) << endl;
								}


								
							}
						}
					}
					delete G;
				}
			}
		}
	}
	list<Calidad> mejores;
	int top = 10;
	for (int i = 1; i<= 20; i++){
		for (int j = 1; j<= 20; j++){
			if (tablaResultados[i][j].cantidad >1){
				list<Calidad> calidadList;
				calidadList.push_back(tablaResultados[i][j]);
				mejores.merge(calidadList, mejorCalidad);
				if (mejores.size() > top)
					mejores.pop_back();	
			}
		}
	}
	cout << endl << "Mejores resultados:";
	int i = 1;
	for (list<Calidad>::iterator it = mejores.begin(); it!=mejores.end(); it++){
		cout << i << ": " << endl;
		cout << "alpha = " << it->alpha << endl;
		cout << "beta = " << it->beta << endl;
		cout << "Calidad = " << it->calidad << endl;
		cout << "Cantidad =" << it->cantidad << endl;
		i++;
	}


	return 0;
}
