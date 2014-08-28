#include "ej1.h"

using namespace std;

LSaltos resolver(int cantTablones, int saltoMaximo, LTablonesEstado& tablones){
//	int ini = 1;

//	LSaltos* saltos = new LSaltos();
	LSaltos saltos;
//	std::vector<int>::iterator ultimoTablon = tablones.begin();
	
	int contadorSaltoMaximo = 0;
	int tablonASaltar;
	int tamSalto = 0;
	bool encontroSalto = false;

//	for(ultimoTablon; ultimoTablon != tablones.end(); ultimoTablon++){
	for(int nroTablon = 0; nroTablon < cantTablones; nroTablon++){

		tamSalto++;
		contadorSaltoMaximo++;
		
		//Si hay un tablon en ese lugar actualizo tablonASaltar
		if(tablones[nroTablon] == 1){
			tablonASaltar = nroTablon;
			encontroSalto = true;
		}
		
		//Si llegue al limite de salto agrego (Y pude hacer un salto) agrego el tablon al que voy a saltar a la lista de saltos y reinicio los contadores
		if(contadorSaltoMaximo == saltoMaximo && encontroSalto){			
			saltos.push_back(tablonASaltar);
			contadorSaltoMaximo = saltoMaximo - tamSalto;
		}else if (!encontroSalto)
		{
			break;
			saltos.clear();
		}
	}
	return saltos;//Tambien devolver si se pudo llegar al final con saltos.
}

void imprimirResultado(LSaltos saltos){
	int cantSaltos = saltos.size();

	if(cantSaltos == 0){
		cout << "no";// << endl;
	}else{
		for (int i = 0; i < cantSaltos; ++i)
		{
			cout << ' ' << saltos[i];
		}
	}
	cout << endl;
	
}
