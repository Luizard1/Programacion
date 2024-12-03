#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 100   // Tamaño del buffer de entrada
#define MAX_ENTRADAS 10   // Número máximo de entradas en el buffer

// Estructura que representa el dispositivo virtual
typedef struct {
    char buffer[BUFFER_SIZE];   // Buffer de entrada para almacenar los datos
    int head;                   // Indica la posición del siguiente carácter a leer
    int tail;                   // Indica la posición del siguiente carácter a escribir
    int lleno;                  // Indica si el buffer está lleno
} DispositivoEntrada;

// Inicializa el dispositivo virtual
void inicializarDispositivo(DispositivoEntrada* dispositivo) {
    dispositivo->head = 0;
    dispositivo->tail = 0;
    dispositivo->lleno = 0;
    memset(dispositivo->buffer, 0, sizeof(dispositivo->buffer));
    printf("Dispositivo de entrada inicializado.\n");
}

// Lee un carácter desde el dispositivo de entrada
int leerEntrada(DispositivoEntrada* dispositivo, char* caracter) {
    if (dispositivo->head == dispositivo->tail && dispositivo->lleno == 0) {
        printf("Error: No hay datos para leer en el dispositivo.\n");
        return -1; // Indicar que no hay datos
    }
    
    *caracter = dispositivo->buffer[dispositivo->head];
    dispositivo->head = (dispositivo->head + 1) % BUFFER_SIZE;

    if (dispositivo->head == dispositivo->tail) {
        dispositivo->lleno = 0;
    }

    return 0; // Éxito en la lectura
}

// Escribe un carácter en el dispositivo de entrada
int escribirEntrada(DispositivoEntrada* dispositivo, char caracter) {
    if (dispositivo->lleno) {
        printf("Error: El dispositivo está lleno, no se puede escribir.\n");
        return -1; // Indicar que el dispositivo está lleno
    }

    dispositivo->buffer[dispositivo->tail] = caracter;
    dispositivo->tail = (dispositivo->tail + 1) % BUFFER_SIZE;

    if (dispositivo->tail == dispositivo->head) {
        dispositivo->lleno = 1; // El buffer está lleno
    }

    return 0; // Éxito en la escritura
}

// Muestra el contenido actual del buffer del dispositivo
void mostrarEstado(DispositivoEntrada* dispositivo) {
    printf("Estado del dispositivo de entrada:\n");
    printf("Buffer: ");
    for (int i = dispositivo->head; i != dispositivo->tail; i = (i + 1) % BUFFER_SIZE) {
        printf("%c ", dispositivo->buffer[i]);
    }
    printf("\n");
}

// Función principal para probar el manejador de dispositivos
int main() {
    DispositivoEntrada dispositivo;
    char caracter;
    int opcion;
    
    // Inicialización del dispositivo virtual
    inicializarDispositivo(&dispositivo);
    
    // Menú interactivo
    while (1) {
        printf("\n---- Manejador de Dispositivo Virtual de Entrada ----\n");
        printf("1. Escribir dato\n");
        printf("2. Leer dato\n");
        printf("3. Mostrar estado del dispositivo\n");
        printf("4. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        getchar(); // Para consumir el salto de línea dejado por scanf

        switch (opcion) {
            case 1:
                // Escribir dato en el dispositivo
                printf("Ingrese un carácter para escribir en el dispositivo: ");
                scanf("%c", &caracter);
                if (escribirEntrada(&dispositivo, caracter) == 0) {
                    printf("Carácter '%c' escrito en el dispositivo.\n", caracter);
                }
                break;
            case 2:
                // Leer dato desde el dispositivo
                if (leerEntrada(&dispositivo, &caracter) == 0) {
                    printf("Carácter leído del dispositivo: '%c'\n", caracter);
                }
                break;
            case 3:
                // Mostrar el estado del dispositivo
                mostrarEstado(&dispositivo);
                break;
            case 4:
                printf("Saliendo del programa.\n");
                exit(0);
            default:
                printf("Opción no válida. Intente de nuevo.\n");
        }
    }
    
    return 0;
}
