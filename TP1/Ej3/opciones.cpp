
#include <iostream>
#include "opciones.h"

using namespace std;

Opciones::Opciones(){
	archivo = false;
	help = false;
	poda_habilitada = false;
	mejora_habilitada = false;
}

bool Opciones::cargarArgumentos(int argc, const char* argv[]){
	nombre_programa = argv[0];
	for (int i = 1; i < argc; i++) {
		// Archivo
		if ((string(argv[i]) == "-p") || (string(argv[i]) == "--path")) {
			if (i + 1 < argc) {
				archivo_entrada = argv[++i];
				archivo = true;
			} else {
				faltaArgumento(argv[i]);
				return false;
			}
		}
		// Archivo salida
		else if ((string(argv[i]) == "-o") || (string(argv[i]) == "--output")) {
			if (i + 1 < argc) {
				archivo_salida = argv[++i];
			} else {
				faltaArgumento(argv[i]);
				return false;
			}
		}
		else if ((string(argv[i]) == "-1") || (string(argv[i]) == "--ej1")) {
			exercise = ej1;
		}
		else if ((string(argv[i]) == "-2") || (string(argv[i]) == "--ej2")) {
			exercise = ej2;
		}
		else if ((string(argv[i]) == "-3") || (string(argv[i]) == "--ej3")) {
			exercise = ej3;
		}
		else if ((string(argv[i]) == "-ph") || (string(argv[i]) == "--podar")) {
			poda_habilitada = true;
		}
		else if ((string(argv[i]) == "-m") || (string(argv[i]) == "--noRepite")) {
			mejora_habilitada = true;
		}
		else if ((string(argv[i]) == "-h") || (string(argv[i]) == "--help")) {
			help = true;
		}
	}

	// Chequear consistencia
	if (!consistente()) return false;

	return true;
}


bool Opciones::consistente(){
	// Esta obligado a meter un archivo de entrada, o mostrar HELP.
	if (!archivo || help){
		cerr << "Error, es necesario ingresar un archivo \n" << endl;
		mostrarUso();
		return false;
	}

	return true;
}

void Opciones::faltaArgumento(const char* opcion) {
	cerr << "La opcion \'" << opcion << "\' necesita de un argumento. Correr \'" << nombre_programa
		<< " -h\' para obtener ayuda." << endl;
}

void Opciones::mostrarUso() {
	cerr << "Uso: " << nombre_programa << " <opcion(es)>\n"
		<< "Opciones:\n"
		<< "\t-h, --help\t\t\tMuestra este mensaje\n"
		<< "\t-1, --ej1\t\t\tSe ejecuta el ejercicio 1\n"
		<< "\t-2, --ej2\t\t\tSe ejecuta el ejercicio 2\n"
		<< "\t-3, --ej3\t\t\tSe ejecuta el ejercicio 3\n"
		<< "\t-p, --path\t\t[PATH]\tCarga el archivo de [PATH]\n"
		<< "\t-o, --ouput\t\t[PATH]\tArchivo de salida\n"
		<< "\t-ph, --podar\t\t\tHabilida la poda en el Ejercicio 3\n"
		<< "\t-m, --mejorar\t\t\tUtiliza el algoritmo mejorado en el Ejercicio 3\n"
		<< endl;
}

void Opciones::imprimirTitulo(){
	cout << "########################\n";
	cout << "# ALGORITMOS III - TP1 #\n";
	cout << "########################\n";
	cout << endl;
}
