#include <stdio.h>
#include <stdlib.h>

/*#include "TDAlista.h"
#include "TDApila.h"
#include "TDAcola.h"
[ESTOS ARCHIVOS ESTÁN DISPONIBLES EN REPOSITORIO].*/

/*------------- estructura de datos -------------*/



typedef struct matrizGrafo 
{
	int cvertices;
	int** adyacencias;
}TDAgrafo;


/*----------------- operaciones -----------------*/

TDAgrafo* crearGrafoVacio(int vertices) 
{
	TDAgrafo* grafo = (TDAgrafo*)malloc(sizeof(TDAgrafo));
	grafo->cvertices = vertices;
	grafo->adyacencias = (int**)malloc(vertices * sizeof(int*));
	int i,j;
	for (i = 0; i < vertices; i++) 
	{
		grafo->adyacencias[i] = (int*)malloc(vertices * sizeof(int));
		//Inicializa en cero
		for(j=0;j<vertices;j++){
			grafo->adyacencias[i][j] = 0;
		}	
	}
	return grafo;
}

void imprimirMatrizAdyacencia(TDAgrafo* grafo) 
{
	int i, j;
	
	for (i = 0; i < grafo->cvertices; i++) 
	{
		for (j = 0; j < grafo->cvertices; j++) 
		{
			printf("%d ", grafo->adyacencias[i][j]);
		}
		printf("\n");
	}
}

int adyacenciaNodos(TDAgrafo * grafo, int vertA, int vertB) 
{
	if (grafo->adyacencias[vertA - 1][vertB - 1] == 1) 
	{
		return 1;
	}
	return 0;
}

TDAgrafo* leerGrafo(char *nombreArchivo){
	FILE*pf;		   //para abrir archivo
	pf = fopen(nombreArchivo,"r");
	int n, aristas;
	int i,j,k;
	fscanf(pf, "%d %d", &n,&aristas); //Cantidad de nodos y aristas
	TDAgrafo *g=crearGrafoVacio(n);
	//dependiendo de las lineas de archivo , pone 1 para grafo no dirigido
	for(k=0;k<aristas;k++){
		fscanf(pf,"%d %d",&i, &j);
		g->adyacencias[i-1][j-1] = 1;
		g->adyacencias[j-1][i-1] = 1;
	}
	fclose(pf);
	return  g;	
}

TDAlista * obtenerAdyacentes(TDAgrafo * grafo, int vertice){
	//generar nueva lista
	TDAlista * aux = crearListaVacia();
	for(int i = 1; i<= grafo->cvertices;i++){
		if(adyacenciaNodos(grafo, vertice, i)){
			insertarInicio(aux,i);
		}
	}
	return(aux);
}


int EsCamino( TDAgrafo* grafo, TDAlista* secuencia ){
	if(!esListaVacia(secuencia)){
		nodo * Auxiliar = secuencia->inicio;
		while(Auxiliar->siguiente!=NULL){
			if(!adyacenciaNodos(grafo, Auxiliar->dato, Auxiliar->siguiente->dato)){
				return(0);
			}
			Auxiliar = Auxiliar->siguiente;
		}
	}
	return(1);
}


int EsCiclo( TDAgrafo* grafo, TDAlista* secuencia){
	int NodoInicial;
	int NodoFinal;
	if(!esListaVacia(secuencia)){
		nodo * Auxiliar = secuencia->inicio;
		NodoInicial = Auxiliar->dato;
		while(Auxiliar->siguiente!=NULL){
			Auxiliar = Auxiliar->siguiente;
		}
		NodoFinal = Auxiliar->dato;
		if(NodoInicial!=NodoFinal){
			return(0);
		}else{
			if(!EsCamino(grafo, secuencia)){
				return(0);
			}
		}
	}
	return(1);
}


//BSF=RECORRIDO POR ANCHURA



//crear función de para recorrido por anchura
void BSF(TDAgrafo *grafo, int v){
	printf("Recorrido por anchura desde  %d\n",v);
	int i;
	int *visitados = (int*)malloc(grafo->cvertices * sizeof(int));
	for(i=0;i<grafo->cvertices;i++){
		visitados[i] = 0;
	}
	TDAcola *cola = crearColaVacia(grafo->cvertices);
	encolar(cola,v);
	visitados[v-1] = 1;
	//generar nodo frente
	nodo *frente;
	frente = cola->frente;
	while(!esColaVacia(cola)){
		frente = cola->frente;
		printf("%d ",frente->dato);
		desencolar(cola);
		TDAlista *adyacentes = obtenerAdyacentes(grafo,frente->dato);
		nodo *aux = adyacentes->inicio;
		while(aux!=NULL){
			if(!visitados[aux->dato-1]){
				encolar(cola,aux->dato);
				visitados[aux->dato-1] = 1;
			}
			aux = aux->siguiente;
		}
	}
	printf("\n");
}


//DFS=RECORRIDO POR PROFUNDIDAD
void DFS(TDAgrafo *grafo, int v){
	printf("===============================\n");
	printf("Recorrido de profundidad desde %d\n",v);
	nodo* u;
	int *visitados;
	TDAlista* lista;
	nodo *ptr=NULL;
	//arreglo de visitados con valor inicial 0
	visitados= (int *) malloc(grafo->cvertices*sizeof(int));
	for (int i=0; i<grafo->cvertices; i++){
		visitados[i]=0;
	}
	TDApila* S=crearPilaVacia(3* grafo->cvertices); //aprox el 3
	apilar(S,v);
	while (esPilaVacia(S)==0){
		u=tope(S);
		desapilar(S);
		//printf("DATO-1: %d",u->dato-1);
		if (visitados[u->dato-1]==0){
			visitados[u->dato-1]=1;
			printf("%d ",u->dato);
			lista=obtenerAdyacentes(grafo,u->dato);
			ptr=lista->inicio;
			while (ptr!=NULL){
				if (visitados[ptr->dato-1]==0){
					apilar(S,ptr->dato);
				}
				ptr=ptr->siguiente;
			}
		}
	}
}



