# Administración de Memoria

## 3.1 Política y filosofía

1. _¿Cuál es la diferencia entre fragmentación interna y externa? Explica cómo cada una afecta el rendimiento de la memoria**_.
  * La fragmentación interna genera bloques de un tamaño específico generalmente grande no contiguos, mientras que la fragmentación interna usa bloques de tamaño libre contiguos. Ambos son ineficientes a su manera específica, como ejemplo:
      * **Fragmetación interna**: al generar bloques de un tamaño específico, si la solicitud es de un tamaño inferior al del bloque, toma de igual manera todo el bloque, haciendo que no se use una parte de la memoria, esto conforme crece el número de solicitudes puede llevarnos a una perdida grande de recursos de la computadora, por un decir, si cada solicitud requiere 10kb de memoria y los bloques son de 25kb, cada solicitud se irían desperdiciando 5kb de memoria, en 10 solicitudes ya serían 50kb.
      > [Tamaño de bloque 15kb] [Tamaño solicitud 10kb]
      > > [Usado 10kb] [Desperdiciado 5kb]
      * **Fragmentación externa**: el tener bloques contiguos de tamaño libre, significa que eventualmente se podría dar el caso de que la siguiente solicitud pida un tamaño mayor al de el espacio restante.
      > [Libre 100kb] [Usado 80kb] [Solicitud nueva 30kb]
              >> Error, no hay suficiente espacio en memoria
      ---
2. _Investiga y explica las políticas de reemplazo de páginas en sistemas operativos. ¿Cuál consideras más eficiente y por qué?_
    * El algorítmo que a mi parecer es más eficiente, es el algoritmo de reloj, ya que toma en cuenta todas las páginas, y va pasando por ellas la cantidad de veces necesarias, no se "olvida" de ninguna como en el caso de Last Recently Used ni "prioriza" a otra como en el caso de Most Frequently used, esto le permite estar constantemente cambiando de página según sea requerido y, aunque no es tan eficiente como el Last Recently Used, tampoco es tan costoso computacionalmente como este último.
