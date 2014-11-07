#include "ej2.h"

MatrizDeNodos modelar(int n){
	MatrizDeNodos matriz = new MatrizDeNodos();
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			Nodo nodo = new Nodo(i,j);
			if(0 < i+2 < n){
				if (0 < j+1 < n){
					nodo.adyacentes.push_back(new Casillero(i+2,j+1));
				}
				if (0 < j-1 < n){
					nodo.adyacentes.push_back(new Casillero(i+2,j-1));
				}
			}
			if(0 < i-2 < n){
				if (0 < j+1 < n){
					nodo.adyacentes.push_back(new Casillero(i-2,j+1));
				}
				if (0 < j-1 < n){
					nodo.adyacentes.push_back(new Casillero(i-2,j-1));
				}
			}
			if(0 < j+2 < n){
				if (0 < i+1 < n){
					nodo.adyacentes.push_back(new Casillero(i+1,j+2));
				}
				if (0 < i-1 < n){
					nodo.adyacentes.push_back(new Casillero(i-1,j+2));
				}
			}
			if(0 < j-2 < n){
				if (0 < i+1 < n){
					nodo.adyacentes.push_back(new Casillero(i+1,j-2));
				}
				if (0 < i-1 < n){
					nodo.adyacentes.push_back(new Casillero(i-1,j-2));
				}
			}
			matriz[i][j] = nodo;
		}
	}

	return matriz;
}

int resolver(MatrizDeNodos matriz, Caballos caballos){




}

void bfs(MatrizDeNodos matriz, Casillero c){
	std::vector<vector<bool>> visitado;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
		visitado[i][j] = false;
		}
	}

	visitado[c.x][c.y] = true;
	Nodo nodo = matriz[c.x][c.y];
	nodo.caballosLlegaron++;
	nodo.distancia = 0;

	std::vector<Nodo> cola;

	ListaDeAdyacencia::iterator itPrimeros = nodo.adyacentes.begin();
	for(; itPrimeros != nodo.adyacentes.end(); ++itPrimeros){
		Casillero casillero = *itPrimeros;
		visitado[casillero.x][casillero.y] = true;
		Nodo adyacente = matriz[casillero.x][casillero.y];
		adyacente.distancia = 1;
		adyacente.caballosLlegaron++;
		adyacente.movimientosNecesarios += 1;

		cola.push_back(adyacente);
	}

	while(!cola.empty()){
		nodo = cola.front();
		cola.pop_front();

		ListaDeAdyacencia::iterator it = nodo.adyacentes.begin();
		for(; it != nodo.adyacentes.end(); ++it){
			Casillero casillero = *it;
			if(!visitado[casillero.x][casillero.y]){
				visitado[casillero.x][casillero.y] = true;
				Nodo adyacente = matriz[casillero.x][casillero.y];
				adyacente.distancia = nodo.distancia +1;
				adyacente.caballosLlegaron++;
				adyacente.movimientosNecesarios += adyacente.distancia;

				cola.push_back(adyacente);
			}
		}
	}

}