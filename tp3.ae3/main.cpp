
#include <iostream>
#include <vector>
#include <list>
#include <limits>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "reloj.h"

using namespace std;

#define INF numeric_limits<double>::max()

int sterling;		// Numero de Sterling con fines de debug.
double peso_min;	// Peso minimo de la solucion encontrada.

void mostrarTiempos(list<Reloj> & relojes, vector<double> sol_pesos, int n, int m, int k){
	cout << n << " " << m << " " << k << " ";
	int i = 0;
	for( list<Reloj>::iterator it = relojes.begin(); it != relojes.end(); it++){
		it->promediar_tiempos();
		cout << it->lapsos_promedios.front().second << " " << sol_pesos[i] << " ";
		i++;
	}
	cout << endl;
}

void mostrarParticiones(vector< list<int> > & particiones, vector< vector<double> > & m_ady){
	for(int i = 0; i < particiones.size(); i++){
		cout << "{ ";
		list<int>::const_iterator it = particiones[i].begin();
		for(; it != particiones[i].end(); ++it){
			cout << *it << " ";
		}
		if(i+1 < particiones.size()) cout << "}, ";
		else cout << "}";
	}
	cout << endl;
}

double peso(vector< list<int> > & particiones, vector< vector<double> > & m_ady){
	double peso = 0;
	for (int i = 0; i < particiones.size(); i++){
		for(auto u = particiones[i].begin(); u != particiones[i].end(); ++u){
			for(auto v = particiones[i].begin(); v != particiones[i].end(); ++v){
				if(m_ady[*u][*v] != -1){
					peso += m_ady[*u][*v];
				}
			}
		}
	}
	return peso;
}

void backtrack(vector< list<int> > & particiones, vector< list<int> > & sol, vector< vector <double> > & m_ady, int k, int v, int vertices_por_ubicar, int K, int particiones_libres){

	// Tenemos una posible solucion, hay que ver si es la de peso minimo o no.
	if (!vertices_por_ubicar){
		double w = peso(particiones,m_ady);
		if(w < peso_min){
			// Copiamos la solucion O(n).
			sol = particiones;
			peso_min = w;
		}
	}

	// Si hay mas particiones libres que vertices por ubicar, entonces obligamos al for
	// a ubicar los vertices en las particiones libres.
	int p = 0;
	if(vertices_por_ubicar <= particiones_libres) p=K-particiones_libres;
	for (; p < k; p++){
		// Si estamos usando una particion nueva (vacia) actualizamos el proximo k
		// y la cantidad departiciones libres usadas para no contemplar casos con
		// menos de K particiones.
		int s_k = k;
		if (particiones[p].empty()){
			particiones_libres--;
			// Si k no supera el numero de particiones que queremos calcular,
			// el proximo llamado recursivo sera con k+1, para que el proximo
			// vertice tenga k+1 particiones para ubicarse.
			if (k < K) s_k++;
		}

		// Si esta rama supera el peso minimo calculado en alguna otra, cortamos.
		if (peso(particiones,m_ady) > peso_min) return;

		particiones[p].push_back(v);
		vertices_por_ubicar--;

		// Backtrack con el proximo vertice a ubicar en s_k conjuntos.
		backtrack(particiones, sol, m_ady, s_k, v+1, vertices_por_ubicar, K, particiones_libres);

		vertices_por_ubicar++;
		particiones[p].pop_back();
		if (particiones[p].empty()) particiones_libres++;
	}
	return;

	// Con fines de debug.
	//mostrarParticiones(particiones, m_ady, K);
	sterling++;
}

//n_candidatos es el beta que utilizamos para randomizar.
void golozo(vector< list<int> > & particiones, vector< vector <double> > & m_ady, int vertices_por_ubicar, int n_candidatos = 1){
	// Mientras me queden vertices por ubicar.
	int v = 1;
	int rand_offset = 1;
	while (v <= vertices_por_ubicar){ // O(n)
		// Si el algoritmo esta randomizado cargamos la lista de posibles candidatos.
		// n_candidatos <= k.
		list<unsigned int> candidatos;
		double peso_candidato_minimo = INF;

		for (unsigned int p = 0; p < particiones.size(); p++){ // O(k)
			particiones[p].push_back(v);
			double w = INF;
			if ((w = peso(particiones, m_ady)) < peso_candidato_minimo){ // O(n)
				// Si todavia no completamos la lista de candidatos simplemente lo agregamos.
				if (candidatos.size() < n_candidatos){
					candidatos.push_front(p);	// Agregamos el mas liviano adelante.
				} else {
					candidatos.push_front(p);	// Agregamos el mas liviano adelante.
					candidatos.pop_back();		// Sacamos el mas pesado de atras.
				}
				peso_candidato_minimo = w;
			}
			particiones[p].pop_back();
		}

		unsigned int particion_destino;
		if (candidatos.size() > 1){
			srand (time(NULL)+rand_offset);
			rand_offset++;
			unsigned int indice = rand() % n_candidatos;
			auto candidato = candidatos.begin();
			advance(candidato, indice);
			particion_destino = *candidato;
		} else {
			particion_destino = candidatos.front();
		}
		particiones[particion_destino].push_back(v);
		v++; // Proximo vertice a probar.
	}
}

