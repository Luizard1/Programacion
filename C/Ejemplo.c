#include <stdio.h>
#include <stdlib.h>
#include <time.h> //Para que los numeros sean realmente aleatorios


//Se define una estructura para crear un nuevo tipo de dato, el tipo de dato "nodo"
typedef struct _nodo{
	int valor;
	int prioridad;
	struct _nodo *siguiente; //Tipo de puntero a la misma estructura, guarda la dirección de donde está la estructura
	
	} nodo;
	
	//Regresa un puntero de tipo "nodo" 
	nodo* genera_proceso(){
		static int contador =1; //Es estático para que cada vez que entra, se siga editando, no se cree nuevamente
		nodo* nuevo = (nodo*)malloc(sizeof(nodo));
						//con malloc se reserva el espacio y apunta a un espacio de memoria(nodo*)
			//nuevo es una variable que apunta a una direccion de tipo nodo*
		if (nuevo ==null)
		{
			prinf("Error al asignar memoria. \n");
			exit(1);
		}
		nuevo -> valor = contador++;
		//operador "->" es para acceder a los atributos
		
		}
	
	
	
