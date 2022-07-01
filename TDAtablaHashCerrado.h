#include <stdio.h>
#include <stdlib.h>


/*--------------- estructura de datos -----------------*/

struct TDAtablaHash{
	int capacidad;
	int* lista;
}typedef tablaHash;


/*--------------- operaciones de creación -----------------*/

//Crear tabla
tablaHash * crearTablaHash(int capacidad){
	tablaHash* tabla = (tablaHash*) malloc(sizeof(tablaHash));
	tabla->capacidad = capacidad;
	tabla->lista = (int*)malloc(sizeof(int) * 7);
	for (int i = 0; i < capacidad; ++i){
		tabla->lista[i] = -1;  
	}
	return tabla;
}


/*--------------- funcion hash -----------------*/

// Función hash
int funcionHash(int llave){
	return((4 * llave + 3) % 7);
}


/*--------------- operaciones de inserción y eliminacion -----------------*/

//Insertar en Bucket
void insertarHashCerrado(tablaHash* tabla, int dato){
	int indice = funcionHash(dato);
	if(esBucketVacio(tabla,indice)){
		tabla->lista[indice] = dato;
	}else{
		int i = 0;
		while(!esBucketVacio(tabla, i)){
			i++;
		}
		tabla->lista[indice] = dato;
	}

	mostrarTablaHashCerrado(tabla);
	
}


//Eliminar en tabla
void eliminarHashCerrado(tablaHash* tabla, int dato){
	int indice = funcionHash(dato); 
	if(tabla->lista[indice] == dato){
		tabla->lista[indice] = -1;
	}else{
		
		int i = 0;
		while(tabla->lista[i] != dato){
			i++;
		}
		tabla->lista[i] = -1;
	}
	mostrarTablaHashCerrado(tabla);
	return;
}

/*--------------- operaciones de consulta -----------------*/

//mostrar tabla
void mostrarTablaHashCerrado(tablaHash* tabla){
	for (int i = 0; i < tabla->capacidad; ++i){
		printf("%d.    %d\n", i+1, tabla->lista[i]);
	} printf("\n");
	return;
}





/*--------------- operaciones auxiliares -----------------*/

//verificador
int esBucketVacio(tablaHash* tabla, int indice){
	if(tabla->lista[indice] == -1){
		return 1;
	}else{
		return 0;
	}
}

/*--------------- operaciones de posicion -----------------*/

//buscar en tabla
void buscarHashCerrado(tablaHash* tabla, int dato){
	int indice = funcionHash(dato);
	if(tabla->lista[indice] == dato){
		printf("El dato se encuentra en la posicion %d", indice);
	}else{
		
		int i = 0;
		while(tabla->lista[i] != dato){
			i++;
		}
		printf("El dato se encuentra en la posicion %d", i);
	}
	return;
}
