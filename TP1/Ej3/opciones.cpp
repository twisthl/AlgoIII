
#include <iostream>
#include "opciones.h"

using namespace std;

Opciones::Opciones(){
	archivo = false;
	help = false;
	poda_habilitada = false;
	mostrar_info = false;
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
		}else if ((string(argv[i]) == "-ph") || (string(argv[i]) == "--podar")) {
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

void Opciones::faltaArgumento(const char* opcion) {
	cerr << "La opcion \'" << opcion << "\' necesita de un argumento. Correr \'" << nombre_programa
		<< " -h\' para obtener ayuda." << endl;
}

void Opciones::mostrarUso() {
	cerr << "Uso: " << nombre_programa << " <opcion(es)>\n"
		<< "Opciones:\n"
		<< "\t-h, --help\t\t\tMuestra este mensaje\n"
		<< "\t-p, --path\t\t[PATH]\tCarga el archivo de [PATH]\n"
		<< "\t-o, --ouput\t\t[PATH]\tArchivo de salida\n"
		<< "\t-ph, --podar\t\tUtiliza poda basica\n"
		<< "\t-i, --info\t\tMuestra informacion adicional\n"
		<< endl;
}

void Opciones::imprimirTitulo(){
	cout << "###########################\n";
	cout << "# ALGORITMOS III - TP1EJ3 #\n";
	cout << "###########################\n";
	cout << endl;
}
