#include <stdio.h>
#include <stdlib.h>

/*------------- estructura de datos -------------*/

typedef struct nodoGenerico
{
  int dato;
  struct nodoGenerico* siguiente;
}nodo;


typedef struct
{
	int capacidad;
	int size;
	nodo* frente;
	nodo* fin;
}TDAcola;



TDAcola* crearColaVacia(int capacidad)
{
	TDAcola *cola=(TDAcola*)malloc(sizeof(TDAcola));
	cola->capacidad=capacidad;
	cola->size=0;
	cola->frente=NULL;
	cola->fin=NULL;
	return cola;
}

int esColaVacia(TDAcola* cola)
{
	if (cola->size == 0)
    	return 1;
	else
    	return 0;
}

void encolar(TDAcola* cola, int dato){
	//ver si el tamaño es menor a la capacidad
	if (cola->size < cola->capacidad){
		nodo* aux=(nodo*)malloc(sizeof(nodo));
		aux->dato=dato;
		aux->siguiente=NULL;
		//si la cola esta vacia		
		if (esColaVacia(cola)==1){
			cola->frente=aux;
		}else{
			cola->fin->siguiente=aux;
		}
		//actualizar el fin
		cola->fin=aux;
		cola->size++;
	}
}


void desencolar(TDAcola* cola){
	//verificar el tamano de la cola es distinto de cero.
	if (cola->size!=0){
		//generar nodo aux
		nodo* aux=cola->frente;
		cola->frente= cola->frente->siguiente;
		free(aux);	
		cola->size= cola->size-1;
	}	
}

//obtener frente
nodo* frente(TDAcola* cola){
	return (cola->frente);
}

//buscar el dato de un elemento de una cola.
int buscarDatoCola(TDAcola* cola, int dato){
	nodo* aux=cola->frente;
	int i=0;
	while (aux!=NULL){
		if (aux->dato==dato){
			return i;
		}
		aux=aux->siguiente;
		i++;
	}
	return -1;
}
