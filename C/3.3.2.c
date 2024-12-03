#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_PAGINAS 8    // Número de páginas virtuales
#define NUM_FRAMES 4     // Número de marcos de memoria física

// Estructura para la tabla de páginas
typedef struct {
    int pagina_virtual;  // Número de página virtual
    int marco_fisico;    // Número de marco físico asignado
    int presente;         // 1 si la página está en memoria, 0 si no
} EntradaPagina;

// Función para inicializar la tabla de páginas
void inicializarTablaPaginas(EntradaPagina tabla[], int numPaginas) {
    for (int i = 0; i < numPaginas; i++) {
        tabla[i].pagina_virtual = i;
        tabla[i].marco_fisico = -1;  // Indica que no está asignada
        tabla[i].presente = 0;       // No está presente en memoria
    }
}

// Función para mostrar el estado de la tabla de páginas
void mostrarTablaPaginas(EntradaPagina tabla[], int numPaginas) {
    printf("\nTabla de Páginas:\n");
    printf("Pagina Virtual | Marco Fisico | Presente\n");
    for (int i = 0; i < numPaginas; i++) {
        printf("      %d        |      %d      |    %d\n",
               tabla[i].pagina_virtual, 
               tabla[i].marco_fisico, 
               tabla[i].presente);
    }
}

// Función para simular un fallo de página y cargar la página en un marco de memoria
int cargarPagina(EntradaPagina tabla[], int numFrames, int paginaVirtual) {
    // Buscar el primer marco libre en la memoria
    for (int i = 0; i < numFrames; i++) {
        // Si el marco está libre, asignar la página a este marco
        if (tabla[i].presente == 0) {
            tabla[i].marco_fisico = i;
            tabla[i].presente = 1;
            return 1; // Éxito
        }
    }
    return 0; // No se pudo cargar la página
}

// Función para simular el acceso aleatorio a la memoria
void accesoMemoria(EntradaPagina tabla[], int numPaginas, int numFrames) {
    int paginaVirtual;
    
    // Acceso aleatorio a la memoria
    paginaVirtual = rand() % numPaginas;  // Generar una página aleatoria
    
    printf("\nAcceso a la pagina virtual %d\n", paginaVirtual);
    
    if (tabla[paginaVirtual].presente == 0) {
        printf("¡Fallo de página! La pagina no está en memoria.\n");
        
        // Intentamos cargar la página en un marco físico
        if (cargarPagina(tabla, numFrames, paginaVirtual)) {
            printf("Página %d cargada en memoria.\n", paginaVirtual);
        } else {
            printf("No se pudo cargar la página, memoria llena.\n");
        }
    } else {
        printf("Página %d ya está en memoria física.\n", paginaVirtual);
    }
}

int main() {
    // Inicializamos la tabla de páginas con 8 páginas virtuales y 4 marcos físicos
    EntradaPagina tablaPaginas[NUM_PAGINAS];
    inicializarTablaPaginas(tablaPaginas, NUM_PAGINAS);
    
    // Inicializamos el generador de números aleatorios
    srand(time(NULL));
    
    // Simulamos varios accesos aleatorios a memoria
    for (int i = 0; i < 10; i++) {
        accesoMemoria(tablaPaginas, NUM_PAGINAS, NUM_FRAMES);
        mostrarTablaPaginas(tablaPaginas, NUM_PAGINAS);
    }

    return 0;
}
