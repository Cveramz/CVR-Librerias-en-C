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
  int capacidad; //capacidad de la pila
  int size; //cantidad de elementos
  nodo* tope;
}TDApila;

/*------------- operaciones -------------*/

TDApila* crearPilaVacia(int capacidad)
{
  TDApila* pila=(TDApila*)malloc(sizeof(TDApila));
  pila->capacidad=capacidad;
  pila->size=0;
  pila->tope=NULL;
  return pila;
}

int esPilaVacia(TDApila* pila)
{
  if (pila->size == 0)
  {
    return 1;
  }else{
    return 0;
  }
}



void apilar(TDApila* pila, int dato){
  if(pila->size < pila->capacidad){
  nodo* nuevo=(nodo*)malloc(sizeof(nodo));
  nuevo->dato=dato;
  nuevo->siguiente=pila->tope;
  pila->tope=nuevo;
  pila->size++;
  }else{
    printf("Pila llena, el elemento %d no se pudo apilar\n",dato);
  }

}

void desapilar(TDApila* pila){
  if(pila->size ==0){
    printf("***No se puede desapilar, pila vacia\n");
  }else{
    printf("Desapilando...\n");
    nodo* aux=pila->tope;
    pila->tope=aux->siguiente;
    pila->size--;
    free(aux);
  }
}

nodo* tope(TDApila* pila){
  if(pila->size ==0){
    printf("***No se puede obtener tope, lista vacia.\n");
  }else{
  return (pila->tope);
  }
}

int buscarDatoPila(TDApila* pila, int dato){
  if(esPilaVacia(pila)==1){
    printf("Pila vacia\n");
    return 0;
  }else{
	TDApila* pila_aux=crearPilaVacia(pila->size);
  pila_aux=pila;
  int datoAux;
    while (esPilaVacia(pila_aux)==0){
      datoAux=pila_aux->tope->dato;
      desapilar(pila_aux);
      if(datoAux==dato){
        return 1;
      }
    }
  }
  return 0;
}
