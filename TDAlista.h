#include <stdio.h>
#include <stdlib.h>

/*------------- estructura de datos -------------*/

typedef struct nodoGenerico
{
  int dato;
  struct nodoGenerico* siguiente;
}nodo;

typedef struct listaGenerica
{
  nodo* inicio;
}TDAlista;


/*------------- operaciones -------------*/

TDAlista* crearListaVacia()
{
  TDAlista* lista=(TDAlista*)malloc(sizeof(TDAlista));
  lista->inicio=NULL;
  return lista;
}

int esListaVacia(TDAlista* lista)
{
  if (lista->inicio == NULL)
    return 1;
  else
    return 0;
}

void recorrerLista(TDAlista* lista)
{
  if (!esListaVacia(lista))
  {
    nodo* auxiliar=lista->inicio;
    while (auxiliar!=NULL)
    {
      printf("%d ",auxiliar->dato);
      auxiliar=auxiliar->siguiente;
    }
    printf("\n");
  }
  else
    printf("La lista está vacia\n");
}

void insertarInicio(TDAlista* lista, int dato)
{
  nodo* nuevo=(nodo*)malloc(sizeof(nodo));
  nuevo->dato=dato;
  nuevo->siguiente = lista->inicio;
  lista->inicio=nuevo;
}

void eliminarInicio(TDAlista* lista)
{
  nodo* auxiliar;
  if(!esListaVacia(lista))
  {
    auxiliar=lista->inicio;
    lista->inicio=lista->inicio->siguiente;
    free(auxiliar);
  }
}


/*------------- Actividad 2 -------------*/
void liberarLista(TDAlista* lista){
  while(!esListaVacia(lista)){
    eliminarInicio(lista);
  }
}


int buscarDato(TDAlista* lista, int dato){
  if (!esListaVacia(lista))
  {
    nodo* auxiliar=lista->inicio;
    while (auxiliar!=NULL)
    {
      if (dato==auxiliar->dato){
        return 1;
      }
      auxiliar=auxiliar->siguiente;
    }
    free(auxiliar);
  }
  else{
    printf("La lista está vacia\n");
  }
  return 0;
}


int obtenerNumeroNodos(TDAlista* lista){
  int contador=0;
  if (!esListaVacia(lista))
  {
    nodo* auxiliar=lista->inicio;
    while (auxiliar!=NULL)
    {
      contador++;
      auxiliar=auxiliar->siguiente;
    }
    return contador;
  }
  else
    printf("La lista está vacia\n");
    return 0;
}

/*------------- Actividad 3 -------------*/
void insertarNodoFinal(TDAlista* lista, int dato){
  if (!esListaVacia(lista)){
    nodo* auxiliar=lista->inicio;
    //insertar nodo al final de lista
    while (auxiliar->siguiente!=NULL){
      auxiliar=auxiliar->siguiente;
    }
    nodo* nuevo=(nodo*)malloc(sizeof(nodo));
    nuevo->dato=dato;
    nuevo->siguiente=NULL;
    auxiliar->siguiente=nuevo;
  }
  else{
    insertarInicio(lista,dato);
  }
}


void insertarNodoDespues(TDAlista* lista, int dato, int datoAnterior){
  if (!esListaVacia(lista)){
    nodo* auxiliar=lista->inicio;
    //insertar nodo despues de un dato
    while (auxiliar->dato!=datoAnterior){
      auxiliar=auxiliar->siguiente;
      //si estamos al final y no se encuentra el dato hacer break
      if (auxiliar==NULL){
        printf("**Error en funcion insertarNodoDespues, no se ha encontrado el datoAnterior.\n");
        break;
      }
    }
    nodo* nuevo=(nodo*)malloc(sizeof(nodo));
    nuevo->dato=dato;
    nuevo->siguiente=auxiliar->siguiente;
    auxiliar->siguiente=nuevo;
  }
  else{
    insertarInicio(lista,dato);
  }
}


void eliminarFinal(TDAlista* lista){
  if (!esListaVacia(lista)){
    nodo* auxiliar=lista->inicio;
    while (auxiliar->siguiente->siguiente!=NULL){
      auxiliar=auxiliar->siguiente;
    }
    free(auxiliar->siguiente);
    auxiliar->siguiente=NULL;
  }
  else{
    printf("La lista está vacia\n");
  }
}


void eliminarDato(TDAlista* lista, int dato){
  if (!esListaVacia(lista)){
    if(obtenerNumeroNodos(lista) >= 2){
      //Se recorre con 2 punteros, contiguos.
      nodo* auxiliar=lista->inicio;
      nodo* siguiente = auxiliar->siguiente;
      //eliminar nodo con dato coincidente

      //En caso que este al inicio
      if(auxiliar->dato == dato){
        eliminarInicio(lista);
      }
      //En otro caso
      while (siguiente != NULL){
        if (siguiente->dato == dato){
          auxiliar->siguiente = siguiente->siguiente;
          siguiente = NULL;
          printf("Se elimino el dato %d",dato);
          break;
        }
        auxiliar = siguiente;
        siguiente = siguiente->siguiente;
      }
    }
  }
  else{
    printf("La lista está vacia\n");
  }
}

nodo* obtenerNodo(TDAlista* lista, int posicion){
  if (!esListaVacia(lista)){
    nodo* auxiliar=lista->inicio;
    int contador=0;
    while (auxiliar!=NULL){
      if (contador==posicion){
        return auxiliar;
      }
      contador++;
      auxiliar=auxiliar->siguiente;
    }
  }
  else{
    printf("La lista está vacia\n");
  }
  return NULL;
}

