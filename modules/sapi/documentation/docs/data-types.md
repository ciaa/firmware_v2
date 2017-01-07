# Tipos de datos de la biblioteca sAPI

## Constantes

Se definen las siguientes constantes:

### Estados lógicos

- ``FALSE = 0``
- ``TRUE  = !FALSE``

### Estados funcionales

- ``ON  = 1``
- ``OFF = 0``

### Estados eléctricos

- ``HIGH = 1``
- ``LOW  = 0``

### Estados de habilitación

- ``ENABLE  = 1``
- ``DISABLE = 0``

## Tipos de datos básicos

Se definen los siguientes tipos de datos básicos:

### Booleano

- ``bool_t``

Valor booleano, puede valer TRUE o FALSE.

### Enteros 

Valores enteros.

Enteros sin signo, con rango de valores de 0 a ((2^N) - 1), *(N = número de bits)*.

- ``uint8_t``
- ``uint16_t``
- ``uint32_t``
- ``uint64_t``


Enteros con signo, con rango de valores de -2^(N-1) a (2^(N-1) - 1), *(N = número de bits)* y formato complemento a 2.


- ``int8_t``
- ``int16_t``
- ``int32_t``
- ``int64_t``


### Flotantes

Valores con punto flotante IEEE-754.

- ``float32_t``:

**Rango:** .

- ``float64_t``

**Rango:** .

### Tick

Es un tipo de datos para el conteo de tiempo transcurrido en la unidad Tick. 
Se almacena internamente como ``uint64_t``.

- ``tick_t``

## Tipos de datos avanzados

### String

- **String** ``String_t``

También define un tipo de datos para puntero a función:

``typedef bool_t (*sapiFuncPtr_t)(void *);``

- Parámetro: ``void *`` Para poder pasar cualquier argumento.
- Retorna: ``bool_t`` Para reportar errores (TRUE si todo está bien).

Utilizando este tipo de datos define la finción Nula que no hace nada y Retorna
siempre TRUE, esta se utiliza para evitar errores de NULL POINTER.

``bool_t sapiNullFuncPtr(void *);``

- Parámetro: ``void *`` No usado.
- Retorna: ``bool_t``Retorna siempre TRUE.

