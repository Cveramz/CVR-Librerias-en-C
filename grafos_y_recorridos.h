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
	int **adyacencias;
} TDAgrafo;

/*----------------- operaciones -----------------*/

TDAgrafo *crearGrafoVacio(int vertices)
{
	TDAgrafo *grafo = (TDAgrafo *)malloc(sizeof(TDAgrafo));
	grafo->cvertices = vertices;
	grafo->adyacencias = (int **)malloc(vertices * sizeof(int *));
	int i, j;
	for (i = 0; i < vertices; i++)
	{
		grafo->adyacencias[i] = (int *)malloc(vertices * sizeof(int));
		// Inicializa en cero
		for (j = 0; j < vertices; j++)
		{
			grafo->adyacencias[i][j] = 0;
		}
	}
	return grafo;
}

void imprimirMatrizAdyacencia(TDAgrafo *grafo)
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

int adyacenciaNodos(TDAgrafo *grafo, int vertA, int vertB)
{
	if (grafo->adyacencias[vertA - 1][vertB - 1] == 1)
	{
		return 1;
	}
	return 0;
}

TDAgrafo *leerGrafoNoDirigido(char *nombreArchivo)
{
	FILE *pf; // para abrir archivo
	pf = fopen(nombreArchivo, "r");
	int n, aristas;
	int i, j, k;
	fscanf(pf, "%d %d", &n, &aristas); // Cantidad de nodos y aristas
	TDAgrafo *g = crearGrafoVacio(n);
	// dependiendo de las lineas de archivo , pone 1 para grafo no dirigido
	for (k = 0; k < aristas; k++)
	{
		fscanf(pf, "%d %d", &i, &j);
		g->adyacencias[i - 1][j - 1] = 1;
		g->adyacencias[j - 1][i - 1] = 1;
	}
	fclose(pf);
	return g;
}

TDAlista *obtenerAdyacentes(TDAgrafo *grafo, int vertice)
{
	// generar nueva lista
	TDAlista *aux = crearListaVacia();
	for (int i = 1; i <= grafo->cvertices; i++)
	{
		if (adyacenciaNodos(grafo, vertice, i))
		{
			insertarInicio(aux, i);
		}
	}
	return (aux);
}

int EsCamino(TDAgrafo *grafo, TDAlista *secuencia)
{
	if (!esListaVacia(secuencia))
	{
		nodo *Auxiliar = secuencia->inicio;
		while (Auxiliar->siguiente != NULL)
		{
			if (!adyacenciaNodos(grafo, Auxiliar->dato, Auxiliar->siguiente->dato))
			{
				return (0);
			}
			Auxiliar = Auxiliar->siguiente;
		}
	}
	return (1);
}

int EsCiclo(TDAgrafo *grafo, TDAlista *secuencia)
{
	int NodoInicial;
	int NodoFinal;
	if (!esListaVacia(secuencia))
	{
		nodo *Auxiliar = secuencia->inicio;
		NodoInicial = Auxiliar->dato;
		while (Auxiliar->siguiente != NULL)
		{
			Auxiliar = Auxiliar->siguiente;
		}
		NodoFinal = Auxiliar->dato;
		if (NodoInicial != NodoFinal)
		{
			return (0);
		}
		else
		{
			if (!EsCamino(grafo, secuencia))
			{
				return (0);
			}
		}
	}
	return (1);
}

// BSF=RECORRIDO POR ANCHURA
// crear función de para recorrido por anchura
void BSF(TDAgrafo *grafo, int v)
{
	printf("Recorrido por anchura desde  %d\n", v);
	int i;
	int *visitados = (int *)malloc(grafo->cvertices * sizeof(int));
	for (i = 0; i < grafo->cvertices; i++)
	{
		visitados[i] = 0;
	}
	TDAcola *cola = crearColaVacia(grafo->cvertices);
	encolar(cola, v);
	visitados[v - 1] = 1;
	// generar nodo frente
	nodo *frente;
	frente = cola->frente;
	while (!esColaVacia(cola))
	{
		frente = cola->frente;
		printf("%d ", frente->dato);
		desencolar(cola);
		TDAlista *adyacentes = obtenerAdyacentes(grafo, frente->dato);
		nodo *aux = adyacentes->inicio;
		while (aux != NULL)
		{
			if (!visitados[aux->dato - 1])
			{
				encolar(cola, aux->dato);
				visitados[aux->dato - 1] = 1;
			}
			aux = aux->siguiente;
		}
	}
	printf("\n");
}

// DFS=RECORRIDO POR PROFUNDIDAD
void DFS(TDAgrafo *grafo, int v)
{
	printf("===============================\n");
	printf("Recorrido de profundidad desde %d\n", v);
	nodo *u;
	int *visitados;
	TDAlista *lista;
	nodo *ptr = NULL;
	// arreglo de visitados con valor inicial 0
	visitados = (int *)malloc(grafo->cvertices * sizeof(int));
	for (int i = 0; i < grafo->cvertices; i++)
	{
		visitados[i] = 0;
	}
	TDApila *S = crearPilaVacia(3 * grafo->cvertices); // aprox el 3
	apilar(S, v);
	while (esPilaVacia(S) == 0)
	{
		u = tope(S);
		desapilar(S);
		// printf("DATO-1: %d",u->dato-1);
		if (visitados[u->dato - 1] == 0)
		{
			visitados[u->dato - 1] = 1;
			printf("%d ", u->dato);
			lista = obtenerAdyacentes(grafo, u->dato);
			ptr = lista->inicio;
			while (ptr != NULL)
			{
				if (visitados[ptr->dato - 1] == 0)
				{
					apilar(S, ptr->dato);
				}
				ptr = ptr->siguiente;
			}
		}
	}
}


