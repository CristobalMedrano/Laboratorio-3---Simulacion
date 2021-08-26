#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <structs.h>
#include <constants.h>
#include <occupation.h>

// Crea el nodo Occupation
Occupation *createNodeOccupation()
{
    Occupation *newOccupation = (Occupation *)malloc(sizeof(Occupation));
    if (NULL != newOccupation)
    {
        newOccupation->occupancyTimes = 0.0;
        newOccupation->lengthQueue = 0;
        newOccupation->nextOccupation = NULL;
        return newOccupation;
    }
    return NULL;
}

// Crea la cola de ocupacion
Occupation *createOccupationQueue(Occupation *currentOccupation)
{
    Occupation *newNodeOccupation = createNodeOccupation();
    Occupation *newNodeAuxOccupation = createNodeOccupation();
    if (NULL != newNodeOccupation)
    {
        // Vacio
        if (NULL == currentOccupation)
        {
            return newNodeOccupation;
        }
        newNodeAuxOccupation = currentOccupation;

        int count = 1;
        while (NULL != newNodeAuxOccupation->nextOccupation)
        {
            count++;
            newNodeAuxOccupation = newNodeAuxOccupation->nextOccupation;
        }
        newNodeAuxOccupation->nextOccupation = newNodeOccupation;
        newNodeOccupation->lengthQueue = count;
        return currentOccupation;
    }
    return currentOccupation;
}

// Inserta un elemento en la cola de ocupacion
Occupation *insertElementOccupationQueue(Occupation *queue, int lengthQueue, float occupancyTime)
{
    // Si la pos ingresada es menor a 0, retorno la lista.
    if (lengthQueue < 0)
    {
        return queue;
    }

    Occupation *index = createNodeOccupation();
    index = queue;

    // Muevo el puntero a la posicion - 1 que no sea nula.
    while (index != NULL && index->lengthQueue != lengthQueue)
    {
        index = index->nextOccupation;
    }
    index->occupancyTimes = index->occupancyTimes + occupancyTime;
    //printf("Largo del nodo actual: %d, posicion a buscar: %d", index->lengthQueue, lengthQueue);
    return queue;
}

// Muestra los nodos que se encuentran dentro de la cola de ocupacion.
void showOccupation(Occupation *currentOccupation)
{
    if (currentOccupation != NULL)
    {
        Occupation *newNodeAuxOccupation = createNodeOccupation();
        newNodeAuxOccupation = currentOccupation;
        while (newNodeAuxOccupation != NULL)
        {
            printf("\n----------------------\n");
            printf("occupancyTimes: %f\n", newNodeAuxOccupation->occupancyTimes);
            printf("lengthQueue: %d\n", newNodeAuxOccupation->lengthQueue);
            newNodeAuxOccupation = newNodeAuxOccupation->nextOccupation;
        }
    }
}

// Obtiene el largo de la cola de ocupacion
int lengthOccupation(Occupation *currentOccupation)
{
    int i = 0;
    Occupation *indexOccupation = currentOccupation;
    while (indexOccupation != NULL)
    {
        indexOccupation = indexOccupation->nextOccupation;
        i++;
    }
    return i;
}

// Obtiene el tiempo de ocupacion de un nodo en la posicion dada.
float getTimeOccupation(Occupation *currentOccupation, int position)
{
    int i;
    if (position < 0)
    {
        return -1;
    }
    i = 0;
    Occupation *indexOccupation = currentOccupation;
    while (indexOccupation != NULL && i < position)
    {
        indexOccupation = indexOccupation->nextOccupation;
        i++;
    }
    if (indexOccupation == NULL)
    {
        return -1;
    }
    return indexOccupation->occupancyTimes;
}

// Libera la cola de ocupacion desde la memoria.
void freeOccupation(Occupation *currentOccupation)
{
    Occupation *newNodeOccupation = currentOccupation;
    Occupation *newNodeAuxOccupation = NULL;
    while (NULL != newNodeOccupation)
    {
        newNodeAuxOccupation = newNodeOccupation;
        newNodeOccupation = newNodeOccupation->nextOccupation;
        free(newNodeAuxOccupation);
    }
}