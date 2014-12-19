/**
 * Class Opciones: Mini clase con opciones del programa
 */
#ifndef _OPCIONES_H_
#define _OPCIONES_H_

#include <iostream>

using namespace std;

#define EXACTO 0
#define GREED 1
#define BUSQUEDA_LOCAL 2
#define GRASP 3
#define PEOR_SOLUCION 4
#define RANDOM_SOLUCION 5

class Opciones{
	public:
		Opciones();
		~Opciones(){};

		// Carga los argumentos que entran por parametro.
		bool cargarArgumentos(int argc, char* argv[]);
		// Imprime las acciones que va a realizar el programa.
		void imprimirAcciones();
		// Realiza comprobaciones sobre los argumentos.
		bool consistente();
		// Imprime un mensaje indicando la falta de argumento.
		void faltaArgumento(char* opcion);
		// Muestra el Help.
		void mostrarUso();
		// Mini metodo que imprime el titulo del tp.
		void imprimirTitulo();

		int exercise;
		bool help;
		bool archivo;
		bool poda_habilitada;
		bool mostrar_info;

		string archivo_entrada;
		string archivo_salida;

		// Nombre del programa
		const char* nombre_programa;
};

#endif
