#include "ej1.h"

using namespace std;

LJumps resolver(int cantBoards, int maxJumps, LBoardState& boards){
	int ini = 1;


//	vector<int>::iterator lastBoard;
	int lastBoard;
	int lastValidBoard;


	for(int i=0; i<cantBoards; i++){

//		for(lastBoard; lastBoard < lastBoard+maxJumps; )

		while(lastBoard)
	}


	for(int i=0; i < maxJumps; i++){
		int farthestBoard = i;
		if(boards[i] == 1){
			//actualizo los datos
			farthestBoard = i;
		}
	}

}