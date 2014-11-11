/*************
 *   TP 1    *
 *************/

#include <iostream>
#include "opciones.h"
#include "ej1_parser.h"


using namespace std;

int main(int argc, const char* argv[]) {
	/* Carga e Impresion de Argumentos */
	Opciones opt;
	// Imprime el título del TP.
	opt.imprimirTitulo();
	// Carga los argumentos.
	if (!opt.cargarArgumentos(argc, argv))
		return -1;

	cout << "# Ejercicio 1" << endl;
	Ej1Parser ej1(opt);
	ej1.resolver();

	return 0;
}
