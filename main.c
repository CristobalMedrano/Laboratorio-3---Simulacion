#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <structs.h>
#include <getopt.h>
#include <constants.h>
#include <options.h>
#include <queue.h>
#include <occupation.h>

// Esta funcion obtiene una muestra x exponencial con parametro a usando drandom48()
// La semilla usada es en base al tiempo del computador.
float inverseCDF(float a)
{
    if (a == 0)
    {
        return 0;
    }
    float random = -(1 / a) * log(1 - (float)drand48());
    return (random <= 0) ? 0.0 : random;
}

// Esta funcion obtiene la cantidad de clientes que existen en la cola.
int findThresholdQueue(Queue *currentQueue, float endTime)
{
    int currentLength = lengthQueue(currentQueue);
    int maxLength = 0;
    for (int i = 0; i < currentLength; i++)
    {
        maxLength = (getTime(currentQueue, i) <= endTime) ? maxLength + 1 : maxLength;
    }
    return maxLength;
}

// Calcula el tiempo de residencia total de la cola.
float SumResidenceTime(Queue *currentQueue, int departureLength)
{
    float time = 0;
    for (int k = 0; k < departureLength; k++)
    {
        time = getTime(currentQueue, k) + time;
    }
    return time;
}

// Obtiene la suma de todos los Qk para calcular el valor de Qn
float getQn(Occupation *currentQueue, int maxLength)
{
    float total = 0;
    float Qk = 0;
    for (int k = 0; k <= maxLength; k++)
    {
        Qk = getTimeOccupation(currentQueue, k);
        total = total + Qk;
    }
    return total;
}

//Funcion que se utiliza para calcular el largo medio de la cola
float sumMeanQueue(Occupation *currentQueue, int maxLength, float Q_N)
{
    if (Q_N == 0)
    {
        return 0.0;
    }

    float total = 0;
    float Qk = 0;
    for (int k = 0; k <= maxLength; k++)
    {
        Qk = getTimeOccupation(currentQueue, k);
        total = total + (float)k * Qk;
    }
    return 1 / (Q_N)*total;
}

