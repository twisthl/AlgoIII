#include "ej2.h"

MatrizDeNodos* modelar(int n){
	vector<Nodo*> aux(n, NULL);
    MatrizDeNodos* matriz = new MatrizDeNodos(n, aux);

	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			Nodo nodo(i,j);
			if( 0< i+2 && i+2 < n){
				if ( 0 < j+1 && j+1 < n){
					cout << "si1" << endl;
					nodo.adyacentes.push_back(Casillero(i+2,j+1));
					cout << "si1" << endl;
				}
				if (0 < j-1 && j-1 < n){
					cout << "si2" << endl;
					nodo.adyacentes.push_back(Casillero(i+2,j-1));
					cout << "si2" << endl;
				}
			}

			if(0 < i-2 && i-2 < n){
				if (0 < j+1 && j+1 < n){
					cout << "si3" << endl;
					nodo.adyacentes.push_back(Casillero(i-2,j+1));
					cout << "si3" << endl;
				}
				if (0 < j-1 && j-1 < n){

					cout << "si4" << endl;
					nodo.adyacentes.push_back(Casillero(i-2,j-1));
					cout << "si4" << endl;
				}
			}

			if(0 < j+2 && j+2 < n){
				if (0 < i+1 && i+1 < n){
					cout << "si5" << endl;
					nodo.adyacentes.push_back(Casillero(i+1,j+2));
					cout << "si5" << endl;
				}
				if (0 < i-1 && i-1 < n){

					cout << "si6" << endl;
					nodo.adyacentes.push_back(Casillero(i-1,j+2));
					cout << "si6" << endl;
				}
			}

			if(0 < j-2 && j-2 < n){
				if (0 < i+1 && i+1 < n){
					cout << "si7" << endl;
					nodo.adyacentes.push_back(Casillero(i+1,j-2));
					cout << "si7" << endl;
				}
				if (0 < i-1 && i-1 < n){

					cout << "si8" << endl;
					nodo.adyacentes.push_back(Casillero(i-1,j-2));
					cout << "si8" << endl;
				}
			}
			cout << "matriz" << endl;
			cout << (*matriz)[i][j] << " " << &nodo << endl;
			(*matriz)[i][j] = &nodo;
			cout << "matriz" << endl;
		}
	}

	cout << "Modelado" << endl;

	return matriz;
}

Nodo resolver(MatrizDeNodos& matriz, int n, Caballos& caballos, int k){

	Caballos::iterator itCaballos = caballos.begin();
	for (; itCaballos != caballos.end(); ++itCaballos){
		bfs(matriz, n, *itCaballos);
	}

	Nodo nodo;
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j){
			if((*matriz[i][j]).caballosLlegaron == k){
				if(nodo.movimientosNecesarios == -1){
					nodo = (*matriz[i][j]);
				} else if(nodo.movimientosNecesarios > (*matriz[i][j]).movimientosNecesarios) {
					nodo = (*matriz[i][j]);
				}
			}
			
		}
	}

	return nodo;
}

void bfs(MatrizDeNodos& matriz, int n, Casillero& c){
	std::vector< vector<bool> > visitado;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
		visitado[i][j] = false;
		}
	}
	int x, y;
	x = c.x -1;
	y = c.y -1;
	visitado[x][y] = true;
	Nodo nodo = (*matriz[x][y]);
	nodo.caballosLlegaron++;
	nodo.distancia = 0;

	std::queue<Nodo> cola;

	ListaAdyacencia::iterator itPrimeros = nodo.adyacentes.begin();
	for(; itPrimeros != nodo.adyacentes.end(); ++itPrimeros){
		Casillero casillero = *itPrimeros;
		x = casillero.x - 1;
		y = casillero.y -1;
		visitado[x][y] = true;
		Nodo adyacente = (*matriz[x][y]);
		adyacente.distancia = 1;
		adyacente.caballosLlegaron++;
		adyacente.movimientosNecesarios += 1;

		cola.push(adyacente);
	}

	while(!cola.empty()){
		nodo = cola.front();
		cola.pop();

		ListaAdyacencia::iterator itAdyacentes = nodo.adyacentes.begin();
		for(; itAdyacentes != nodo.adyacentes.end(); ++itAdyacentes){
			Casillero casillero = *itAdyacentes;
			x = casillero.x - 1;
			y = casillero.y -1;
			if(!visitado[x][y]){
				visitado[x][y] = true;
				Nodo adyacente = (*matriz[x][y]);
				adyacente.distancia = nodo.distancia + 1;
				adyacente.caballosLlegaron++;
				adyacente.movimientosNecesarios += adyacente.distancia;

				cola.push(adyacente);
			}
		}
	}
}