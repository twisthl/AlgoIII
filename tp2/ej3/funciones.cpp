// Declaraciones en el archivo .h

MatrizAdyacencia ady; //matriz de adyacencia
 
// Devuelve la matriz de adyacencia del árbol mínimo.
vector< vector<int> > kruskal(int cantCompus, Red red){
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

    Enlace menorEnlaceExcluido;
    bool noEncontreEnlaceExcluido = true;

    //FALTA ORDENAR LA LISTA DE CONEXIONES POR PESO DE MENOR A MAYOR redOrdenada

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

        // Encontrar  el arco mínimo que no forma ciclo y guardar los nodos y la distancia.
        int min = INF;
        for(int i = 0; i < cantCompus; i++)
            for(int j = 0; j < cantCompus; j++)
                if(min > red[i][j] && red[i][j]!=0 && pertenece[i] != pertenece[j]){
                    min = red[i][j];
                    compu1 = i;
                    compu2 = j;
                }
