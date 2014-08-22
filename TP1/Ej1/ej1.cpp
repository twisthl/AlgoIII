#include "ej1.h"

using namespace std;

int main(){
	int cantBoards;
	int maxJump;

	while(true){

		//Si termina de leer el archivo, fin.
		if(cin.eof()){
			break;
		}

		//1er y 2do params cantidad de tablas del puente y salto maximo.
		cin >> cantBoards;
		cin >> maxJump;

		//cout << "cantidad de tablas: " << cantBoards << endl;
		//cout << "salto maximo: " << maxJump << endl;

		LBoardState* boards = new LBoardState();

		//Armo la lista de estado de Tablas del puente
		for(int i=0; i<cantBoards;i++){
			cin >> boardI;

			boards->push_back(boardI);
		}
		cin >> endEntry;

		res = resolver(cantBoards, maxJump, *boards);
	


	}
}