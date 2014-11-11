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

		Caballos caballos;
		for(int i=0; i<k; i++){
			cin >> x;
			cin >> y;

			Casillero casilla(x,y);
			caballos.push_back(casilla);
		}

		MatrizDeNodos* matriz = modelar(n);

		Nodo solucion = resolver(*matriz, n, caballos, k);

		if(solucion.movimientosNecesarios != -1){
			cout << solucion.x + 1 << " " << solucion.y + 1 << " " << solucion.movimientosNecesarios << endl;
		} else {
			cout << "no" << endl;
		}
	}
	return 0;
}
