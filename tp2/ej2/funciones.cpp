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