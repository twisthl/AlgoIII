/**
 * Class Opciones: Mini clase con opciones del programa
 */
#ifndef _OPCIONES_H_
#define _OPCIONES_H_

#include <iostream>

using namespace std;

//EJERCICIOS
#define EJ1 0
#define EJ2 1
#define EJ3 2

class Opciones{
	public:
		Opciones();
		~Opciones(){}

		// Carga los argumentos que entran por parametro.
		bool cargarArgumentos(int argc, const char* argv[]);
		// Imprime las acciones que va a realizar el programa.
		void imprimirAcciones();
		// Realiza comprobaciones sobre los argumentos.
		bool consistente();
		// Imprime un mensaje indicando la falta de argumento.
		void faltaArgumento(const char* opcion);
		// Muestra el Help.
		void mostrarUso();
		// Mini metodo que imprime el titulo del tp.
		void imprimirTitulo();

		enum numero_ejercicio {
			ej1,
			ej2,
			ej3
		} exercise;

		bool help;
		bool archivo;
		bool poda_habilitada;
		bool mejora_habilitada;

		string archivo_entrada;
		string archivo_salida;

		// Nombre del programa
		const char* nombre_programa;
};

#endif
