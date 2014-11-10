#include "ej2.h"

MatrizDeNodos* modelar(int n){
	vector<Nodo> aux(n);
    MatrizDeNodos* matriz = new MatrizDeNodos(n, aux);

	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			//ListaAdyacencia lista;
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
			(*matriz)[i][j] = nodo;
			cout << "matriz" << endl;
		}
	}

	cout << "Modelado" << endl;

	return matriz;
}

Nodo resolver(MatrizDeNodos& matriz, int n, Caballos& caballos, int k){

	int i = 1;
	Caballos::iterator itCaballos = caballos.begin();
	for (; itCaballos != caballos.end(); ++itCaballos){
		cout << "Resolver " << i << endl;	
		bfs(matriz, n, *itCaballos);
		++i;
	}

	Nodo nodo;
	for (int i = 0; i < n; ++i){
		cout << "MATRIZ ";
		for (int j = 0; j < n; ++j){
			cout << matriz[i][j].caballosLlegaron << " " << matriz[i][j].movimientosNecesarios << " ; ";
			if(matriz[i][j].caballosLlegaron == k){
				if(nodo.movimientosNecesarios == -1){
					nodo = matriz[i][j];
				} else if(nodo.movimientosNecesarios > matriz[i][j].movimientosNecesarios) {
					nodo = matriz[i][j];
				}
			}
			
		}
		cout << endl;
	}

	return nodo;
}

void bfs(MatrizDeNodos& matriz, int n, Casillero& c){
	cout << "BFS" << endl;
	cout << "Caballo : " << c.x << " " << c.y << endl;


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
	cout << "CASILLERO " << x << " " << y << endl;
	cout << "visitados " << visitado[x][y] << endl;
	visitado[x][y] = true;
	cout << "visitados " << visitado[x][y] << endl;

	//Nodo nodo = matriz[x][y];
	cout << "CaballosLlegaron " << matriz[x][y].caballosLlegaron << endl;
	matriz[x][y].caballosLlegaron++;
	cout << "CaballosLlegaron " << matriz[x][y].caballosLlegaron << endl;
	matriz[x][y].distancia = 0;

	cout << "Size() " << matriz[x][y].adyacentes.size() << endl;

	std::queue<Nodo> cola;

	ListaAdyacencia::iterator itPrimeros = matriz[x][y].adyacentes.begin();
	for(; itPrimeros != matriz[x][y].adyacentes.end(); ++itPrimeros){
		Casillero casillero = *itPrimeros;
		int a = casillero.x;
		int b = casillero.y;
		cout << "Casillero: " << a << " " << b << endl;
		cout << "visitados " << visitado[a][b] << endl;
		visitado[a][b] = true;
		cout << "visitados " << visitado[a][b] << endl;
		//Nodo adyacente = matriz[a][b];
		matriz[a][b].distancia = 1;
		matriz[a][b].caballosLlegaron++;
		cout << "MOVIMIENTOS: " << matriz[a][b].movimientosNecesarios << endl;
		matriz[a][b].movimientosNecesarios += 1;
		cout << "MOVIMIENTOS: " << matriz[a][b].movimientosNecesarios << endl;

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
				//Nodo adyacente = matriz[a][b];
				matriz[a][b].distancia = nodo.distancia + 1;
				matriz[a][b].caballosLlegaron++;
				cout << "MOVIMIENTOS: " << matriz[a][b].movimientosNecesarios << endl;
				matriz[a][b].movimientosNecesarios += matriz[a][b].distancia;
				cout << "MOVIMIENTOS: " << matriz[a][b].movimientosNecesarios << endl;

				cola.push(matriz[a][b]);
			}
		}
	}
}