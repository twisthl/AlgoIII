/*************
 *   TP 1    *
 *************/

#include <iostream>
#include "opciones.h"
#include "ej3_parser.h"


using namespace std;

int main(int argc, const char* argv[]) {
	/* Carga e Impresion de Argumentos */
	Opciones opt;
	// Imprime el título del TP.
	opt.imprimirTitulo();
	// Carga los argumentos.
	if (!opt.cargarArgumentos(argc, argv))
		return -1;

	cout << "# Ejercicio 3" << endl;
	Ej3Parser ej3(opt);
	ej3.resolver();

	return 0;
}
