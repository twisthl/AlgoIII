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
	// Imprime el título del TP.
	opt.imprimirTitulo();
	// Carga los argumentos.
	if (!opt.cargarArgumentos(argc, argv))
		return -1;
	switch (opt.exercise){
		case EXACTO:{
			cout << "# EXACTO" << endl;
			Parser parser(opt);
			parser.resolver();
			parser.mostrarSolucion();
			break;
		}
		case GREED:{
			cout << "# GREED" << endl;
			Parser parser(opt);
			parser.resolver();
			parser.mostrarSolucion();
			break;
		}
		case BUSQUEDA_LOCAL:{
			cout << "# BUSQUEDA LOCAL" << endl;
			Parser parser(opt);
			parser.resolver();
			parser.mostrarSolucion();
			break;
		}
		case GRASP:{
			cout << "# GRASP" << endl;
			Parser parser(opt);
			parser.resolver();
			parser.mostrarSolucion();
			break;
		}
		default :{ 
			cerr << "Error fatal, no se ejecuta ningun ejercicio" << endl;
		}
	}

	return 0;

}