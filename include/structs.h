#ifndef _STRUCTS_H
#define _STRUCTS_H

// Estructura que se utiliza para crear la cola de ocupacion
typedef struct Occupation
{
    float occupancyTimes;              // Tiempo de ocupacion acumulado.
    int lengthQueue;                   // Largo de la cola T(n).
    struct Occupation *nextOccupation; // Puntero al siguiente nodo.
} Occupation;

// Estructura que se utiliza para crear una cola.
typedef struct Queue
{
    float time;                // Tiempo.
    struct Queue *nextElement; // Puntero al siguiente nodo.
} Queue;

#endif