void busquedaLocal(vector< list<int> > particiones, vector< list<int> > & sol, vector< vector<double> > & m_ady){
	double peso_minimo_local = peso(particiones, m_ady);
	double peso_mejor_particionado = peso_minimo_local;
	sol = particiones;
	do {
		particiones = sol;
		peso_minimo_local = peso_mejor_particionado;
		for (int p = 0; p < particiones.size(); p++){
			for(int i = 0; i < particiones[p].size(); i++){
				int vertice = particiones[p].front();
				particiones[p].pop_front();
				for(int particion_nueva = 0; particion_nueva < particiones.size(); particion_nueva++){
					if(particion_nueva == p) continue;
					particiones[particion_nueva].push_back(vertice);
					double w = peso(particiones,m_ady);
					if(w < peso_mejor_particionado){
						peso_mejor_particionado = w;
						sol = particiones;
					}
					particiones[particion_nueva].pop_back();
				}
				particiones[p].push_back(vertice);
			}
		}
	} while (peso_mejor_particionado < peso_minimo_local);
}

void mejorar(vector< list<int> > & sol, vector< vector<double> > & m_ady, vector< list<int> > & solucion_candidata, vector< list<int> > & solucion_inicial, double & peso_minimo, int N, int K, int rcl){
	solucion_candidata.clear();
	solucion_candidata.resize(K);
	solucion_inicial.clear();
	solucion_inicial.resize(K);

	golozo(solucion_inicial, m_ady, N, rcl);
	busquedaLocal(solucion_inicial, solucion_candidata, m_ady);
	double w = peso(sol, m_ady);
	if (w < peso_minimo) {
		peso_minimo = w;
		sol = solucion_candidata;
	}
}

void grasp(vector< list<int> > & sol, vector< vector<double> > & m_ady, int N, int K, int rcl, int iteraciones){
	vector< list<int> > solucion_inicial(K);
	vector< list<int> > solucion_candidata;
	double peso_minimo = INF;
	for(int i = 0; i < iteraciones; i++){
		mejorar(sol, m_ady, solucion_candidata, solucion_inicial, peso_minimo, N, K, rcl);
	}
}

void grasp(vector< list<int> > & sol, vector< vector<double> > & m_ady, 
	   int N, int K, int rcl, int iteraciones, double cociente_mejora){

	vector< list<int> > solucion_inicial(K);
	vector< list<int> > solucion_candidata;
	double peso_minimo = INF;
	bool seguir_iterando = true;
	while(seguir_iterando){
		double peso_minimo_anterior = peso_minimo;
		for( int i = 0; i < iteraciones; i++ )
			mejorar(sol, m_ady, solucion_candidata, solucion_inicial, peso_minimo, N, K, rcl);
		if( ( 1 - cociente_mejora ) *  peso_minimo <= peso_minimo_anterior) 
			seguir_iterando = false;
	}
}

typedef struct Opt{
	Opt():mostrar_tiempos(false), mostrar_solucion(false),
	      grasp_it(false), grasp_porcentaje(false), 
	      grasp_iteraciones(1), grasp_rcl(-1), grasp_cociente_mejora(0),
	      local(false), golozo(false), backtrack(false),
	      golozo_n_candidatos(1), cantidad_de_muestras_a_promediar(1){};

	bool mostrar_tiempos;
	bool mostrar_solucion;

	bool backtrack;
	bool local;
	
	bool golozo;
	int golozo_n_candidatos;

	bool grasp_it;
	int grasp_iteraciones;
	int grasp_rcl;

	bool grasp_porcentaje;
	double grasp_cociente_mejora;


	int cantidad_de_muestras_a_promediar;
} Opt;

