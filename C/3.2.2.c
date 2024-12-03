#include <stdio.h>

#define NUM_PROCESOS 5    // Número de procesos
#define NUM_BLOQUES 4     // Número de bloques de memoria

// Estructura que representa los bloques de memoria
typedef struct {
    int tamanio;      // Tamaño del bloque de memoria
    int ocupado;      // 0 = libre, 1 = ocupado
} BloqueMemoria;

// Estructura que representa los procesos
typedef struct {
    int tamanio;      // Tamaño del proceso
    int asignado;     // 0 = no asignado, 1 = asignado
} Proceso;

void asignarMemoria(BloqueMemoria bloques[], Proceso procesos[], int numBloques, int numProcesos) {
    for (int i = 0; i < numProcesos; i++) {
        int asignado = 0;
        for (int j = 0; j < numBloques; j++) {
            // Buscar el primer bloque libre que sea lo suficientemente grande
            if (bloques[j].ocupado == 0 && bloques[j].tamanio >= procesos[i].tamanio) {
                bloques[j].ocupado = 1;  // Marcar bloque como ocupado
                procesos[i].asignado = 1; // Marcar proceso como asignado
                printf("Proceso %d asignado al bloque %d de tamaño %d\n", i+1, j+1, bloques[j].tamanio);
                asignado = 1;
                break;
            }
        }
        if (!asignado) {
            printf("Proceso %d no pudo ser asignado.\n", i+1);
        }
    }
}

int main() {
    // Inicializamos los bloques de memoria
    BloqueMemoria bloques[NUM_BLOQUES] = {
        {100, 0},  // Bloque 1 de tamaño 100, libre
        {500, 0},  // Bloque 2 de tamaño 500, libre
        {200, 0},  // Bloque 3 de tamaño 200, libre
        {300, 0}   // Bloque 4 de tamaño 300, libre
    };

    // Inicializamos los procesos
    Proceso procesos[NUM_PROCESOS] = {
        {120, 0},  // Proceso 1 de tamaño 120, no asignado
        {450, 0},  // Proceso 2 de tamaño 450, no asignado
        {300, 0},  // Proceso 3 de tamaño 300, no asignado
        {150, 0},  // Proceso 4 de tamaño 150, no asignado
        {350, 0}   // Proceso 5 de tamaño 350, no asignado
    };

    // Llamamos a la función para asignar memoria
    asignarMemoria(bloques, procesos, NUM_BLOQUES, NUM_PROCESOS);

    return 0;
}
