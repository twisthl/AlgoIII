#include "ej2.h"

MatrizDeNodos* modelar(int n){
	vector<Nodo> aux(n);
    MatrizDeNodos* matriz = new MatrizDeNodos(n, aux);

	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			//ListaAdyacencia lista;
			Nodo nodo(i,j);
			if( 0<= i+2 && i+2 < n){
				if ( 0 <= j+1 && j+1 < n){
					nodo.adyacentes.push_back(Casillero(i+2,j+1));
				}
				if (0 <= j-1 && j-1 < n){
					nodo.adyacentes.push_back(Casillero(i+2,j-1));
				}
			}

			if(0 <= i-2 && i-2 < n){
				if (0 <= j+1 && j+1 < n){
					nodo.adyacentes.push_back(Casillero(i-2,j+1));
				}
				if (0 <= j-1 && j-1 < n){
					nodo.adyacentes.push_back(Casillero(i-2,j-1));
				}
			}

			if(0 <= j+2 && j+2 < n){
				if (0 <= i+1 && i+1 < n){
					nodo.adyacentes.push_back(Casillero(i+1,j+2));
				}
				if (0 <= i-1 && i-1 < n){
					nodo.adyacentes.push_back(Casillero(i-1,j+2));
				}
			}

			if(0 <= j-2 && j-2 < n){
				if (0 <= i+1 && i+1 < n){
					nodo.adyacentes.push_back(Casillero(i+1,j-2));
				}
				if (0 <= i-1 && i-1 < n){
					nodo.adyacentes.push_back(Casillero(i-1,j-2));
				}
			}
			(*matriz)[i][j] = nodo;
		}
	}
	return matriz;
}

Nodo resolver(MatrizDeNodos& matriz, int n, Caballos& caballos, int k){

	int i = 1;
	Caballos::iterator itCaballos = caballos.begin();
	for (; itCaballos != caballos.end(); ++itCaballos){
		//imprimirMatriz(matriz,n);	
		bfs(matriz, n, *itCaballos);
		//imprimirMatriz(matriz,n);
		++i;
	}

	Nodo nodo;
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j){
			if(matriz[i][j].caballosLlegaron == k){
				if(nodo.movimientosNecesarios == -1){
					nodo = matriz[i][j];
				} else if(nodo.movimientosNecesarios > matriz[i][j].movimientosNecesarios) {
					nodo = matriz[i][j];
				}
			}
		}
	}
	imprimirMatriz(matriz,n);
	return nodo;
}

void bfs(MatrizDeNodos& matriz, int n, Casillero& c){
	std::vector<bool> aux(n,false);
	std::vector< vector<bool> > visitado(n,aux);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
		visitado[i][j] = false;
		}
	}

	int x, y;
	x = c.x -1;
	y = c.y -1;
	visitado[x][y] = true;

	matriz[x][y].caballosLlegaron++;
	matriz[x][y].distancia = 0;

	std::queue<Nodo> cola;

	ListaAdyacencia::iterator itPrimeros = matriz[x][y].adyacentes.begin();
	for(; itPrimeros != matriz[x][y].adyacentes.end(); ++itPrimeros){
		Casillero casillero = *itPrimeros;
		int a = casillero.x;
		int b = casillero.y;
		visitado[a][b] = true;
		matriz[a][b].distancia = 1;
		matriz[a][b].caballosLlegaron++;
		matriz[a][b].movimientosNecesarios += 1;

		cola.push(matriz[a][b]);
	}

	while(!cola.empty()){
		Nodo nodo = cola.front();
		cola.pop();

		ListaAdyacencia::iterator itAdyacentes = nodo.adyacentes.begin();
		for(; itAdyacentes != nodo.adyacentes.end(); ++itAdyacentes){
			Casillero casillero = *itAdyacentes;
			int a = casillero.x;
			int b = casillero.y;
			if(!visitado[a][b]){
				visitado[a][b] = true;
				matriz[a][b].distancia = nodo.distancia + 1;
				matriz[a][b].caballosLlegaron++;
				matriz[a][b].movimientosNecesarios += matriz[a][b].distancia;

				cola.push(matriz[a][b]);
			}
		}
	}
}

void imprimirMatriz(MatrizDeNodos& matriz, int n){
	for (int i = 0; i < n; ++i){
		cout << "MATRIZ ";
		for (int j = 0; j < n; ++j){
			cout << matriz[i][j].caballosLlegaron << " " << matriz[i][j].movimientosNecesarios << " ; ";			
		}
		cout << endl;
	}
}