![Algoritmo de reloj](https://marcodubon.wordpress.com/wp-content/uploads/2016/09/ghfghf.png)


## 3.2 Memoria real

1. _Escribe un programa en C o Python que simule la administración de memoria mediante particiones fijas_.

~~~
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

~~~


2. _Diseña un algoritmo para calcular qué procesos pueden ser asignados a un sistema con memoria real limitada utilizando el algoritmo de "primera cabida"_.

~~~
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
~~~

## 3.3 Organización de memoria virtual

1. _Investiga y explica el concepto de "paginación" y "segmentación". ¿Cuáles son las ventajas y desventajas de cada técnica?_
      * **Paginación**: es una técnica según la cual el espacio de direcciones virtuales se divide en páginas del mismo tamaño, la memoria virtual también se divide en "marcos" o "páginas del mismo tamaño físicas" del mismo tamaño, dichos marcos son compartidos por los distintos procesos que hay en el sistema de modo que cada proceso llegará a tener algunas páginas en la memoria principal (llamadas páginas activas) y otras en memoria secundaria (llamadas páginas inactivas). Este mecanismo cumple dos funciones:
         * Llevar a cabo la transformación de una dirección virtual a física, osea, la determinación de la página a la que corresponde una determinada dirección de un programa, así como del marco, si lo hay, que ocupa esta página.
         * Transferir, cuando haga falta, páginas de la memoria secundaria a la memoria principal, y de la memoria principal a la memoria secundaria cuando ya no sean necesarias.
         * _VENTAJAS_:
             * Permite que la memoria de un proceso no sea contigua, y que a un proceso se le asigne memoria física donde quiera que ésta esté disponible.
             * Evita el gran problema de acomodar trozos de memoria de tamaño variable en el almacenamiento auxiliar.
         * _DESVENTAJAS_:
             * Costo de hardware y software alto debido al uso elevado de recursos de memoria y tiempo de CPU para la implantación de la nueva información manejada además de el mecanismo de traducción de direcciones que sea necesario.

  * __Segmentación__: es un esquema de administración de memoria que apoya la perspectiva que el usuario tiene de la memoria. Un espacio de direcciones lógicas se compone de un conjunto de segmentos, cada uno de los cuales tiene un nombre y una longitud. Las direcciones especifican el nombre del segmento y el desplazamiento dentro de él, de manera que el usuario especifica cada dirección con dos cantidades: el nombre del segmento y un desplazamiento.
      * _VENTAJAS:_
          * Debido a que es posible separar modulos, se hace más fácil la modifiación de los mismos.
          * Crecimiento dinámico de los segmentos según sea necesario.
          * Es posible definir segmentos que aún no existan, con el fin de que la memoria esté libre hasta el momento en el que se necesite dicho segmento.
          * El programador puede conocer las unidades lógicas de su programa, para darles un tratamiento particular.

      * _DESVENTAJAS:_
          * El uso de la memoria virtual suele ser más complejo.
          * Requiere un mayor consumo de recursos.
          * El problema de fragmentación externa, que es básicamente que se ocupe más espacio del disponible y por ende no se pueda cargar en memoria un proceso.
2. _Escribe un programa que simule una tabla de páginas para procesos con acceso aleatorio a memoria virtual_.

~~~
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

~~~

## 3.4 Administración de memoria virtual

1. _Escribe un código que implemente el algoritmo de reemplazo de página "Least Recently Used" (LRU)_.

~~~
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

~~~

2. _Diseña un diagrama que represente el proceso de traducción de direcciones virtuales a físicas en un sistema con memoria virtual_.

## Integración

1. _Analiza un sistema operativo moderno (por ejemplo, Linux o Windows) e identifica cómo administra la memoria virtual_.
    * El sistema operativo Windows, administra esta memoria por medio de un archivo llamado "pagefile.sys", mejor conocido como "archivo de paginación", localizado en el directorio raíz del disco que seleccionemos (Generalmente c:/pagefile.sys). Este archivo tiene un tamaño específico designado ya sea automáticamente por el sistema o editado por el administrador. Cuando la memoria física se llena, windows recurre a este archivo para seguir cargando procesos. También existe la opción de no tener archivo de paginación alguno, esta opción nos permite no "molestar" al disco duro con este archivo si tenemos suficiente memoria física, generalmente esto se recomienda para sistemas operativos con cantidades de RAM mayores a 8 gigabytes.
2. _Realiza una simulación en cualquier lenguaje de programación que emule el swapping de procesos en memoria virtual_.

# Administración de Entrada/Salida

## 4.1 Dispositivos y manejadores de dispositivos

1. _Explica la diferencia entre dispositivos de bloque y dispositivos de carácter. Da un ejemplo de cada uno_.
    * La principal diferencia entre estos es la forma en la que manejan los datos, los dispositivos de caracter (como el teclado, el mouse o una cinta magnética) manejan los datos como un flujo de bytes y no permiten el acceso aleatorio, mientras que los dispositivos de bloque (como los discos duros) administran los datos en bloques, lo cual permite el acceso aleatorio de los mismos, lo cual los hace más adecuados para archivos que requieren operaciones frecuentes de lectura/escritura.
2. _Diseña un programa que implemente un manejador de dispositivos sencillo para un dispositivo virtual de entrada_.

~~~
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

~~~

## 4.2 Mecanismos y funciones de los manejadores de dispositivos

1. _Investiga qué es la interrupción por E/S y cómo la administra el sistema operativo. Escribe un ejemplo en pseudocódigo para simular este proceso_.
    * La interrupción E/S es fundamental para el funcionamiento de nuestras computadoras, pues es la que permite que los dispositivos perifericos (mouse, teclado, discos duros, etc) se comuniquen con el CPU y viceversa, esto sin la necesidad de que el procesador esté revisando constantemente el estado del dispositivo.

~~~
// Definición de procesos y dispositivos
procesos = [proceso1, proceso2, proceso3]
dispositivos = [disco, red, teclado]

// Cola de interrupciones
cola_interrupciones = []

// Estado de los dispositivos
estado_dispositivo = {
    disco: "libre",
    red: "libre",
    teclado: "ocupado"
}

// Función que simula una interrupción por E/S
función generar_interrupción(dispositivo):
    // Se agrega el dispositivo a la cola de interrupciones
    cola_interrupciones.agregar(dispositivo)
    imprimir("Interrupción generada por: ", dispositivo)

// Función que maneja las interrupciones
función manejar_interrupciones():
    mientras cola_interrupciones.no_esta_vacia():
        // Obtener el dispositivo de la cola
        dispositivo = cola_interrupciones.sacar()

        si dispositivo == "disco":
            imprimir("Manejando interrupción de disco: operación completa.")
            // Desbloquear proceso esperando por disco
            desbloquear(proceso1)
        si dispositivo == "red":
            imprimir("Manejando interrupción de red: datos recibidos.")
            // Desbloquear proceso esperando por red
            desbloquear(proceso2)
        si dispositivo == "teclado":
            imprimir("Manejando interrupción de teclado: tecla presionada.")
            // Desbloquear proceso esperando por teclado
            desbloquear(proceso3)

// Función que desbloquea un proceso
función desbloquear(proceso):
    imprimir("Proceso ", proceso, " reanudado.")


// Simulación del sistema operativo y dispositivos de E/S
función sistema_operativo():
    // Generar algunas interrupciones
    generar_interrupción("disco")
    generar_interrupción("red")
    generar_interrupción("teclado")

    // Manejar las interrupciones
    manejar_interrupciones()

// Ejecutar la simulación
sistema_operativo()

~~~

2. _Escribe un programa que utilice el manejo de interrupciones en un sistema básico de simulación_.

~~~
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

~~~


## 4.3 Estructuras de datos para manejo de dispositivos

1. _Investiga y explica qué es una cola de E/S. Diseña una simulación de una cola con prioridad_.
2. _Escribe un programa que simule las operaciones de un manejador de dispositivos utilizando una tabla de estructuras_.

~~~
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

~~~


## 4.4 Operaciones de Entrada/Salida

1. _Diseña un flujo que describa el proceso de lectura de un archivo desde un disco magnético. Acompáñalo con un programa básico que simule el proceso_.
2. _Implementa un programa en Python, C o Java que realice operaciones de entrada/salida asíncronas usando archivos_.

## Integración

1. _Escribe un programa que implemente el algoritmo de planificación de discos "Elevator (SCAN)"_.
2. _Diseña un sistema que maneje múltiples dispositivos simulados (disco duro, impresora, teclado) y muestra cómo se realiza la comunicación entre ellos_.

# Avanzados

1. _Explica cómo los sistemas operativos modernos optimizan las operaciones de entrada/salida con el uso de memoria caché_.