TDAlista *encontrarCamino(TDAgrafo *grafo, int vertice, int verticeFinal)
{
	nodo *u;
	int *visitados;
	TDAlista *lista;
	nodo *ptr = NULL;
	// arreglo de visitados con valor inicial 0
	visitados = (int *)malloc(grafo->cvertices * sizeof(int));
	for (int i = 0; i < grafo->cvertices; i++)
	{
		visitados[i] = 0;
	}

	// variación a DFS para encontrar camino
	TDAlista *camino = crearListaVacia();
	int *antecesor = (int *)malloc(sizeof(int) * grafo->cvertices);
	for (int c = 0; c < (grafo->cvertices); c++)
		antecesor[c] = -1;

	TDApila *S = crearPilaVacia(3 * grafo->cvertices); // aprox el 3  //S ← crearPilaVacia()
	apilar(S, vertice);
	int fincamino = 0;
	while ((esPilaVacia(S) == 0) && (fincamino == 0))
	{
		u = tope(S);
		desapilar(S);
		if (visitados[(u->dato) - 1] == 0)
		{
			visitados[(u->dato) - 1] = 1;
			// printf(" %d ",u->dato);
			if (u->dato != verticeFinal)
			{
				lista = obtenerAdyacentes(grafo, u->dato);
				ptr = lista->inicio;
				while (ptr != NULL)
				{
					if (visitados[ptr->dato - 1] == 0)
					{
						apilar(S, ptr->dato);
						antecesor[ptr->dato] = u->dato; // variación a DFS para encontrar camino
					}
					ptr = ptr->siguiente;
				}
			}
			else
			{
				fincamino = 1;
			}
		}
	}
	free(lista);

	// se recupera camino desde verticeFinal usando antecesor
	int w;
	insertarInicio(camino, verticeFinal);
	w = verticeFinal;
	while (antecesor[w] != -1)
	{
		if (antecesor[w] != -1)
		{
			insertarInicio(camino, antecesor[w]);
		}
		w = antecesor[w];
	}
	return camino;
}

// NoDirigido Ponderado
TDAgrafo *leerGrafoNoDirigidoPonderado(char *nombreArchivo)
{
	FILE *pf; // para abrir archivo
	pf = fopen(nombreArchivo, "r");
	int n_vertices, m_aristas;
	int i, j, w, k;
	if (pf == NULL)
	{
		printf("Error de archivo\n");
		return NULL;
	}
	else
	{
		// Cantidad de nodos y aristas
		fscanf(pf, "%d %d", &n_vertices, &m_aristas);
		TDAgrafo *G = crearGrafoVacio(n_vertices);
		// dependiendo de las lineas de archivo,
		//  1 para grafo no dirigido no ponderado
		for (k = 0; k < m_aristas; k++)
		{
			fscanf(pf, "%d %d %d", &i, &j, &w);
			G->adyacencias[i - 1][j - 1] = w;
			G->adyacencias[j - 1][i - 1] = w;
		}
		fclose(pf);
		return G;
	}
}

int ExistenVerticesSinVisitar(TDAgrafo *G)
{
	for (int p = 0; p < G->cvertices; p++)
	{
		for (int l; l < G->cvertices; l++)
		{
			if (G->adyacencias == 0)
			{
				return 1;
			}
		}
	}
	return 0;
}
int extraerMinimo(int *distancias, int *visitados, int tamano)
{
	int menor = distancias[0];
	int Id;
	for (int t = 0; t < tamano; t++)
	{
		if (distancias[t] < menor && visitados[t] == 0)
		{
			menor = distancias[t];
			Id = t;
		}
	}
	return Id;
}

void Dijkstra(TDAgrafo *G, int inicio)
{
	int n = G->cvertices;
	int *antecesor = (int *)malloc(sizeof(int) * n);
	int *visitados = (int *)malloc(sizeof(int) * n);
	int *distancias = (int *)malloc(sizeof(int) * n);
	for (int i = 1; i < n; i++)
	{
		visitados[i] = 0;
		antecesor[i] = -1;
		if ((G->adyacencias[inicio][i]) > 0)
		{
			distancias[i] = (G->adyacencias[inicio][i]);
			antecesor[i] = inicio;
		}
		else
		{
			distancias[i] = INT_MAX; // esto viene de la libreria limits.h
		}
		visitados[inicio] = 1;
		distancias[inicio] = 0;
		while (ExistenVerticesSinVisitar(G) == 1)
		{
			int u = extraerMinimo(distancias, visitados, n);
			nodo *aux = NULL;
			visitados[u] = 1;
			TDAlista *lista = obtenerAdyacentes(G, u);
			aux = lista->inicio;
			while (aux != NULL)
			{
				int w = aux->dato;
				if (distancias[w] > distancias[u] + G->adyacencias[u][w])
				{
					distancias[w] = distancias[u] + G->adyacencias[u][w];
					antecesor[w] = u;
				}
				aux = aux->siguiente;
			}
		}
	}
	free(antecesor);
	free(visitados);
	free(distancias);
}


