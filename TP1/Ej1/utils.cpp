#include "ej1.h"

using namespace std;

LSaltos resolver(int cantTablones, int saltoMaximo, LTablonesEstado& tablones){
//	int ini = 1;

	LSaltos* saltos = new LSaltos();
//	std::vector<int>::iterator ultimoTablon = tablones.begin();
	
	int contadorSaltoMaximo = 0;
	int tablonASaltar;	
	bool encontroSalto = false;

//	for(ultimoTablon; ultimoTablon != tablones.end(); ultimoTablon++){
	for(int nroTablon = 0; nroTablon < cantTablones; nroTablon++){

		contadorSaltoMaximo++;
		
		//Si hay un tablon en ese lugar actualizo tablonASaltar
		if(tablones[nroTablon] == 1){
			tablonASaltar = nroTablon;
			encontroSalto = true;
		}
		
		//Si llegue al limite de salto agrego (Y pude hacer un salto) agrego el tablon al que voy a saltar a la lista de saltos y reinicio los contadores
		if(contadorSaltoMaximo == saltoMaximo && encontroSalto){			
			saltos->push_back(tablonASaltar);
			contadorSaltoMaximo = 0;
		}else if (!encontroSalto)
		{
			break;
		}
	}
	return *saltos;//Tambien devolver si se pudo llegar al final con saltos.
}
