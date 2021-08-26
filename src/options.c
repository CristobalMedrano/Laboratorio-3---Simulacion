#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <getopt.h>
#include <constants.h>
#include <options.h>

//Entradas: argc (int): Numero de argumentos ingresados al momento de ejecutar el programa.
//          argv (char*): Arreglo con los argumentos del programa.
//          arrivalRate (float*): Especifica la tasa de arribos (por ejemplo 4 jobs/minutos).
//          departureRate (float*): Especifica la tasa de servicio (por ejemplo 6 jobs/minutos).
//          endTime (float*): Es el tiempo final de simulacion (por ejemplo 4 minutos).
//
//Funcionamiento: Procedimiento que obtiene los datos ingresados por el usuario, de no existir alguna opcion
//                obligatoria, el programa termina su ejecucion indicando el error por pantalla.
//
//Salidas: Vacia, se retornan los datos por referencia.
void getOptionsArguments(int argc, char *argv[], float *arrivalRate, float *departureRate, float *endTime)
{

    // Se inicializan los datos
    int option = 0;

    // Si la cantidad de argumentos del programa no supera los argumentos minimos requeridos, el programa muestra
    // el error y termina la ejecucion de este.
    if (argc < MIN_OPTS)
    {
        showCorrectUse(argv);
        exit(EXIT_FAILURE);
    }
    else
    {
        // Se leen las opciones ingresadas por el usuario
        while ((option = getopt(argc, argv, "a:d:t:")) != -1)
        {
            switch (option)
            {
            case 'a':
                // Se verifica que sea un flotante el valor ingresado, sino, el programa termina su ejecucion.
                if (!isFloat(optarg, "tasa de arribos"))
                {
                    showCorrectUse(argv);
                    exit(EXIT_FAILURE);
                }
                // Se retorna por referencia el valor para la tasa de arribos
                *arrivalRate = strtof(optarg, NULL);

                break;
            case 'd':
                // Se verifica que sea un flotante el valor ingresado, sino, el programa termina su ejecucion.
                if (!isFloat(optarg, "tasa de servicio"))
                {
                    showCorrectUse(argv);
                    exit(EXIT_FAILURE);
                }
                // Se retorna por referencia el valor para la tasa de salidas.
                *departureRate = strtof(optarg, NULL);

                break;
            case 't':

                // Se verifica que sea un flotante el valor ingresado, sino, el programa termina su ejecucion.
                if (!isFloat(optarg, "tiempo final de simulacion"))
                {
                    showCorrectUse(argv);
                    exit(EXIT_FAILURE);
                }
                // Se retorna por referencia el valor para el tiempo final de simulacion.
                *endTime = strtof(optarg, NULL);

                break;
            default:
                // Si algun argumento no es correcto, se muestra el error por pantalla y el programa finaliza su ejecucion
                showCorrectUse(argv);
                exit(EXIT_FAILURE);
                break;
            }
        }
    }
}

//Entradas: argv (char*): Arreglo con los argumentos del programa.
//
//Funcionamiento: Muestra por pantalla el error de argumentos.
//
//Salidas: No posee.
void showCorrectUse(char *argv[])
{
    // Se muestra el error por pantalla.
    printf("ERROR. Se ingreso un numero incorrecto de opciones/argumentos\n");
    fprintf(stderr, "Uso: %s [-a tasadearribos (jobs/minutos)] [-d tasadesalidas (jobs/minutos)] [-t tiempoend (minutos)]\n", argv[0]);
}

//Entradas: optarg (char*): String que contiene la opcion ingresada por el usuario.
//          type (char*): String que contiene un mensaje tipo caracteristico de cada funcion.
//
//Funcionamiento: Verifica si el argumento ingresado (optarg) es un entero.
//
//Salidas: Retorna TRUE (1) si el argumento es un entero y FALSE (0), si no lo es.
int isFloat(char *optarg, char *type)
{
    // Se inicializan las variables
    int i = 0;
    char dash = '-';
    // Si el argumento es valido
    if (optarg != NULL)
    {
        // Para cada letra en el string argumento, se verifica
        for (i = 0; i < strlen(optarg); i++)
        {
            // Si contiene un punto, coma o guion, ademas de verificar si es una letra
            if (optarg[i] == dash ||
                isalpha(optarg[i]))
            {
                printf("ERROR. El valor para %s debe ser un decimal (separado en .) positivo.\n", type);
                // Si contiene algun caracter, retorna falso.
                return FALSE;
            }
        }
        // En caso contrario, optarg es un entero y retorna verdadero.
        return TRUE;
    }
    else
    {
        // Si no existe un argumento, retorna inmediatamente falso
        return FALSE;
    }
}

//Entradas: arrivalRate (float): Flotante con la tasa de arribos
//          departureRate (float): Flotante con la tasa de salida
//          endTime (float): Flotante con el tiempo final de simulacion
//
//Funcionamiento: Verifica el estado de validacion de cada argumento.
//
//Salidas: Retorna TRUE (1) si todos los argumentos son validos o retorna FALSE (0) si algun argumento es incorrecto.
int validateArgs(float arrivalRate, float departureRate, float endTime)
{
    int validation1 = validateNumber(arrivalRate);
    int validation2 = validateNumber(departureRate);
    int validation3 = validateNumber(endTime);
    if (validation1 == TRUE &&
        validation2 == TRUE &&
        validation3 == TRUE)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

//Entradas: number (float): Flotante con un numero.
//
//Funcionamiento: Valida si el numero ingresado es positivo.
//
//Salidas: Retorna verdadero (TRUE 1) si el umbral es correto y falso (FALSE 0) si el umbral es incorrecto.
int validateNumber(float number)
{
    // Si el umbral es negativo
    if (number < (float)0)
    {
        // Se indica que existe un error.
        printf("ERROR. Numero invalido (negativo).\n");
        // Se retorna falso.
        return FALSE;
    }
    else
    {
        // el umbral es valido y se retorna verdadero.
        return TRUE;
    }
}