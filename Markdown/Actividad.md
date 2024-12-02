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
2. _Diseña un algoritmo para calcular qué procesos pueden ser asignados a un sistema con memoria real limitada utilizando el algoritmo de "primera cabida"_.

## 3.3 Organización de memoria virtual

1. _Investiga y explica el concepto de "paginación" y "segmentación". ¿Cuáles son las ventajas y desventajas de cada técnica?_
    * **Paginación**:
2. _Escribe un programa que simule una tabla de páginas para procesos con acceso aleatorio a memoria virtual_.

## 3.4 Administración de memoria virtual

1. _Escribe un código que implemente el algoritmo de reemplazo de página "Least Recently Used" (LRU)_.
2. _Diseña un diagrama que represente el proceso de traducción de direcciones virtuales a físicas en un sistema con memoria virtual_.

## Integración

1. _Analiza un sistema operativo moderno (por ejemplo, Linux o Windows) e identifica cómo administra la memoria virtual_.
2. _Realiza una simulación en cualquier lenguaje de programación que emule el swapping de procesos en memoria virtual_.

# Administración de Entrada/Salida

## 4.1 Dispositivos y manejadores de dispositivos

1. _Explica la diferencia entre dispositivos de bloque y dispositivos de carácter. Da un ejemplo de cada uno_.
2. _Diseña un programa que implemente un manejador de dispositivos sencillo para un dispositivo virtual de entrada_.

## 4.2 Mecanismos y funciones de los manejadores de dispositivos

1. _Investiga qué es la interrupción por E/S y cómo la administra el sistema operativo. Escribe un ejemplo en pseudocódigo para simular este proceso_.
2. _Escribe un programa que utilice el manejo de interrupciones en un sistema básico de simulación_.

## 4.3 Estructuras de datos para manejo de dispositivos

1. _Investiga y explica qué es una cola de E/S. Diseña una simulación de una cola con prioridad_.
2. _Escribe un programa que simule las operaciones de un manejador de dispositivos utilizando una tabla de estructuras_.

## 4.4 Operaciones de Entrada/Salida

1. _Diseña un flujo que describa el proceso de lectura de un archivo desde un disco magnético. Acompáñalo con un programa básico que simule el proceso_.
2. _Implementa un programa en Python, C o Java que realice operaciones de entrada/salida asíncronas usando archivos_.

## Integración

1. _Escribe un programa que implemente el algoritmo de planificación de discos "Elevator (SCAN)"_.
2. _Diseña un sistema que maneje múltiples dispositivos simulados (disco duro, impresora, teclado) y muestra cómo se realiza la comunicación entre ellos_.

# Avanzados

1. _Explica cómo los sistemas operativos modernos optimizan las operaciones de entrada/salida con el uso de memoria caché_.