void help(){
	cout << "ej1 <[-t] | [-s]> [-g n_candidatos] [-gr iteraciones rcl]" << endl 
	     << "     [-gri] [-grp cociente_mejora] [-b backtrack] [-l] [-m cantidad_de_muestras_a_promediar]" << endl << endl
	     << "recibe por entrada estandar una sola instancia a resolver por los algoritmos indicados en sus parámetros" << endl
	     << "todos los parámetros son opcionales pero hay que elegir al menos '-t' o '-s'" << endl 
	     << "no es importante el orden de los parámetros pero si el orden de los argumentos de cada parámetro, que son sin excepción obligatorios" << endl
	     << "\t" << "-t: muestra los tiempos" << endl
	     << "\t" << "-s: muestra las soluciones" << endl
	     << "\t" << "-g n_candidatos : parametro compartido del golozo,"<< endl 
	     << "\t" << "                 n_candidatos sirve para randomizar, por defecto vale 1, no randomiza" << endl
	     << "\t" << "-gr  iteraciones rcl : parametro que alimenta ambos grasps" << endl 
	     << "\t" << "     iteraciones : la cantidad de veces que se iterará grasp " << endl
	     << "\t" << "     rcl:         número que representa cuanto elementos tiene la lista restringuida de candidatos" << endl
	     << "\t" << "-gri : activa grasp acotado por iteraciones" << endl
	     << "\t" << "-gpr cociente_mejora : activa grasp acotado por cociente de mejora luego de cierta cantidad de iteraciones " << endl
	     << "\t" << "     cociente_mejora : valor entre 0 y 1" << endl
	     << "\t" << "-l : activa busqueda local" << endl
	     << "\t" << "-m cantidad_de_muestras a promediar" << endl;
		
}


ostream & operator<<(ostream & os, Opt & opt){
	os << "mostrar tiempos:                                        " << ( opt.mostrar_tiempos ? "true": "false" ) << endl 
	   << "mostrar solución:                                       " << ( opt.mostrar_solucion ? "true": "false" ) << endl 
	   << "cantidad de muestras a promediar:                       " << opt.cantidad_de_muestras_a_promediar << endl
	   << "ejecutar backtrack:                                     " << ( opt.backtrack ? "true": "false" ) << endl 
	   << "ejecutar golozo:                                        " << ( opt.golozo ? "true": "false" ) << endl;
	if( opt.golozo )
		os << "n candidatos (randomizacion) : " << opt.golozo_n_candidatos << endl;
	os << "ejecutar local:                                         " << ( opt.local ? "true": "false" ) << endl
	   << "ejecutar grasp acotado por iteraciones:                 " << ( opt.grasp_iteraciones ? "true" : "false") << endl;
	if( opt.grasp_iteraciones ){
		os << " iteraciones: " << opt.grasp_iteraciones << endl
		   << " rcl:         " << opt.grasp_rcl << endl;
	}
	os << "ejecutar grasp acotado por iteraciones y porcentaje:    " << ( opt.grasp_porcentaje ? "true" : "false") << endl;
	if( opt.grasp_porcentaje )
		os << " cociente de mejora: " << opt.grasp_cociente_mejora << endl;

		      return os;
}

void obtener_argumentos(Opt & opt, int argc, char * argv[]){
	for(int i = 1; i < argc; i ++){
		if( !strcmp(argv[i], "-b" ) ){
			opt.backtrack = true;
		}
		if( !strcmp(argv[i], "-t" ) ){
			opt.mostrar_tiempos = true;
		}
		if( !strcmp(argv[i], "-s" ) ){
			opt.mostrar_solucion = true;
		}
		if( !strcmp(argv[i], "-g" ) ){
			opt.golozo = true;
			opt.golozo_n_candidatos = atoi(argv[i+1]);
		}
		if( !strcmp(argv[i], "-m" ) ){
			opt.cantidad_de_muestras_a_promediar = atoi(argv[i+1]);
		}
		if( !strcmp(argv[i], "-gr") ){
			opt.grasp_iteraciones = atoi(argv[i+1]);
			opt.grasp_rcl = atoi(argv[i+2]);
		}
		if( !strcmp(argv[i], "-gri" ) ){
			opt.grasp_it = true;
		}
		if( !strcmp(argv[i], "-grp" ) ){
			opt.grasp_porcentaje = true;
			opt.grasp_cociente_mejora = atoi(argv[i+1]);
		}
		if( !strcmp(argv[i], "-l" ) ){
			opt.local = true;
		}
	}
	if( ! (opt.mostrar_tiempos || opt.mostrar_solucion) ){
		cout << "Debe o bien mostrar tiempos o mostrar soluciones... me niego trabajar en balde" << endl << endl;
		help();
		cout << endl << endl;
		cout << opt << endl;
		exit(1);
	}
}


