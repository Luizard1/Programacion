#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define NUM_INTERRUPCIONES 3

// Simulación de interrupciones
typedef enum {
    INTERRUPCION_DISPOSITIVO,
    INTERRUPCION_FINALIZACION_TAREA,
    INTERRUPCION_TEMPO,
    NOMBRE_INTERRUPCION_INVALIDO
} tipo_interrupcion;

// Estructura que representa una interrupción
typedef struct {
    tipo_interrupcion tipo;
    int id;
} Interrupcion;

// Variables globales
bool interrupcion_ocurrida = false;
Interrupcion interrupcion_actual;

// Función que simula la generación de una interrupción por dispositivo
void generar_interrupcion(tipo_interrupcion tipo) {
    interrupcion_ocurrida = true;
    interrupcion_actual.tipo = tipo;
    interrupcion_actual.id = rand() % 100;  // Asignamos un ID aleatorio a la interrupción
    printf("Generada interrupción de tipo %d con ID %d\n", tipo, interrupcion_actual.id);
}

// Función que simula el manejador de interrupciones
void manejar_interrupcion() {
    if (!interrupcion_ocurrida) {
        return; // No hay interrupciones para manejar
    }

    printf("Manejando interrupción...\n");

    switch (interrupcion_actual.tipo) {
        case INTERRUPCION_DISPOSITIVO:
            printf("Procesando interrupción de dispositivo con ID %d\n", interrupcion_actual.id);
            break;
        case INTERRUPCION_FINALIZACION_TAREA:
            printf("Procesando interrupción de finalización de tarea con ID %d\n", interrupcion_actual.id);
            break;
        case INTERRUPCION_TEMPO:
            printf("Procesando interrupción de tiempo con ID %d\n", interrupcion_actual.id);
            break;
        default:
            printf("Tipo de interrupción desconocido\n");
            break;
    }

    // Después de procesar, reiniciamos la interrupción
    interrupcion_ocurrida = false;
}

// Función que simula el procesamiento de un proceso o tarea
void procesar_tarea(int tarea_id) {
    printf("Procesando tarea %d...\n", tarea_id);

    // Simulamos el tiempo de procesamiento
    int tiempo = rand() % 3 + 1; // Entre 1 y 3 segundos
    for (int i = 0; i < tiempo; i++) {
        if (rand() % 10 < 3) { // Probabilidad de generar una interrupción
            generar_interrupcion(rand() % NUM_INTERRUPCIONES);
            break;
        }
    }
}

// Función principal del programa
int main() {
    srand(time(NULL));  // Inicializamos el generador de números aleatorios
    int tarea_id = 1;

    while (1) {
        printf("\nInicio del ciclo de ejecución\n");
        
        // Simulamos el procesamiento de una tarea
        procesar_tarea(tarea_id++);
        
        // Si ocurrió una interrupción, la manejamos
        manejar_interrupcion();

        // Simulamos un breve descanso entre ciclos de tarea
        printf("Esperando al siguiente ciclo de ejecución...\n");
        sleep(2);  // Simulamos un pequeño delay entre las tareas
    }

    return 0;
}
