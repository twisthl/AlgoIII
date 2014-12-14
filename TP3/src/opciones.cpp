#include <iostream>
#include "opciones.h"

using namespace std;

Opciones::Opciones(){
	this->archivo = false;
	this->help = false;
	this->poda_habilitada = false;
	this->mostrar_info = false;
	this->exercise = -1;
}

bool Opciones::cargarArgumentos(int argc, char* argv[]){
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
		else if ((string(argv[i]) == "-EX") || (string(argv[i]) == "--exacto")) {
			exercise = EXACTO;
		}
		else if ((string(argv[i]) == "-GD") || (string(argv[i]) == "--greed")) {
			exercise = GREED;
		}
		else if ((string(argv[i]) == "-GP") || (string(argv[i]) == "--grasp")) {
			exercise = GRASP;
		}
		else if ((string(argv[i]) == "-BL") || (string(argv[i]) == "--busqueda")) {
			exercise = BUSQUEDA_LOCAL;
		}
		else if ((string(argv[i]) == "-ph") || (string(argv[i]) == "--podar")) {
			poda_habilitada = true;
		}
		else if ((string(argv[i]) == "-i") || (string(argv[i]) == "--info")) {
			mostrar_info = true;
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

void Opciones::faltaArgumento(char* opcion) {
	cerr << "La opcion \'" << opcion << "\' necesita de un argumento. Correr \'" << nombre_programa
		<< " -h\' para obtener ayuda." << endl;
}

void Opciones::mostrarUso() {
	cerr << "Uso: " << nombre_programa << " <opcion(es)>\n"
		<< "Opciones:\n"
		<< "\t-h, --help\t\t\tMuestra este mensaje\n"
		<< "\t-EX, --exacto\t\t\tSe ejecuta la implementacion del algoritmo exacto\n"
		<< "\t-GD, --greed\t\t\tSe ejecuta la implementacion del algoritmo greedy\n"
		<< "\t-GP, --grasp\t\t\tSe ejecuta la implementacion del algoritmo grasp\n"
		<< "\t-BL, --busqueda\t\t\tSe ejecuta la implementacion del algoritmo grasp\n"
		<< "\t-p, --path\t\t[PATH]\tCarga el archivo de [PATH]\n"
		<< "\t-o, --ouput\t\t[PATH]\tArchivo de salida\n"
		<< "\t-ph, --podar\t\t\tHabilida la poda en del algoritmo exacto\n"
		<< "\t-i, --info\t\t\tSe muestra informacion adicional durante la ejecucion\n"
		<< endl;
}

void Opciones::imprimirTitulo(){
	cout << "########################\n";
	cout << "# ALGORITMOS III - TP1 #\n";
	cout << "########################\n";
	cout << endl;
}
