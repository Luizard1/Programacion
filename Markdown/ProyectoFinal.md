# __SISTEMAS DE ARCHIVOS__
# EJERCICIO 1: Concepto y noción de archivo real y virtual.

## Define el concepto de archivo real y archivo virtual.
* Archivo real: todo aquel archivo, programa o datos que se guarda en la computadora, y que al apagar el sistema permanece, es decir, todos aquellos archivos que ocupan una parte física en bytes en la computadora.
* Archivo virtual: es un archivo que se almacena en un sistema de almacenamiento en la nube, se puede visualizar cuando se consulta un archivo y genera una copia del original hasta que sea guardado físicamente. Otro tipo de arcihvos virtuales son aquellos que genera el sistema de manera temporal.

## Proporciona ejemplos de cómo los sistemas operativos manejan archivos reales y virtuales.
* Archivo real: Se muestran de manera real, en la información del espacio que ocupa en un disco duro o sistema de almacenamiento, en otras palabras, su tamaño en bytes.
*
* Archivo virtual: Se generan mientras se está en la ejecución de un proceso con la finalidad de almacenar información temporal y organizarla, su tamaño es muy variable y terminan al detener la ejecución del sistema, muchos de ellos son borrados, por ejemplo, los archivos *.tmp.

## Explica un caso práctico donde un archivo virtual sea más útil que un archivo real.
* A la hora de manejar gestores de datos o archivos, se generan primero archivos virtuales para ir almacenando lo que se tiene escrito en el gestor, sin guardarlo en caso de que al salir, no se quiera ocupar ese espacio en disco, sino hasta que se le de la orden al programa de que lo guarde como tal.

# EJERCICIO 2: Componentes de un sistema de archivos.

## Identifica los componentes clave de un sistema de archivos (por ejemplo, metadatos, tablas de asignación, etc.).
* Bloques o clústers. Son los espacios en los que se divide el almacenamiento, estos bloques son las unidades mínimas de almacenamiento en donde se pueden guardar datos.
* Tabla de archivos o directorio. Es una estructura que contiene información sobre los archivos almacenados en el sistema de archivos, nombres, tamaños, ubicaciones, permisos, entre otros metadatos.
* Estructura de metadatos. Incluye datos como: propietario y grupo del archivo, permisos de acceso (de lectura, escritura y/o ejecución), tiempos de acceso, tiempos de modificación, tiempos de cambio, dirección de bloques de datos en disco.
* Tabla de asignación. Se encarga de llevar el seguimiento de los bloques que pertenecen a cada archivo. En sistemas de archivos FAT, la tabla de asignación tiene entradas que indican qué bloques pertenecen a un archivo y cuál es el siguiente bloque en caso de que el archivo esté dividido.
* Superbloque. Es una estructura crítica que contiene la información principal sobre el sistema de archivos en sí, como el tamaño del sistema de archivos, número de bloques disponibles, información sobre los bloques de metadatos, entre otras cosas.
* Punteros. Son direcciones dentro de los metadatos que indican dónde están los bloques de datos reales en el disco.

## Crea un cuadro comparativo de cómo estos componentes funcionan en sistemas como EXT4 y NTFS.



## Describe las ventajas y desventajas de cada sistema basado en sus componentes.

# EJERCICIO 3: Organización lógica y física de archivos

## Diseña un árbol jerárquico que represente la organización lógica de directorios y subdirectorios.

## Explica cómo se traduce la dirección lógica a la dirección física en el disco.
* La memoria física se divide en bloques de tamaño fijo llamados marcos, y la memoria lógica se divide en bloques del mismo tamaño llamados páginas.

* Cuando la CPU genera una dirección, esta se divide en dos partes:

 * Número de página (p): Se utiliza como índice para acceder a una tabla de páginas que contiene las direcciones de las páginas en la memoria física.
 * Desplazamiento (d): Es la parte dentro de la página que se usa junto con la dirección base para obtener la dirección final en la memoria física.
* Un apuntador a la tabla de páginas se guarda en el bloque de control de procesos junto con otros registros del proceso. Al iniciar un proceso, el sistema operativo recarga los registros del usuario y actualiza la tabla de páginas de hardware con los valores correspondientes de la tabla de páginas de usuario.

* En un sistema con paginación, la transformación entre direcciones lógicas y físicas es invisible para el programador. Esto se realiza mediante una tabla de segmentos que tiene entradas con una base de segmento y un límite. El desplazamiento de la dirección lógica debe estar entre 0 y el límite del segmento; de lo contrario, se genera una excepción al sistema operativo.

## Proporciona un ejemplo práctico de cómo un archivo se almacena físicamente.
En el escenario de un sistema de archivos NTFS en Windows:
 * Segmentación: El archivo se divide en fragmentos que se almacenan en clústers que van generalmente de (4kb a 8kb).
 * Dependiendo de si el archivo está fragmentado o no, los archivos se almacenarán en clústers contiguos o no contiguos.
 * Cada archivo tiene una entrada en la MFT (Tabla maestra de archivos), que contiene metadatos del archivo como nombre, tamaño, ubicación en disco, etcétera.
 * Cuando el archivo se accede, el sistema operativo consulta la MFT y recupera los fragmentos del archivo desde los clústers correspondientes en el disco.

* _EJEMPLO_: si un archivo tiene 10KB y el tamaño de los clusters es de 4b, se dividiría en 3 fragmentos (uno de 4kb y dos de 3kb) y se almacena en 3 clústers no necesariamente contiguos.