int main(int argc, char * argv[]){

	Opt opciones;
	obtener_argumentos(opciones, argc, argv);

	int N, M, K, u, v;
	double w;
	cin >> N;
	cin >> M;
	cin >> K;

	// Matriz de adyacencias.
	vector< vector<double> > m_ady;
	for(int i = 0; i < N+1; i++){
		vector<double> v(N+1,-1);
		m_ady.push_back(v);
	}

	// K particiones de vertices.
	//	vector< list<int> > particiones(K);
	vector< list<int> > sol_golozo(K);
	vector< list<int> > sol_local(K);
	vector< list<int> > sol_grasp_it(K);
	vector< list<int> > sol_grasp_p(K);
	// Solucion de K particiones.
	vector< list<int> > particiones_backtack(K);
	vector< list<int> > sol_backtrack;

	for(int i = 0; i < M; i++){
		cin >> u;
		cin >> v;
		cin >> w;
		m_ady[v][u] = w;
	}

	sterling = 0;
	peso_min = INF;

	Reloj r_backtrack(CLOCK_PROCESS_CPUTIME_ID);
	Reloj r_golozo(CLOCK_PROCESS_CPUTIME_ID);
	Reloj r_local(CLOCK_PROCESS_CPUTIME_ID);
	Reloj r_grasp_it(CLOCK_PROCESS_CPUTIME_ID);
	Reloj r_grasp_p(CLOCK_PROCESS_CPUTIME_ID);
	vector<double> sol_pesos;

	for(int rep=0; rep < opciones.cantidad_de_muestras_a_promediar; rep ++){
		if(opciones.backtrack){
			// Algoritmo exacto.
			cerr << "BACKTRACK" << endl;
			r_backtrack(N);
			backtrack(particiones_backtack, sol_backtrack, m_ady, 1, 1, N, K, K);
			sol_pesos.push_back(peso(sol_backtrack, m_ady));
			r_backtrack(N);
		}
		if(opciones.golozo){
			cerr << "GOLOZO" << endl;
			r_golozo(N);
			golozo(sol_golozo, m_ady, N);
			sol_pesos.push_back(peso(sol_golozo, m_ady));
			r_golozo(N);
		}
		if(opciones.local){
			cerr << "LOCAL" << endl;
			r_local(N);
			golozo(sol_golozo, m_ady, N);
			busquedaLocal(sol_local, sol_golozo, m_ady);
			r_local(N);
		}
		if(opciones.grasp_it){
			cerr << "GRASP IT" << endl;
			r_grasp_it(N);
			grasp(sol_grasp_it, m_ady, N, K, opciones.grasp_rcl, opciones.grasp_iteraciones);
			r_grasp_it(N);
		}
		if(opciones.grasp_porcentaje){
			cerr << "GRASP PORCENTAJE" << endl;
			r_grasp_p(N);
			grasp(sol_grasp_p, m_ady, N, K, opciones.grasp_rcl, opciones.grasp_iteraciones, opciones.grasp_porcentaje);
			r_grasp_p(N);
		}
	}

	list<Reloj> relojes;
	if(opciones.backtrack){
		if(opciones.mostrar_solucion) mostrarParticiones(sol_backtrack, m_ady);
		if(opciones.mostrar_tiempos) relojes.push_back(r_backtrack);
	}
	if(opciones.golozo){
		if(opciones.mostrar_solucion) mostrarParticiones(sol_golozo, m_ady);
		if(opciones.mostrar_tiempos) relojes.push_back(r_golozo);
	}
	if(opciones.local){
		if(opciones.mostrar_solucion) mostrarParticiones(sol_local, m_ady);
		if(opciones.mostrar_tiempos) relojes.push_back(r_local);
	}
	if(opciones.grasp_it){	
		if(opciones.mostrar_solucion) mostrarParticiones(sol_grasp_it, m_ady);
		if(opciones.mostrar_tiempos) relojes.push_back(r_grasp_it);
	}
	if(opciones.grasp_porcentaje){
		if(opciones.mostrar_solucion) mostrarParticiones(sol_grasp_p, m_ady);
		if(opciones.mostrar_tiempos) relojes.push_back(r_grasp_p);
	}

	if(opciones.mostrar_tiempos)
		mostrarTiempos(relojes, sol_pesos, N, M, K);

	return 0;
}
