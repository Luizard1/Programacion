#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definimos el número máximo de dispositivos en el sistema
#define MAX_DISPOSITIVOS 5

// Estructura que representa un dispositivo
typedef struct {
    int id;             // Identificador del dispositivo
    char nombre[50];    // Nombre del dispositivo
    int estado;         // Estado del dispositivo (0 = inactivo, 1 = activo)
    char buffer[100];   // Buffer de datos (simula los datos de entrada/salida)
} Dispositivo;

// Tabla de dispositivos
Dispositivo tablaDispositivos[MAX_DISPOSITIVOS];

// Inicializar la tabla de dispositivos
void inicializarDispositivos() {
    for (int i = 0; i < MAX_DISPOSITIVOS; i++) {
        tablaDispositivos[i].id = i;
        snprintf(tablaDispositivos[i].nombre, sizeof(tablaDispositivos[i].nombre), "Dispositivo_%d", i);
        tablaDispositivos[i].estado = 0; // Estado inicial: inactivo
        memset(tablaDispositivos[i].buffer, 0, sizeof(tablaDispositivos[i].buffer)); // Limpiamos el buffer
    }
}

// Función para activar un dispositivo
void activarDispositivo(int id) {
    if (id >= 0 && id < MAX_DISPOSITIVOS) {
        tablaDispositivos[id].estado = 1; // Activamos el dispositivo
        printf("El dispositivo %s (ID: %d) ha sido activado.\n", tablaDispositivos[id].nombre, id);
    } else {
        printf("Dispositivo con ID %d no existe.\n", id);
    }
}

// Función para desactivar un dispositivo
void desactivarDispositivo(int id) {
    if (id >= 0 && id < MAX_DISPOSITIVOS) {
        tablaDispositivos[id].estado = 0; // Desactivamos el dispositivo
        printf("El dispositivo %s (ID: %d) ha sido desactivado.\n", tablaDispositivos[id].nombre, id);
    } else {
        printf("Dispositivo con ID %d no existe.\n", id);
    }
}

// Función para realizar una operación de lectura en un dispositivo
void leerDispositivo(int id) {
    if (id >= 0 && id < MAX_DISPOSITIVOS) {
        if (tablaDispositivos[id].estado == 1) {
            printf("Leyendo datos del dispositivo %s (ID: %d): %s\n", tablaDispositivos[id].nombre, id, tablaDispositivos[id].buffer);
        } else {
            printf("El dispositivo %s (ID: %d) está inactivo. No se puede leer.\n", tablaDispositivos[id].nombre, id);
        }
    } else {
        printf("Dispositivo con ID %d no existe.\n", id);
    }
}

// Función para realizar una operación de escritura en un dispositivo
void escribirDispositivo(int id, const char* datos) {
    if (id >= 0 && id < MAX_DISPOSITIVOS) {
        if (tablaDispositivos[id].estado == 1) {
            snprintf(tablaDispositivos[id].buffer, sizeof(tablaDispositivos[id].buffer), "%s", datos);
            printf("Escribiendo en el dispositivo %s (ID: %d): %s\n", tablaDispositivos[id].nombre, id, datos);
        } else {
            printf("El dispositivo %s (ID: %d) está inactivo. No se puede escribir.\n", tablaDispositivos[id].nombre, id);
        }
    } else {
        printf("Dispositivo con ID %d no existe.\n", id);
    }
}

// Función para mostrar el estado de todos los dispositivos
void mostrarDispositivos() {
    printf("\nEstado de los dispositivos:\n");
    for (int i = 0; i < MAX_DISPOSITIVOS; i++) {
        printf("ID: %d, Nombre: %s, Estado: %s, Buffer: %s\n",
               tablaDispositivos[i].id,
               tablaDispositivos[i].nombre,
               (tablaDispositivos[i].estado == 1) ? "Activo" : "Inactivo",
               tablaDispositivos[i].buffer);
    }
}

int main() {
    int opcion, id;
    char datos[100];

    // Inicializamos los dispositivos
    inicializarDispositivos();

    while (1) {
        printf("\n--- Manejador de Dispositivos ---\n");
        printf("1. Activar dispositivo\n");
        printf("2. Desactivar dispositivo\n");
        printf("3. Leer dispositivo\n");
        printf("4. Escribir en dispositivo\n");
        printf("5. Mostrar estado de dispositivos\n");
        printf("6. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Ingrese el ID del dispositivo a activar: ");
                scanf("%d", &id);
                activarDispositivo(id);
                break;
            case 2:
                printf("Ingrese el ID del dispositivo a desactivar: ");
                scanf("%d", &id);
                desactivarDispositivo(id);
                break;
            case 3:
                printf("Ingrese el ID del dispositivo a leer: ");
                scanf("%d", &id);
                leerDispositivo(id);
                break;
            case 4:
                printf("Ingrese el ID del dispositivo a escribir: ");
                scanf("%d", &id);
                getchar(); // Limpiar el buffer de entrada
                printf("Ingrese los datos a escribir: ");
                fgets(datos, sizeof(datos), stdin);
                datos[strcspn(datos, "\n")] = 0; // Eliminar el salto de línea
                escribirDispositivo(id, datos);
                break;
            case 5:
                mostrarDispositivos();
                break;
            case 6:
                printf("Saliendo del manejador de dispositivos...\n");
                return 0;
            default:
                printf("Opción no válida.\n");
                break;
        }
    }

    return 0;
}
