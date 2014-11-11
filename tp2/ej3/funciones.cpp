// Declaraciones en el archivo .h
#include "ej3.h"

void resolver(int cantCompus, int cantEnlaces, Red& red){


    Enlace * conexionAnillo = new Enlace();

    vector<int> aux(cantCompus);

    ListaAdyacencia * agmL = new ListaAdyacencia(cantCompus, aux);
    MatrizAdyacencia agmM;
    vector<int> conexionesAnillo;
 //   Red * conexionesRestantes = new Red();
    int costoTotal;
    
    //Primero ordeno la red por peso en O(n*log(n))
    // http://www.cplusplus.com/reference/algorithm/sort/?kw=sort
    sort(red.begin(), red.end(), esMayorEnlace);


    //Obtengo el AGM a partir de la red.
    agmM = kruskal(cantCompus, cantEnlaces, red, *conexionAnillo, *agmL,& costoTotal);
    if (costoTotal == 0){
        cout << "no";
        //return 0;
    }

//    conexionesAnillo = bfs(agmL, conexionAnillo.compu1, conexionAnillo.compu2, *conexionesRestantes);

    conexionesAnillo = bfs(*agmL, conexionAnillo->compu1, cantCompus - 1);

    Red * anilloServidores = new Red();
    Red * compusEnRed = new Red();

    obtenerServidoresYRed(*anilloServidores, *compusEnRed, conexionesAnillo, conexionAnillo->compu1, conexionAnillo->compu2);

    int cantEnlacesEnCamino = anilloServidores->size();
    int cantEnlacesFuera = compusEnRed->size();

    imprimirResultado(costoTotal, cantEnlacesEnCamino, cantEnlacesFuera, *anilloServidores, *compusEnRed);


}

void obtenerServidoresYRed(Red& anilloServidores, Red& compusEnRed, vector<int> conexionesAnillo, int desde, int hasta){

    Enlace enlace;
    while (conexionesAnillo[hasta] != -1){
        enlace.compu1 = hasta;
        enlace.compu2 = conexionesAnillo[hasta];
        enlace.costo = 0;
        anilloServidores.push_back(enlace);
        
        int viejoHasta = hasta;
        hasta = conexionesAnillo[hasta];
        conexionesAnillo[viejoHasta] = -1;
    }

    for (unsigned int i = 0; i < conexionesAnillo.size(); ++i){
        if (conexionesAnillo[i] != -1){
            enlace.compu1 = i;
            enlace.compu2 = conexionesAnillo[i];
            enlace.costo = 0;
            compusEnRed.push_back(enlace);
        }
    }


}


// Comparador de el struct Enlace.
bool esMayorEnlace(const Enlace& a, const Enlace& b)
{
    return a.costo < b.costo;
}

 
// Devuelve la matriz de adyacencia del árbol mínimo.
// Debe recibir la red ordenada por peso de menor a mayor.
MatrizAdyacencia kruskal(int cantCompus, int cantTotalAristas, Red& red, Enlace& menorEnlaceExcluido, ListaAdyacencia& agmL, int* costoTotal){
    Red redOrdenada = red;
    MatrizAdyacencia agm(cantCompus);
    vector<int> pertenece(cantCompus); // indica a que árbol pertenece el nodo
//    ListaAdyacencia agmL(cantCompus);
 
    for(int i = 0; i < cantCompus; i++){
        agm[i] = vector<int> (cantCompus, 0);
        pertenece[i] = i;
    }
 
    int compu1;
    int compu2;
    int costo;
    int cantAristas = 1;
    int posicionEnRed = 0;
    int cantAristasVisitadas = 0;
    costoTotal = 0;

//    Enlace menorEnlaceExcluido;
    bool noEncontreEnlaceExcluido = true;

    while(cantAristas < cantCompus && cantAristas <= cantTotalAristas){
        compu1 = redOrdenada[posicionEnRed].compu1;
        compu2 = redOrdenada[posicionEnRed].compu2;
        costo = redOrdenada[posicionEnRed].costo;
        posicionEnRed++;
        cantAristasVisitadas++;

        // Si los nodos no pertenecen al mismo árbol agrego la arista al árbol mínimo.
        if(pertenece[compu1] != pertenece[compu2]){
            agm[compu1][compu2] = costo;
            agm[compu2][compu1] = costo;
            costoTotal = costoTotal + costo;

            agmL[compu1].push_back(compu2);
            agmL[compu2].push_back(compu1);
 
            // Todos los nodos del árbol del compu2 ahora pertenecen al árbol del compu1.
        	int temp = pertenece[compu2];
        	pertenece[compu2] = pertenece[compu1];
        	for(int k = 0; k < cantCompus; k++)
        		if(pertenece[k] == temp)
        			pertenece[k] = pertenece[compu1];
 
            cantAristas++;
        }else{
            if(noEncontreEnlaceExcluido){
                menorEnlaceExcluido.compu1 = compu1;
                menorEnlaceExcluido.compu2 = compu2;
                menorEnlaceExcluido.costo = costo;
                noEncontreEnlaceExcluido = false;
            }
        }
    }
    if(cantAristas < cantCompus - 1){
        costoTotal=0;
        return agm;
    }
    return agm;
}


void imprimirResultado(int costoTotal, int cantEnlacesEnCamino, int cantEnlacesFuera, Red anilloServidores, Red compusEnRed){

    if(costoTotal == 0){
        cout << "no";// << endl;
    }else{
        cout << costoTotal << " " << cantEnlacesEnCamino << " " << cantEnlacesFuera << endl;

        for (int i = 0; i < cantEnlacesEnCamino; ++i){
            cout << anilloServidores[i].compu1 << " " << anilloServidores[i].compu2 << endl;
        }

        for (int i = 0; i < cantEnlacesFuera; ++i){
            cout << compusEnRed[i].compu1 << " " << compusEnRed[i].compu2 << endl;
        }
    }
    cout << endl;    
}

//Red conexionesAnillo = bfs(agmL, conexionAnillo.compu1, conexionAnillo.compu2, *conexionesRestantes);



vector<int> bfs(ListaAdyacencia agm, int desde, int cantAristas)
{
    std::vector<bool> visitado(cantAristas);
    std::vector<int> lPadres(cantAristas+1);
    for(int i = 0; i < cantAristas; i++)
        visitado[i] = false;
 
    visitado[desde] = true;

    list<int> cola;
    cola.push_back(desde);
 
    vector<int>::iterator i;
    int s;
    while(!cola.empty())
    {
        // Dequeue a vertex from cola and print it
        s = cola.front();
//        cout << s << " ";
        cola.pop_front();
 
        // Get all adjacent vertices of the dequeued vertex s
        // If a adjacent has not been visited, then mark it visited
        // and enqueue it
        for(i = agm[s].begin(); i != agm[s].end(); ++i)
        {
            if(!visitado[*i])
            {
                lPadres[*i] = s;
                visitado[*i] = true;
                cola.push_back(*i);
            }
        }
    }
    return lPadres;
}