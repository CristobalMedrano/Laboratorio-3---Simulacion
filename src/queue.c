#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <structs.h>
#include <constants.h>
#include <queue.h>

// Crea un nodo de tipo Queue
Queue *createNodeQueue()
{
    Queue *newQueue = (Queue *)malloc(sizeof(Queue));
    if (NULL != newQueue)
    {
        newQueue->time = 0;
        newQueue->nextElement = NULL;
        return newQueue;
    }
    return NULL;
}

//Inserta un elemento en la cola
Queue *insertElementQueue(float time, Queue *currentQueue)
{
    Queue *newNodeQueue = createNodeQueue();
    Queue *newNodeAuxQueue = createNodeQueue();
    if (NULL != newNodeQueue)
    {
        if (NULL == currentQueue)
        {
            currentQueue = newNodeQueue;
            newNodeQueue->time = time;
            newNodeQueue->nextElement = NULL;
            free(newNodeAuxQueue);
            return currentQueue;
        }
        newNodeAuxQueue = currentQueue;
        while (NULL != newNodeAuxQueue->nextElement)
        {
            newNodeAuxQueue = newNodeAuxQueue->nextElement;
        }
        newNodeAuxQueue->nextElement = newNodeQueue;
        newNodeQueue->time = time;
        newNodeQueue->nextElement = NULL;
        return currentQueue;
    }
    return currentQueue;
}

// Obtiene el tiempo de un nodo en una posicion dada
float getTime(Queue *currentQueue, int position)
{
    int i;
    if (position < 0)
    {
        return -1;
    }
    i = 0;
    Queue *indexQueue = currentQueue;
    while (indexQueue != NULL && i < position)
    {
        indexQueue = indexQueue->nextElement;
        i++;
    }
    if (indexQueue == NULL)
    {
        return -1;
    }
    return indexQueue->time;
}

// Obtiene el largo de la cola.
int lengthQueue(Queue *currentQueue)
{
    int i = 0;
    Queue *indexQueue = currentQueue;
    while (indexQueue != NULL)
    {
        indexQueue = indexQueue->nextElement;
        i++;
    }
    return i;
}

// Muestra los datos de la cola
void showQueue(Queue *currentQueue)
{
    if (currentQueue != NULL)
    {
        Queue *newNodeAuxQueue = createNodeQueue();
        newNodeAuxQueue = currentQueue;
        while (newNodeAuxQueue != NULL)
        {
            printf("Element: %f\n", newNodeAuxQueue->time);
            newNodeAuxQueue = newNodeAuxQueue->nextElement;
        }
    }
}

// Libera memoria utilizada por la cola.
void freeQueue(Queue *currentQueue)
{
    Queue *newNodeQueue = currentQueue;
    Queue *newNodeAuxQueue = NULL;
    while (NULL != newNodeQueue)
    {
        newNodeAuxQueue = newNodeQueue;
        newNodeQueue = newNodeQueue->nextElement;
        free(newNodeAuxQueue);
    }
    free(newNodeQueue);
}
