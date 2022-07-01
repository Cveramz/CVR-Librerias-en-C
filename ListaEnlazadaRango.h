#include <stdio.h>
#include <stdlib.h>

/*------------- estructura de datos -------------*/

typedef struct nodoGenerico
{
  int inicio; //inicio de rango
  int fin; //fin de rango
  struct nodoGenerico* siguiente;
}nodo;

typedef struct listaGenerica
{
  nodo* inicio;
}TDAlista;


/*------------- operaciones -------------*/
//crea una lista vacia
TDAlista* crearListaVacia()
{
  TDAlista* lista=(TDAlista*)malloc(sizeof(TDAlista));
  lista->inicio=NULL;
  return lista;
}
//verificar si es lista vacia, retorna 1 si es vacia, 0 si no
int esListaVacia(TDAlista* lista)
{
  if (lista->inicio == NULL)
    return 1;
  else
    return 0;
}

//Muestra en pantalla los nodos.
void recorrerLista(TDAlista* lista)
{
  if (!esListaVacia(lista))
  {
    nodo* auxiliar=lista->inicio;
    while (auxiliar!=NULL)
    {
      printf("%d ",auxiliar->inicio);
      printf("%d ",auxiliar->fin);
      printf("\n");
      auxiliar=auxiliar->siguiente;
    }
  }
  else
    printf("La lista esta vacia\n");
}

//Inserta un nodo al inicio de la lista
void insertarInicio(TDAlista* lista, int dato1, int dato2)
{
  nodo* nuevo=(nodo*)malloc(sizeof(nodo));
  nuevo->inicio=dato1;
  nuevo->fin=dato2;
  nuevo->siguiente = lista->inicio;
  lista->inicio=nuevo;
}

//Insertar nodo al final de la lista
void insertarNodoFinal(TDAlista* lista, int dato1, int dato2){
  if (!esListaVacia(lista)){
    nodo* auxiliar=lista->inicio;
    //insertar nodo al final de lista
    while (auxiliar->siguiente!=NULL){
      auxiliar=auxiliar->siguiente;
    }
    nodo* nuevo=(nodo*)malloc(sizeof(nodo));
    nuevo->inicio=dato1;
    nuevo->fin=dato2;
    nuevo->siguiente=NULL;
    auxiliar->siguiente=nuevo;
  }
  else{
    insertarInicio(lista,dato1, dato2);
  }
}

//eliminar el primer nodo de la lista
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

//Eliminar nodo al final de la lista.
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
    printf("La lista esta vacia\n");
  }
}


//liberar la lista
void liberarLista(TDAlista* lista){
  while(!esListaVacia(lista)){
    eliminarInicio(lista);
  }
}



//buscar por fin de rango el valor dado
int buscarPorFin(TDAlista* lista, int dato){
  if (!esListaVacia(lista))
  {
    nodo* auxiliar=lista->inicio;
    while (auxiliar!=NULL)
    {
      if (dato==auxiliar->fin){
        return 1;
      }
      auxiliar=auxiliar->siguiente;
    }
    free(auxiliar);
  }
  else{
    printf("La lista esta vacia\n");
  }
  return 0;
}


//Obtener cantidad de nodos totales de la lista
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
    printf("La lista esta vacia\n");
    return 0;
}



//Insertar nodo despues del final de un rango especifico
void insertarNodoDespuesPorFin(TDAlista* lista, int inicio, int fin, int datoAnterior){
  if (!esListaVacia(lista)){
    nodo* auxiliar=lista->inicio;
    //insertar nodo despues de un dato
    while (auxiliar->fin!=datoAnterior){
      auxiliar=auxiliar->siguiente;
      //si estamos al final y no se encuentra el dato hacer break
      if (auxiliar==NULL){
        printf("**Error en funcion insertarNodoDespues, no se ha encontrado el datoAnterior.\n");
        break;
      }
    }
    nodo* nuevo=(nodo*)malloc(sizeof(nodo));
    nuevo->inicio=inicio;
    nuevo->fin=fin;
    nuevo->siguiente=auxiliar->siguiente;
    auxiliar->siguiente=nuevo;
  }
  else{
    //insertarInicio(lista,dato);
    printf("**Error en funcion insertarNodoDespues, la lista esta vacia.\n");
  }
}

//Eliminar nodo que contanga un inicio de rango especificado.
void eliminarDatoPorInicio(TDAlista* lista, int dato){
  if (!esListaVacia(lista)){
    if(obtenerNumeroNodos(lista) >= 2){
      //Se recorre con 2 punteros, contiguos.
      nodo* auxiliar=lista->inicio;
      nodo* siguiente = auxiliar->siguiente;
      //eliminar nodo con dato coincidente

      //En caso que este al inicio
      if(auxiliar->inicio == dato){
        eliminarInicio(lista);
      }
      //En otro caso
      while (siguiente != NULL){
        if (siguiente->inicio == dato){
          auxiliar->siguiente = siguiente->siguiente;
          siguiente = NULL;
          printf("Se elimino el nodo con inicio %d\n",dato);
          break;
        }
        auxiliar = siguiente;
        siguiente = siguiente->siguiente;
      }
    }
  }
  else{
    printf("La lista esta vacia\n");
  }
}

