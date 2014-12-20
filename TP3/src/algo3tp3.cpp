#include "clock.h"
#include <iostream>
#include "tipos.h"
#include "opciones.h"
#include "parser.h"

#define TAB "\t"

using namespace std;

int main(int argc, char * argv[]){
/* Carga e Impresion de Argumentos */
	Opciones opt;
	
	// Carga los argumentos.
	if (!opt.cargarArgumentos(argc, argv))
		return -1;
	// Imprime el título del TP.
	if (opt.silence == false)
		opt.imprimirTitulo();
	switch (opt.exercise){
		case EXACTO:{
			if (opt.silence == false)
				cout << "# EXACTO" << endl;
			break;
		}
		case GREED:{
			if (opt.silence == false)
				cout << "# GREED" << endl;
			break;
		}
		case BUSQUEDA_LOCAL:{
			if (opt.silence == false)
				cout << "# BUSQUEDA LOCAL" << endl;
			break;
		}
		case GRASP:{
			if (opt.silence == false)
				cout << "# GRASP" << endl;
			break;
		}
		case PEOR_SOLUCION:{
			if (opt.silence == false)
				cout << "# PEOR SOLUCION" << endl;
			break;
		}
		case RANDOM_SOLUCION:{
			if (opt.silence == false)
				cout << "# RANDOM SOLUCION" << endl;;
			break;
		}
		default :{ 
			if (opt.silence == false)
				cerr << "Error fatal, no se ejecuta ningun ejercicio" << endl;
			return -1;
		}
		Parser parser(opt);
		parser.resolver();
		if (opt.silence == false)
			parser.mostrarSolucion();
	}

	return 0;

}