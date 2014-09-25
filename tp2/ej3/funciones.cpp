// Declaraciones en el archivo .h


void resolver(int cantCompus, int cantEnlaces, Red& red){


    Enlace aristaParaCiclo = new Enlace();
    
    //Primero ordeno la red por peso en O(n*log(n))
    // http://www.cplusplus.com/reference/algorithm/sort/?kw=sort
    sort(red.begin(), red.end(), esMayorEnlace);


    //Obtengo el AGM a partir de la red.
    MatrizAdyacencia agm = kruskal(cantCompus, *red, *aristaParaCiclo);
    int cantEnlacesEnCamino;

    //Aplicar BFS en agm, empezando en algunas de las compus de aristaParaCiclo
    //este BFS debe ir guardando el antecesor para despues reconstruir el camino de una compu a la otra
    //A medida que reconstruimos el camino, guardarlo en un vector para mostrarlo

}


// Comparador de el struct Enlace.
bool esMayorEnlace(const Enlace& a, const Enlace& b)
{
    return a.costo > b.costo;
}

 
// Devuelve la matriz de adyacencia del árbol mínimo.
// Debe recibir la red ordenada por peso de menor a mayor.
MatrizAdyacencia kruskal(int cantCompus, Red& red, Enlace& menorEnlaceExcluido){
    Red redOrdenada = red;
    MatrizAdyacencia agm(cantCompus);
    vector<int> pertenece(cantCompus); // indica a que árbol pertenece el nodo
 
    for(int i = 0; i < cantCompus; i++){
        agm[i] = vector<int> (cantCompus, 0);
        pertenece[i] = i;
    }
 
    int compu1;
    int compu2;
    int costo;
    int cantAristas = 1;
    int posicionEnRed = 0;

//    Enlace menorEnlaceExcluido;
    bool noEncontreEnlaceExcluido = true;

    while(cantAristas < cantCompus){
        compu1 = redOrdenada[posicionEnRed].compu1;
        compu2 = redOrdenada[posicionEnRed].compu2;
        costo = redOrdenada[posicionEnRed].costo;
        posicionEnRed++;

        // Si los nodos no pertenecen al mismo árbol agrego la arista al árbol mínimo.
        if(pertenece[compu1] != pertenece[compu2]){
            agm[compu1][compu2] = costo;
            agm[compu2][compu1] = costo;
 
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
    return agm;
}


void imprimirResultado(int costoTotal, int cantEnlacesEnCamino, int canEnlacesFuera, Red anilloServidores, Red compusEnRed){

    if(costoTotal == 0){
        cout << "no";// << endl;
    }else{
        cout << costoTotal << " " << cantEnlacesEnCamino << " " << canEnlacesFuera << endl;

        for (int i = 0; i < cantEnlacesEnCamino; ++i){
            cout << anilloServidores[i].compu1 << " " << anilloServidores[i].compu2 << endl;
        }

        for (int i = 0; i < canEnlacesFuera; ++i){
            cout << compusEnRed[i].compu1 << " " << compusEnRed[i].compu2 << endl;
        }
    }
    cout << endl;    
}