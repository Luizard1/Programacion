#include <stdio.h>
#include <stdlib.h>

#define NUM_PARTITIONS 4 // Número de particiones fijas
#define PARTITION_SIZE 50 // Tamaño de cada partición

// Estructura para un proceso
typedef struct {
    int id;         // ID del proceso
    int size;       // Tamaño del proceso
    int allocated;  // 1 si está asignado, 0 si no
} Process;

// Estructura para una partición de memoria
typedef struct {
    int id;         // ID de la partición
    int size;       // Tamaño de la partición
    int allocated;  // 1 si está ocupada, 0 si está libre
    int processId;  // ID del proceso asignado a la partición (si está ocupada)
} Partition;

// Función para mostrar el estado de las particiones
void showPartitions(Partition partitions[], int numPartitions) {
    printf("\nEstado de las particiones:\n");
    printf("ID\tTamaño\tEstado\tProceso Asignado\n");
    for (int i = 0; i < numPartitions; i++) {
        printf("%d\t%d\t%s\t", partitions[i].id, partitions[i].size,
               partitions[i].allocated ? "Ocupada" : "Libre");
        if (partitions[i].allocated) {
            printf("Proceso %d\n", partitions[i].processId);
        } else {
            printf("Ninguno\n");
        }
    }
}

// Función para asignar procesos a particiones
int allocateProcessToPartition(Partition partitions[], Process *process) {
    for (int i = 0; i < NUM_PARTITIONS; i++) {
        if (!partitions[i].allocated && partitions[i].size >= process->size) {
            partitions[i].allocated = 1;
            partitions[i].processId = process->id;
            process->allocated = 1;
            printf("Proceso %d asignado a partición %d\n", process->id, partitions[i].id);
            return 1; // Asignado con éxito
        }
    }
    return 0; // No se pudo asignar
}

int main() {
    // Inicializar particiones de memoria
    Partition partitions[NUM_PARTITIONS];
    for (int i = 0; i < NUM_PARTITIONS; i++) {
        partitions[i].id = i + 1;
        partitions[i].size = PARTITION_SIZE;
        partitions[i].allocated = 0;
        partitions[i].processId = -1;  // Ningún proceso asignado
    }

    // Inicializar procesos
    Process processes[5] = {
        {1, 30, 0},  // Proceso 1 de tamaño 30
        {2, 60, 0},  // Proceso 2 de tamaño 60
        {3, 20, 0},  // Proceso 3 de tamaño 20
        {4, 40, 0},  // Proceso 4 de tamaño 40
        {5, 50, 0}   // Proceso 5 de tamaño 50
    };

    // Mostrar particiones inicialmente
    showPartitions(partitions, NUM_PARTITIONS);

    // Asignar procesos a particiones
    for (int i = 0; i < 5; i++) {
        if (!processes[i].allocated) {
            if (!allocateProcessToPartition(partitions, &processes[i])) {
                printf("No hay partición suficiente para el proceso %d (tamaño: %d)\n",
                        processes[i].id, processes[i].size);
            }
        }
    }

    // Mostrar el estado final de las particiones
    showPartitions(partitions, NUM_PARTITIONS);

    return 0;
}

