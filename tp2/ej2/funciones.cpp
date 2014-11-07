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

Nodo resolver(MatrizDeNodos matriz, Caballos caballos){

	Caballos::iterator itCaballos = caballos.begin();
	for (; itCaballos != caballos.end(); ++itCaballos){
		bfs(matriz, *itCaballos);
	}

	Nodo nodo = NULL;
	MatrizDeNodos::iterator itCasilleros = matriz.begin();
	for (; itCasilleros != matriz.end(); ++it){
		if(*it.caballosLlegaron == k){
			if (nodo == NULL){
				nodo = *it;
			} else if (nodo.movimientosNecesarios > *it.movimientosNecesarios){
				nodo = *it;
			}
		}
	}

	return nodo


}

void bfs(MatrizDeNodos matriz, Casillero c, int k){
	std::vector<vector<bool>> visitado;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
		visitado[i][j] = false;
		}
	}
	int x, y;
	x = c.x -1;
	y = c.y -1;
	visitado[x][y] = true;
	Nodo nodo = matriz[x][y];
	nodo.caballosLlegaron++;
	nodo.distancia = 0;

	std::vector<Nodo> cola;

	ListaDeAdyacencia::iterator itPrimeros = nodo.adyacentes.begin();
	for(; itPrimeros != nodo.adyacentes.end(); ++itPrimeros){
		Casillero casillero = *itPrimeros;
		x = casillero.x - 1;
		y = casillero.y -1;
		visitado[x][y] = true;
		Nodo adyacente = matriz[x][y];
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
			x = casillero.x - 1;
			y = casillero.y -1;
			if(!visitado[x][y]){
				visitado[x][y] = true;
				Nodo adyacente = matriz[x][y];
				adyacente.distancia = nodo.distancia + 1;
				adyacente.caballosLlegaron++;
				adyacente.movimientosNecesarios += adyacente.distancia;

				cola.push_back(adyacente);
			}
		}
	}

}