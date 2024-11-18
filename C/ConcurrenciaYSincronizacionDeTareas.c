#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* tarea1(void* arg) {
    printf("Inicio de tarea 1\n");
    sleep(1);
    printf("Fin de tarea 1\n");
    return NULL;
}

void* tarea2(void* arg) {
    printf("Inicio de tarea 2\n");
    sleep(1);
    printf("Fin de tarea 2\n");
    return NULL;
}

int main() {
    pthread_t hilo1, hilo2;
    pthread_create(&hilo1, NULL, tarea1, NULL);
    pthread_create(&hilo2, NULL, tarea2, NULL);

    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);
    printf("Ambas tareas han terminado de forma concurrente\n");
    return 0;
}