//eliminar nodo que contenga un fin de rango especificado
void eliminarDatoPorFin(TDAlista* lista, int dato){
  if (!esListaVacia(lista)){
    if(obtenerNumeroNodos(lista) >= 2){
      //Se recorre con 2 punteros, contiguos.
      nodo* auxiliar=lista->inicio;
      nodo* siguiente = auxiliar->siguiente;
      //eliminar nodo con dato coincidente

      //En caso que este al inicio
      if(auxiliar->fin == dato){
        eliminarInicio(lista);
      }
      //En otro caso
      while (siguiente != NULL){
        if (siguiente->fin == dato){
          auxiliar->siguiente = siguiente->siguiente;
          siguiente = NULL;
          printf("Se elimino el nodo con fin %d \n",dato);
          break;
        }
        auxiliar = siguiente;
        siguiente = siguiente->siguiente;
      }
    }
  }
  else{
    printf("La lista esta vacia\n");
  }
}

//obtener nodo de una posición especificada (recordar igualar a otro nodo)
nodo* obtenerNodo(TDAlista* lista, int posicion){
  if (!esListaVacia(lista)){
    nodo* auxiliar=lista->inicio;
    int contador=0;
    while (auxiliar!=NULL){
      if (contador==posicion-1){
        return auxiliar;
      }
      contador++;
      auxiliar=auxiliar->siguiente;
    }
  }
  else{
    printf("La lista esta vacia\n");
  }
  return NULL;
}

//crear una función de ordenamiento por selección.

void swap(nodo* nodo1, nodo* nodo2){
	int iniaux= nodo2->inicio;
	int finaux= nodo2->fin;
	nodo2->inicio=nodo1->inicio;
	nodo2->fin=nodo1->fin;
	nodo1->inicio=iniaux;
	nodo1->fin=finaux;
}

nodo* buscarMenorNodo(TDAlista* lista, int posini){
	printf("Entrando a menor nodo\n");
  if (!esListaVacia(lista)){
    nodo* auxiliar=lista->inicio;
    int contador=0;
	printf("entrando al while de menor nodo\n");
    while (contador!=posini){
		printf("While\n");
      contador++;
      auxiliar=auxiliar->siguiente;
	  printf("Auxiliar: %d\n",auxiliar);
    }
	printf("Fuera del while\n");
	//aqui llegamos a la posición inicial
	nodo* menor = auxiliar;
	while (auxiliar->siguiente!=NULL){
		//inicio es el inicio del rango de tiempo
		if (auxiliar->inicio < menor->inicio){
			menor=auxiliar;
		}
		auxiliar=auxiliar->siguiente;
	}
	return menor;
  }
  else{
    printf("La lista esta vacia\n");
  }
  return NULL;
} 

void seleccion(TDAlista* lista){
	nodo* temporal = lista->inicio;
	nodo* minimo;
	nodo* minimosig;
	while (temporal!=NULL){ //designa el largo de la lista.
		minimo=temporal;
		minimosig= temporal->siguiente;
		while (minimosig!=NULL){ //buscar el minimo de los nodos.
			if(minimo->inicio>minimosig->inicio){ //comparación
				minimo=minimosig;
			}
			minimosig=minimosig->siguiente;
		}
		swap(temporal,minimo); //cambio de nodos
		temporal=temporal->siguiente;
	}
}

/*
//Crear función para guardar todas las horas disponibles en una lista.
void guardarHoras(TDAlista* listaoriginal, TDAlista* nuevo){
  nodo* temporal = listaoriginal->inicio;
  int ini;
  int fin;
  int nodos= obtenerNumeroNodos(listaoriginal);
  int i;
  for i=0;i<nodos;i++{
    ini= listaoriginal->inicio
    fin->listaoriginal->fin;
    temporal=temporal->siguiente;
    
  }
}
*/

//crear función para abrir archivo.
void ingresardatos(char *nombrearchivo, TDAlista *lista){
    FILE *archivo;
    archivo = fopen(nombrearchivo, "r");
    int dato1, dato2;
    if(archivo == NULL){
        printf("No se pudo abrir el archivo\n");
    }else{
        while(!feof(archivo)){
            fscanf(archivo, "%d %d", &dato1, &dato2);
            insertarNodoFinal(lista, dato1, dato2);
        }
        eliminarInicio(lista);
        fclose(archivo);
    }
}

//crear una función que escriba en un archivo los datos de la lista.
void escribirdatos(char *nombrearchivo, TDAlista *lista){
    FILE *archivo;
    archivo = fopen(nombrearchivo, "w");
    nodo* temporal = lista->inicio;
    if(archivo == NULL){
        printf("No se pudo abrir el archivo\n");
    }else{
        while(temporal != NULL){
            fprintf(archivo, "%d %d\n", temporal->inicio, temporal->fin);
            temporal = temporal->siguiente;
        }
        fclose(archivo);
    }
}
