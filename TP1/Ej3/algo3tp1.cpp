/*************
 *   TP 1    *
 *************/

#include <iostream>
#include "opciones.h"
//#include "ej1.h"
//#include "ej2.h"
#include "ej3_parser.h"
#include "ej3.h"


using namespace std;

int main(int argc, const char* argv[]) {
	/* Carga e Impresion de Argumentos */
	Opciones opt;
	// Imprime el título del TP.
	opt.imprimirTitulo();
	// Carga los argumentos.
	if (!opt.cargarArgumentos(argc, argv))
		return -1;

	switch (opt.exercise){
		case EJ1: {
			cout << "# Ejercicio 1" << endl;
			cout << "NOTHING TO DO HERE" << endl;
			break;
		}
		case EJ2: {
			cout << "# Ejercicio 2" << endl;
			cout << "NOTHING TO DO HERE" << endl;
			break;
		}
		case EJ3: {
			cout << "# Ejercicio 3" << endl;
			Ej3 ej3(opt);
			ej3.resolverBiohazard();
			ej3.mostrarMejorSolucion();
			break;
		}
		default : {
			cerr << "Error fatal, no se ejecuta ningun ejercicio" << endl;
		}
	}
	return 0;
}

