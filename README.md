# Como ejecutar el programa

### Compilación

Se provee de un makefile para compilar el programa. Este makefile tiene variadas opciones:

- make (compila el programa)
- make clean (borra los archivos compilados)

### Ejecución

El simulador se ejecutara de la siguiente forma:

```console
mm1 -a tasadearribos -d tasadesalidas -t tiempoend
```

Donde la opción:

- -a especifica la tasa de arribos (por ejemplo 4 jobs/minutos)
- -d especifica la tasa de servicio (por ejemplo 6 jobs/minutos)
- -t es el tiempo final de simulación.

Por ejemplo:

```console
mm1 -a 4 -d 6 -t 10
```

Esto mostrará por pantalla lo siguiente\*:

Numero de cliente que llegaron: N_a
Numero de clientes que salieron: N_d
Tiempo total de cola vacía: Q_0
Largo máximo de la cola: N
Tiempo total de cola largo máximo: Q_N
Utilización: U
Largo promedio de la cola: X
Tiempo promedio de residencia: S

\*_Debido a que se utiliza la función drandom48, para que no siempre se generaran los mismos, se utiliza una semilla basa en el tiempo actual. Esta semilla se encuentra en la línea 89 del archivo main.c_