//Entradas: argc: Numero de argumentos ingresados al momento de ejecutar el programa.
//          argv: Arreglo con los argumentos del programa.
//
//Funcionamiento: Funcion principal del programa, en esta funcion se lleva a cabo el pipeline de 6 etapas.
//
//Salidas: Retorna 0 si la ejecucion fue correcta y 1 si la ejecucion fue incorrecta.
int main(int argc, char *argv[])
{
    // Semilla del random
    srand48(time(0));

    // Opciones ingresadas por el usuario.
    float arrivalRate = 0;
    float departureRate = 0;
    float endTime = 0;
    int isValidOpt = FALSE;

    // Obtencion de los argumentos ingresados por el usuario.
    getOptionsArguments(argc, argv, &arrivalRate, &departureRate, &endTime);

    // Se validan los argumentos obtenidos de la funcion anterior
    isValidOpt = validateArgs(arrivalRate, departureRate, endTime);

    // Si los argumentos son correctos se inicia el pipeline
    if (isValidOpt == TRUE)
    {
        Queue *arrivalTimesQueue = NULL;
        Queue *departureTimesQueue = NULL;
        Queue *systemTimesQueue = NULL;
        Queue *Y = NULL;
        Queue *Z = NULL;

        Y = insertElementQueue(inverseCDF(arrivalRate), Y);
        Z = insertElementQueue(inverseCDF(departureRate), Z);

        arrivalTimesQueue = insertElementQueue(getTime(Y, 0), arrivalTimesQueue);
        systemTimesQueue = insertElementQueue(getTime(Z, 0), systemTimesQueue);
        departureTimesQueue = insertElementQueue((getTime(Y, 0) + getTime(Z, 0)), departureTimesQueue);

        int previousValue = 0;

        while (endTime > getTime(arrivalTimesQueue, previousValue))
        {
            float y = inverseCDF(arrivalRate);
            Y = insertElementQueue(y, Y);

            float z = inverseCDF(departureRate);
            Z = insertElementQueue(z, Z);

            float currentArrivalTime = getTime(arrivalTimesQueue, previousValue) + y;
            arrivalTimesQueue = insertElementQueue(currentArrivalTime, arrivalTimesQueue);

            float previousDepartureTime = getTime(departureTimesQueue, previousValue);

            // si el que acabo de agregar (arrival) es mayor al departure anterior, debo sumar el arrival de ahora + z de ahora.
            // sino tengo que sumar departure anterior + z de ahora.
            if (currentArrivalTime > previousDepartureTime)
            {
                departureTimesQueue = insertElementQueue(currentArrivalTime + z, departureTimesQueue);
            }
            else
            {
                departureTimesQueue = insertElementQueue(previousDepartureTime + z, departureTimesQueue);
            }
            previousValue++;

            // dep actual - arrival actual
            systemTimesQueue = insertElementQueue(getTime(departureTimesQueue, previousValue) - currentArrivalTime, systemTimesQueue);
        }

        // El tiempo actual es una variable aparte para tener de referencia entre arrival y departure.
        int maxLengthQueue = 0;
        float currentTime = 0.0;
        int arrivalPosition = 0;
        int departurePosition = 0;
        int occupationQueuePosition = 0;
        Occupation *occupationQueue = NULL;

        for (int i = 0; i < lengthQueue(arrivalTimesQueue); i++)
        {
            occupationQueue = createOccupationQueue(occupationQueue);
        }

        if (getTime(arrivalTimesQueue, arrivalPosition) < endTime)
        {
            // Entra el primer arrival.
            occupationQueue = insertElementOccupationQueue(occupationQueue, occupationQueuePosition, getTime(arrivalTimesQueue, arrivalPosition) - currentTime);
            currentTime = getTime(arrivalTimesQueue, arrivalPosition);
            occupationQueuePosition++;
            arrivalPosition++;

            maxLengthQueue = (maxLengthQueue < occupationQueuePosition) ? occupationQueuePosition : maxLengthQueue;

            while (getTime(arrivalTimesQueue, arrivalPosition) < endTime || getTime(departureTimesQueue, departurePosition) < endTime)
            {
                if (getTime(arrivalTimesQueue, arrivalPosition) < getTime(departureTimesQueue, departurePosition))
                {
                    // Entra un arrival.
                    occupationQueue = insertElementOccupationQueue(occupationQueue, occupationQueuePosition, getTime(arrivalTimesQueue, arrivalPosition) - currentTime);
                    currentTime = getTime(arrivalTimesQueue, arrivalPosition);
                    occupationQueuePosition++;
                    arrivalPosition++;
                    // ------------------
                }
                else
                {
                    // Sale un departure.
                    occupationQueue = insertElementOccupationQueue(occupationQueue, occupationQueuePosition, getTime(departureTimesQueue, departurePosition) - currentTime);
                    currentTime = getTime(departureTimesQueue, departurePosition);
                    occupationQueuePosition--;
                    departurePosition++;
                    // ------------------
                }
                // Se actualiza el valor maximo de la cola
                maxLengthQueue = (maxLengthQueue < occupationQueuePosition) ? occupationQueuePosition : maxLengthQueue;
            }
        }

        // Se calculan los parametros pedidos.
        int N_a = findThresholdQueue(arrivalTimesQueue, endTime);
        int N_d = findThresholdQueue(departureTimesQueue, endTime);
        int N = maxLengthQueue;
        float Q_0 = getTimeOccupation(occupationQueue, 0);
        float Q_N = getQn(occupationQueue, N);
        float U = (Q_N == 0.0) ? 0.0 : 1.0 - (Q_0 / Q_N);
        float X = sumMeanQueue(occupationQueue, N, Q_N);
        float S = (N_d == 0) ? 0.0 : (1.0 / N_d) * SumResidenceTime(systemTimesQueue, N_d);

        printf("Numero de clientes que llegaron : %d\n", N_a);
        printf("Numero de clientes que salieron: %d\n", N_d);
        printf("Tiempo total de cola vacia: %.3f\n", Q_0);
        printf("Largo maximo de la cola: %d\n", N);
        printf("Tiempo total de cola largo maximo: %.3f\n", Q_N);
        printf("Utilizacion: U %.3f\n", U);
        printf("Largo promedio de la cola: %.3f\n", X);
        printf("Tiempo promedio de residencia: %.3f\n", S);

        // Se libera memoria
        freeOccupation(occupationQueue);
        freeQueue(arrivalTimesQueue);
        freeQueue(departureTimesQueue);
        freeQueue(systemTimesQueue);
        freeQueue(Y);
        freeQueue(Z);
        return SUCCESS;
    }
    else
    {
        return FAILURE;
    }
}