# EJERCICIO 4: Mecanismos de acceso a los archivos

## Define los diferentes mecanismos de acceso.
* Acceso secuencial. Implica leer o escribir los datos en un archivo en un orden coninuo, uno tras otro.
* Acceso directo (o aleatorio). Permite acceder a cualquier parte del archivo sin necesidad de leer los datos en orden secuencial.
* Acceso por índice. Este mecanismo utiliza una estructura de índice que mantiene una lista de las ubicaciones de los datos dentro de un archivo.
* Acceso secuencial con índice. Es la combinación del acceso secuencial y acceso por índice, optimiza la búsqueda de archivos secuenciales grandes.
* Acceso por segmentos. En este mecanismo los archivos se dividen en segmentos lógicos, los cuales pueden ser tratados de forma independiente, lo que permite un acceso rápido a las partes del archivo sin necesidad de recorrer todo el archivo.

## Escribe un pseudocódigo que muestre cómo acceder a:
 * Un archivo secuencialmente.
 * Un archivo directamente mediante su posición.
 * Un archivo utilizando un índice.
## Compara las ventajas de cada mecanismo dependiendo del caso de uso.
* Acceso secuencial: es ideal para situaciones en las que se procesan datos en orden, como en archivos de registros o multimedia.
* Acceso directo/aleatorio: se recomienda cuando los archivos requieren acceso a ubicaciones específicas sin seguir un orden secuencial, como las bases de datos.
* Acceso por índice: su mayor ventaja reluce cuando se necesita acceder rápidamente a partes de un archivo grande, como en bases de datos que manejan grandes volúmenes de información.
* Acceso secuencial con índice: se podría decir que es el mejor o más óptimo de todos, prefiriendo usarse en busquedas en grandes archivos o catálogos.
* Acceso por segmentos: es excelente para gestionar grandes volúmenes de datos, como en bases de datos distribuidas o sistemas que manejen gran tamaño de manera paralela.

# EJERCICIO 5: Modelo jerárquico y mecanismos de recuperación en caso de falla

## Diseña un modelo jerárquico para un sistema de archivos con al menos tres niveles de directorios.

## Simula una falla en un directorio específico y describe los pasos necesarios para recuperarlo.

## Explica qué herramientas o técnicas de respaldo (backup) utilizarías para evitar pérdida de datos.
Utilizaría principalmente respaldos en la nube, para tener mi información segura sin importar el estado de mi infraestructura, acompañada claro de respaldos locales, además, ambos serían automáticos y programados, con el fin de no hacer la tarea de respaldo cada día hora, o tiempo definido, haciendo que sea 100% seguro que se hará y evitando error de olvido o algo parecido. Estos respaldos serían empleando la técnica de respaldo incremental, para no saturar los espacios de almacenamiento con información de la base de datos completa. Cabe destacar que, si los equipos (su rendimiento) lo permiten, optaría por respaldos continuos también, para asegurar al máximo que no habrá pérdida de datos.
# __PROTECCIÓN Y SEGURIDAD__

# EJERCICIO 1: Concepto y objetivos de protección y seguridad
## Define los conceptos de protección y seguridad en el contexto de sistemas operativos.
## Identifica los objetivos principales de un sistema de protección y seguridad, como confidencialidad, integridad y disponibilidad.
## Da un ejemplo práctico de cómo se aplican estos objetivos en un sistema operativo.

# EJERCICIO 2: Clasificación aplicada a la seguridad.
## Investiga las clasificaciones comunes de la seguridad, como física, lógica y de red.
## Explica el papel de cada clasificación en la protección de un sistema operativo.
## Proporciona ejemplos prácticos de herramientas o técnicas utilizadas en cada clasificación

# EJERCICIO 3: Funciones del sistema de protección.

## Describe cómo un sistema de protección controla el acceso a los recursos.
## Explica las funciones principales como autenticación, autorización y auditoría.
## Diseña un caso práctico donde se muestren las funciones de un sistema de protección en acción.

# EJERCICIO 4: Implantación de matrices de acceso.
## Diseña una matriz de acceso para un sistema con al menos 3 usuarios y 4 recursos.
## Explica cómo esta matriz se utiliza para controlar el acceso en un sistema operativo.
## Simula un escenario donde un usuario intenta acceder a un recurso no permitido y cómo la matriz lo bloquea.

# EJERCICIO 5:  Protección basada en el lenguaje.

## Explica el concepto de protección basada en el lenguaje.
## Proporciona un ejemplo de cómo un lenguaje como Java o Rust asegura la memoria y evita accesos no autorizados.
## Compara este enfoque con otros mecanismos de protección en sistemas operativos.

# EJERCICIO 6: Validación y amenazas al sistema.

## Investiga y describe al menos tres tipos de amenazas comunes (por ejemplo, malware, ataques de fuerza bruta, inyección de código).
## Explica los mecanismos de validación como autenticación multifactor y control de integridad.
## Diseña un esquema de validación para un sistema operativo con múltiples usuarios.

# EJERCICIO 7: Cifrado.
## Define los conceptos de cifrado simétrico y asimétrico.
## Proporciona un ejemplo práctico de cada tipo de cifrado aplicado en sistemas operativos.
## Simula el proceso de cifrado y descifrado de un archivo con una clave dada.
