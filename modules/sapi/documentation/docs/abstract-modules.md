# Módulos abstractos de la biblioteca sAPI

Representan módulos que agregan un mayor nivlel de abstracción sobre otros módulos, por ejemplo, periféricos físicos.

## Tick

Utiliza un **Timer**.

tickConfig( TICK_MS(1) ); o tickStart( TICK_MS(1) );
tickEnabeling( ENABLE );
tickSetCallback( function );

typedef tick_t uint64_t;

#define TICK_MS(t) ((typedef)(t))
#define TICK_S(t)  (((typedef)(t))*1000)

*(¿Porque alguien que solo quiere usar el Systick para medir intervalos tendria que tener en cuenta el callback?)*



**Configuración de interrupción periódica**

``bool_t tickConfig(tick_t tickRateMSvalue, sAPI_FuncPtr_t tickHook );``

- Parámetro: ``tick_t tickRateMSvalue`` cada cuantos ms ocurre un tick.
- Parámetro: ``sAPI_FuncPtr_t tickHook`` función a ejecutar en cada tick.
- Retorna: ``bool_t`` TRUE en en caso correcto o FALSE en caso de errores.

Configura una interrupción periódica de temporizador cada tickRateMSvalue
milisegundos para utilizar de base de tiempo del sistema. Una vez ejecutada
esta función se dice que ocurre un tick del sistema cada tickRateMSvalue
milisegundos.

La tasa de ticks en ms, tickRateMS, es un parámetro con rango de 1 a 50 ms.

Además de aumentar el conteo de ticks en cada interrupción, la función
tickConfig ejecuta la función pasada como parámero cada vez que ocurre un tick.
Si no se desea ejecutar ninguna función debe poner en cero este parámetro.

**Leer la variable del conteo actual de ticks**

``tick_t tickRead( void );``

- Parámetro: ``void`` sin parámetro.
- Retorna: ``tick_t`` el valor actual del contador de ticks.

La variable del conteo actual de ticks se incrementa en 1 cada tickRateMSvalue
milisegundos.

**Escribir la variable del conteo actual de ticks**

``void tickWrite( tick_t ticks );``

- Parámetro: ``tick_t ticks`` el nuevo valor a setear del contador de ticks.
- Retorna: ``void``

Se utiliza si se necesita cambiar el valor del contador de ticks, por ejemplo,
para resetearlo.

En la implementación para la CIAA utiliza internaente el peiférico temporizador
Systick para configurar una interrupción periódica.


## Delay

Utiliza el módulo **Tick**.

Para utilizar los retardos (con excepción del retardo inexacto) se debe
configurar el Tick ya que utiliza estas interrupciones como base de tiempo.

Todos los tiempos de parámetros están en milisegundos.

Define la constante ``#define INACCURATE_TO_MS 20400`` y contiene las funciones:

**Retardo inexacto bloqueante** ``void delayInaccurate( tick_t delay_ms );``

- Parámetros: ``tick_t delay_ms`` tiempo de duración del retardo en ms.
- Retorna: ``void``

Utiliza un bloque for bloqueante que tiene una constante calculada "a ojo"
(INACCURATE_TO_MS) para perder muchos ciclos de reloj y lograr hacer un retado.

**Retardo bloqueante** ``void delay ( tick_t time );``

- Parámetros: ``tick_t time``
- Retorna: ``void``

Utiliza el conteo de ticks para determinar el tiempo transcurrido resultando en
un retardo exacto. Es bloqueante pues se queda en un bucle while hasta que se
cuentan los ticks necesarios para lograr el tiempo especificado.

**Retardo no bloqueante**

Este tipo de retardo permite realizar otras tareas mientras se ejecuta ya que
simplemente se chequea si el tiempo de retardo se ha arribado en lugar de
quedarse bloqueado esperando a que se complete el tiempo como en los casos
anteriores.

Define el tipo de datos estructurado ``delay_t``

Contiene las funciones:

``void delayConfig( delay_t* delay, tick_t duration );``

- Parámetro: ``delay_t * delay`` dirección de memoria de una variable del tipo delay_t.
- Parámetro: ``tick_t duration`` tiempo de duración del retardo en ms.
- Retorna: ``void``

``bool_t delayRead( delay_t* delay );``

- Parámetro: ``delay_t* delay`` dirección de memoria de una variable del tipo delay_t.
- Retorna: ``bool_t`` TRUE cuando el delay se cumplió, FALSE en caso contrario.

``void delayWrite( delay_t* delay, tick_t duration );``

- Parámetro: ``delay_t* delay`` dirección de memoria de una variable del tipo delay_t.
- Parámetro: ``tick_t duration`` tiempo de duración del retardo en ms.
- Retorna: ``void``


Uso:

Se utiliza declarando una variable de estructura del tipo delay_t, por ejemplo:

``delay_t myDelay;``

Luego, se configura inicialmente pasando como parámetro la variable recién
declarada

``delayConfig( &myDelay, 500 );``

Se detecta con un bloque if si se cumplió el delay leyéndolo con

``delayRead( &myDelay );``

La primera vez que se ejecuta delayRead activa el mismo. delayRead devuelve TRUE
cuando se completo y se vuelve a relanzar automáticamente.

Con ``delayWrite( &myDelay, 1000 );`` se puede cambiar la duración de un delay
en tiempo de ejecución.


