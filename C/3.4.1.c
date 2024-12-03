#include <stdio.h>
#include <stdlib.h>

#define NUM_FRAMES 4      // Número de marcos de memoria (páginas en la memoria física)
#define NUM_PAGINAS 7     // Número total de páginas virtuales

// Función para imprimir el contenido actual de la memoria
void imprimirMemoria(int memoria[], int numFrames) {
    printf("Contenido actual de la memoria: ");
    for (int i = 0; i < numFrames; i++) {
        printf("%d ", memoria[i]);
    }
    printf("\n");
}

// Función para implementar el algoritmo LRU
void reemplazarLRU(int paginas[], int numPaginas, int memoria[], int numFrames) {
    int tiempo[numPaginas];  // Arreglo para almacenar el tiempo de uso de cada página
    int acceso = 0;          // Contador de accesos

    // Inicializar los tiempos con valores -1
    for (int i = 0; i < numPaginas; i++) {
        tiempo[i] = -1;
    }

    // Iterar sobre las páginas a acceder
    for (int i = 0; i < numPaginas; i++) {
        int pagina = paginas[i];
        int encontrado = 0;
        
        // Comprobar si la página ya está en memoria
        for (int j = 0; j < numFrames; j++) {
            if (memoria[j] == pagina) {
                encontrado = 1;
                tiempo[pagina] = acceso;  // Actualizar el tiempo de acceso
                printf("Página %d ya está en memoria.\n", pagina);
                break;
            }
        }

        // Si la página no está en memoria, se reemplaza una página
        if (!encontrado) {
            int menosReciente = 0;
            for (int j = 1; j < numFrames; j++) {
                if (tiempo[memoria[j]] < tiempo[memoria[menosReciente]]) {
                    menosReciente = j;  // Encontrar la página menos recientemente usada
                }
            }
            memoria[menosReciente] = pagina;  // Reemplazar la página menos recientemente usada
            tiempo[pagina] = acceso;          // Establecer el tiempo de acceso para la nueva página
            printf("Página %d reemplazada por %d.\n", memoria[menosReciente], pagina);
        }

        acceso++;  // Incrementar el contador de accesos
        imprimirMemoria(memoria, numFrames);  // Imprimir el estado actual de la memoria
    }
}

int main() {
    // Páginas a acceder (simulamos una secuencia de accesos)
    int paginas[NUM_PAGINAS] = {7, 0, 1, 2, 0, 3, 0};

    // Memoria (marcos de memoria) inicialmente vacía
    int memoria[NUM_FRAMES] = {-1, -1, -1, -1};  // -1 significa que el marco está vacío

    // Llamamos a la función de reemplazo LRU
    reemplazarLRU(paginas, NUM_PAGINAS, memoria, NUM_FRAMES);

    return 0;
}
