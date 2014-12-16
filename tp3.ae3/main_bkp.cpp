#include <iostream>
#include <vector>
#include <list>
#include <limits>
#include <stdlib.h>
#include <time.h>
using namespace std;
#define INF numeric_limits<double>::max()
int sterling; // Numero de Sterling con fines de debug.
double peso_min; // Peso minimo de la solucion encontrada.
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
void goloso(vector< list<int> > & particiones, vector< vector <double> > & m_ady, int vertices_por_ubicar, int n_candidatos = 1){
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
					candidatos.push_front(p); // Agregamos el mas liviano adelante.
				} else {
					candidatos.push_front(p); // Agregamos el mas liviano adelante.
					candidatos.pop_back(); // Sacamos el mas pesado de atras.
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
void mejorar(vector< list<int> > & sol, vector< vector<double> > & m_ady, vector< list<int> > & solucion_candidata, vector< list<int> > & solucion_inicial, double peso_minimo, int N, int K, int rcl){
	solucion_candidata.clear();
	solucion_candidata.resize(K);
	solucion_inicial.clear();
	solucion_inicial.resize(K);
	goloso(solucion_inicial, m_ady, N, rcl);
	busquedaLocal(solucion_inicial, solucion_candidata, m_ady);
	double w = peso(sol, m_ady);
	if (w < peso_minimo) {
		peso_minimo = w;
		sol = solucion_candidata;
	}
}
void grasp(vector< list<int> > & sol, vector< vector<double> > & m_ady, int N, int K, int rcl, int iteraciones, ){
	vector< list<int> > solucion_inicial(K);
	vector< list<int> > solucion_candidata;
	double peso_minimo = INF;
	bool seguir_iterando = true;
	while(seguir_iterando){
		double peso_minimo_anterior = peso_minimo;
		for(int i = 0; i < iteraciones; i++)
			mejorar(sol, m_ady, solucion_candidata, solucion_inicial, peso_minimo, N, K, rcl);
	}
}
void grasp(vector< list<int> > & sol, vector< vector<double> > & m_ady, int N, int K, int rcl, int iteraciones, ){
	vector< list<int> > solucion_inicial(K);
	vector< list<int> > solucion_candidata;
	double peso_minimo = INF;
	for(int i = 0; i < iteraciones; i++){
		mejorar(sol, m_ady, solucion_candidata, solucion_inicial, peso_minimo, N, K, rcl);
	}
}
int main(){
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
	vector< list<int> > particiones(K);
	// Solucion de K particiones.
	vector< list<int> > sol;
	for(int i = 0; i < M; i++){
		cin >> u;
		cin >> v;
		cin >> w;
		m_ady[v][u] = w;
	}
	sterling = 0;
	peso_min = INF;
	// Algoritmo exacto.
	cout << "BACKTRACK" << endl;
	backtrack(particiones, sol, m_ady, 1, 1, N, K, K);
	// Con fines de debug.
	cout << "sterling: " << sterling << endl;
	mostrarParticiones(sol, m_ady);
	cout << "peso: " << peso(sol,m_ady) << endl;
	cout << endl;
	// Algoritmo goloso.
	cout << "GOLOSO" << endl;
	particiones.clear(); //TODO: Sacar! Hago esto para correrlo despues del backtrack.
	particiones.resize(K); //TODO: Sacar! Hago esto para correrlo despues del backtrack.
	sol.clear(); //TODO: Sacar! Hago esto para correrlo despues del backtrack.
	goloso(particiones, m_ady, N);
	mostrarParticiones(particiones, m_ady);
	cout << endl;
	// Algoritmo goloso randomizado.
	cout << "GOLOSO RANDOM" << endl;
	particiones.clear(); //TODO: Sacar! Hago esto para correrlo despues del goloso.
	particiones.resize(K); //TODO: Sacar! Hago esto para correrlo despues del goloso.
	sol.clear(); //TODO: Sacar! Hago esto para correrlo despues del goloso.
	goloso(particiones, m_ady, N, 2);
	mostrarParticiones(particiones, m_ady);
	cout << endl;
	// Algoritmo de busqueda local.
	cout << "Algoritmo de busqueda local" << endl;
	particiones.clear(); //TODO: Sacar! Hago esto para correrlo despues del goloso.
	particiones.resize(K); //TODO: Sacar! Hago esto para correrlo despues del goloso.
	sol.clear(); //TODO: Sacar! Hago esto para correrlo despues del goloso.
	// Corro un goloso para generar la sol inicial.
	goloso(particiones, m_ady, N, 2);
	busquedaLocal(particiones, sol, m_ady);
	mostrarParticiones(sol, m_ady);
	cout << endl;
	cout << "GRASP" << endl;
	particiones.clear(); //TODO: Sacar! Hago esto para correrlo despues de busqueda local.
	particiones.resize(K); //TODO: Sacar! Hago esto para correrlo despues de busqueda local.
	sol.clear(); //TODO: Sacar! Hago esto para correrlo despues de busqueda local.
	grasp(particiones, m_ady, N, K, 2, 2);
	mostrarParticiones(particiones, m_ady);
	return 0;
}
