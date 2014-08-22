#include "ej1.h"

using namespace std;

LJumps resolver(int cantTablones, int saltoMaximo, LTablonesEstado& tablones){
	int ini = 1;


//	vector<int>::iterator lastBoard;
//	int ultimoTablon;
//	int ultimoTablonValido;

	LSaltos saltos* = new LSaltos();
	
	std::vector<int>::iterator ultimoTablon = tablones.begin();
	
	int contadorSaltoMaximo = 0;
	
	//inserto el primer tablon
//	saltos->push_back(1);
	
	
//	for(ultimoTablon; ultimoTablon != tablones.end(); ultimoTablon++){
	for(int contadorNroTablon = 0; contadorNroTablon < cantTablones; contadorNroTablon++){

//		contadorNroTablon++;
		contadorSaltoMaximo++;
		
		//Si hay un tablon en ese lugar actualizo tablonASaltar
		//Es posible que tenga que agregar un bool para chequear que haya podido hacer algun salto el cual se setea a true aca.
		if(tablones[contadorNroTablon] == 1){
			tablonASaltar = contadorNroTablon;
		}
		
		//Si llegue al limite de salto agrego (Y pude hacer un salto) agrego el tablon al que voy a saltar a la lista de saltos y reinicio los contadores
		if(contadorSaltoMaximo == saltoMaximo){
			
			saltos->push_back(contadorNroTablon);
			contadorSaltoMaximo = 0;
		}
	}
	
	return saltos;//Tambien devolver si se pudo llegar al final con saltos.


/*	for(int i=0; i < saltoMaximo; i++){
		int tablonMasLejano = i;
		if(tablones[i] == 1){
			//actualizo los datos
			tablonMasLejano = i;
		}
	}
*/
}
