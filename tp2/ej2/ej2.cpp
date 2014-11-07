#include "ej2.h"

int main(){
	int n = 0;
	int k = 0;

	int x = 0;
	int y = 0;

	while(true){
		//Si termina de leer el archivo, fin.
		if(cin.eof()){
			break;
		}

		cin >> n;
		cin >> k;
		if (n < 1 || k < 1) {
			break;
		}

		Caballos caballos = new Caballos();
		for(int i=0; i<k;i++){
			cin >> x;
			cin >> y;

			Casillero casilla = new Casillero(x,y);

			caballos->push_back(casilla);
		}

		MatrizDeNodos matriz = modelar(n);

		Nodo solucion = resolver(matriz, caballos);

		if(soluccion != NULL){
			cout << solucion.x << solucion.y << solucion.movimientosnecesarios << endl;
		} else {
			cout << no << enld;
		}
	}
	return 0;
}
