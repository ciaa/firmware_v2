# Periféricos físicos de la biblioteca sAPI

Modelan peiféricos con existencia física en el SoC. Estos periféricos no son
"creables", solamente son "inicializables", además, tienen definidos nombres
prefijados que no se pueden destruir o crear dos veces. Es decir, no se puede,
por ejemplo, tener 10 SPI apuntando al mismo elemento fisico; SPI0, es SPI0 
desde que el software arranca hasta que termina o se destrulle el chip.

Los periféricos modelados son:

- GPIO0 a GPIO63.
- ADC0 a ADC7. Tienen 8 canales cada uno.
- DAC0 a DAC7.
- TIMER0 a TIMER7.
- RCT0 a RCT3.
- UART0 a UART7.
- I2C0 a I2C7.
- SPI0 a SPI7.
- POWER_MANAGEMENT.

## GPIO

GPIO modela un único pin de entrada/salida de porpósito general. El valor de un
pin es booleano.

### Propiedades de GPIO

- Propiedades de configuración:
    - ``mode`` (tipo ``gpioConfig_t``).
    - ``speed`` (tipo ``gpioConfig_t``).
    - ``power`` (tipo ``gpioConfig_t``).
- Propiedades de valor:
    - ``value`` (tipo ``bool_t``).
- Propiedades de eventos:
    - ``event`` (tipo ``gpioConfig_t``).
    - ``eventCallback`` (tipo ``Callback_t``).

**Valores posibles:**

- mode:
    - ``GPIO_INPUT`` (valor por defecto). Posibles flags de modificación:
        - ``GPIO_NOPULL`` (valor por defecto)
        - ``GPIO_PULLUP``
        - ``GPIO_PULLDOWN``
        - ``GPIO_PULLUP | GPIO_PULLDOWN``
        - ``GPIO_PULLUPDOWN``
    - ``GPIO_OUTPUT``. Posibles flags de modificación:
        - ``GPIO_PUSHPULL`` (valor por defecto)
        - ``GPIO_PUSHPULL | GPIO_STRENGTH(i)`` (i = 0,...,7)
        - ``GPIO_OPENCOLLECTOR`` ( es equivalente también ``GPIO_OPENDRAIN``)
        - ``GPIO_OPENCOLLECTOR | GPIO_PULLUP``
- speed: ``GPIO_SPEED(i)`` (i = 0,...,7)

- power: ``ON`` (valor por defecto), ``OFF``, ``ENABLE`` o ``DISABLE``

- value: ``ON``, ``OFF``, ``HIGH``, ``LOW``, ``TRUE`` o ``FALSE``

- event:
    - ``GPIO_EVENT_DISABLE`` (valor por defecto)
    - ``GPIO_LEVEL`` Level-sensitive (high/low). Posibles flags de modificación:
        - ``GPIO_LEVEL_HIGH`` (valor por defecto)
        - ``GPIO_LEVEL_LOW``
        - ``GPIO_LEVEL_HIGH | GPIO_LEVEL_LOW``
        - ``GPIO_LEVEL_BOTH``
    - ``GPIO_EDGE`` Edge (Rising/falling). Posibles flags de modificación:
        - ``GPIO_EDGE_RISING`` (valor por defecto)
        - ``GPIO_EDGE_FALLING``
        - ``GPIO_EDGE_RISING | GPIO_EDGE_FALLING``
        - ``GPIO_EDGE_BOTH``
    - ``GPIO_ASYNCHRONOUS_EDGE`` Asynchronous Edge (Rising/falling). Posibles flags de modificación:
        - ``GPIO_EDGE_RISING`` (valor por defecto)
        - ``GPIO_EDGE_FALLING``
        - ``GPIO_EDGE_RISING | GPIO_EDGE_FALLING``
        - ``GPIO_EDGE_BOTH``
- eventCallback:
    - Una estructura con el puentero a función y el puntero al parámetro que le pueda pasar el usuario a dicha función.


### Métodos de GPIO

**Getters y Setters de todas sus propiedades**

- Getters y Setters de configuración:
    - ``mode``
        - ``gpioSetMode( GPIO<i>, GPIO_INPUT | GPIO_PULLUP );``

        - ``gpioSetMode( GPIO<i>, GPIO_OUTPUT | GPIO_PUSHPULL | GPIO_STRENGTH(7) );``
        - ``gpioMode = gpioGetMode( GPIO<i> );``
    - ``speed``
        - ``gpioSetSpeed( GPIO<i>, GPIO_SPEED(7) );``
        - ``gpioSpeed = gpioGetSpeed( GPIO<i> );``
    - ``power``
        - ``gpioSetPower( GPIO<i>, ON );``
        - ``booleanValue = gpioGetPower( GPIO<i> );``
- Getters y Setters de valor:
    - ``value``
        - ``gpioSetValue( GPIO<i>, HIGH );``
        - ``booleanValue = gpioGetValue( GPIO<i> );``
- Getters y Setters de eventos:
    - ``event``
        - ``gpioSetEvent( GPIO<i>, GPIO_EDGE | GPIO_EDGE_RISING );``
        - ``gpioEvent = gpioGetEvent( GPIO<i> );``
    - ``eventCallback``
        - ``gpioSetValue( GPIO<i>, HIGH );``
        - ``booleanValue = gpioGetValue( GPIO<i> );``

**Configuración inicial y modo de una entrada o salida**

``bool_t gpioConfig( gpioMap_t pin, gpio_t mode );``

- Parámetro: ``gpioMap_t pin`` pin a configurar (ver GPIO Map).
- Parámetro: ``gpioConfig_t config`` configuración.
- Retorna: ``bool_t`` TRUE si la configuración es correcta.

Alias de ``gpioSetMode();`

**Lectura de Entrada**

``bool_t gpioRead( gpioMap_t pin );``

- Parámetro: ``gpioMap_t pin`` pin a leer (ver GPIO Map).
- Retorna: ``bool_t`` estado del pin.

Alias de ``gpioGetValue();``

**Escritura de Salida**

``void gpioWrite( gpioMap_t pin, bool_t value );``

- Parámetro: ``gpioMap_t pin`` pin a escribir (ver GPIO Map).
- Parámetro: ``bool_t value`` valor a escribir en el pin.
- Retorna: nada.

Alias de ``gpioSetValue();``

## ADC

Manejo de conversor analógico-digital.

**Configuración inicial de conversor analógico-digital**

``void adcConfig( adcConfig_t config );``

- Parámetro: ``adcConfig_t config`` configuración.
- Retorna: ``void``.

Posibles configuraciones:

- ``ADC_ENABLE`` Habilita el periférico ADC.
- ``ADC_DISABLE`` Deshabilita el periférico ADC.

**Lectura de Entrada analógica**

``uint32_t adcRead( adcMap_t analogInput );``

- Parámetro: ``adcMap_t analogInput`` pin a leer (ver ADC Map).
- Retorna: ``uint32_t`` el valor actual de la entrada analógica.


## DAC

Manejo de conversor digital-analógico.

**Configuración inicial de conversor digital-analógico**

``void dacConfig( dacConfig_t config );``

- Parámetro: ``dacConfig_t config`` configuración.
- Retorna: ``void``.

Posibles configuraciones:

- ``DAC_ENABLE`` Habilita el periférico DAC.
- ``DAC_DISABLE`` Deshabilita el periférico DAC.

**Escritura de Salida analógica**

``void dacWrite( dacMap_t analogOutput, uint32_t value );``

- Parámetro: ``dacMap_t analogOutput`` pin a escribir (ver DAC Map).
- Parámetro: ``uint32_t value`` valor del pin a escribir.
- Retorna: ``void``.



## Timer

### PWM

Manejo de salidas PWM (modulación por ancho de pulso). En la EDU-CIAA-NXP se
utiliza internamente el periférico SCT para generar los PWM.

**Configuración**

``bool_t pwmConfig( pwmMap_t pwmNumber, pwmConfig_t config);``

- Parámetro: ``pwmMap_t pwmNumber`` pin a configurar como salida PWM (ver PWM Map).
- Parámetro: ``uint8_t config`` configuración.
- Retorna: ``bool_t`` TRUE si la configuración es correcta.

Posibles configuraciones:

- ``PWM_ENABLE`` habilita el o los Timers en modo PWM.
- ``PWM_DISABLES`` deshabilita el o los Timers en modo PWM.
- ``PWM_ENABLE_OUTPUT`` habilita la salida PWM particular.
- ``PWM_DISABLE_OUTPUT`` deshabilita la salida PWM particular.

**Lectura del ciclo de trabajo (duty cycle) de la salida PWM**

``uint8_t pwmRead( pwmMap_t pwmNumber );``

- Parámetro: ``pwmMap_t pwmNumber`` salida PWM a leer el ciclo de trabajo.
- Retorna: ``uint8_t`` el ciclo de trabajo de la salida PWM.

 **Establecer el ciclo de trabajo de la salida PWM**

``bool_t pwmWrite( pwmMap_t pwmNumber, uint8_t percent );``

- Parámetro: ``pwmMap_t pwmNumber`` salida PWM a leer el ciclo de trabajo.
- Parámetro: ``uint8_t percent`` valor de ciclo de trabajo a setear en la salida PWM.
- Retorna: ``bool_t`` TRUE.



## RTC

Manejo del periférico RTC (reloj de tiempo real).

**Configuración**

``bool_t rtcConfig( rtc_t * rtc );``

- Parámetro: ``rtc_t * rtc`` Puntero a estructura de configuración del tipo RTC_t.
- Retorna: ``bool_t`` TRUE si la configuración es correcta.

La estructura del tipo ``RTC_t`` contiene los parámetros:

- ``uint16_t year`` año, con valores desde 1 a 4095.
- ``uint8_t month`` mes, con valores desde 1 a 12.
- ``uint8_t mday`` día, con valores desde 1 a 31.
- ``uint8_t wday`` día de la semana, con valores desde 1 a 7.
- ``uint8_t hour`` horas, con valores desde 0 a 23.
- ``uint8_t min`` minutos, con valores desde 0 a 59.
- ``uint8_t sec`` segundos, con valores desde 0 a 59.

**Lectura de fecha y hora**

``bool_t rtcRead( rtc_t * rtc );``

- Parámetro: ``rtc_t * rtc`` Puntero a estructura del tipo RTC_t donde se guarda la fecha y hora.
- Retorna: ``bool_t`` TRUE.

**Establecer la fecha y hora**

``bool_t rtcWrite( rtc_t * rtc );``

- Parámetro: ``rtc_t * rtc`` Puntero a estructura del tipo RTC_t con la nueva fecha y hora a setear.
- Retorna: ``bool_t`` TRUE.




## UART

Modela periférico de comunicación UART (transmisor/receptor asincrónico universal), coumnmente llamado *puerto serie*.


### Propiedades de UART

- Propiedades de configuración:
    - ``baudRate``
    - ``dataBits``
    - ``stopBits``
    - ``parity``
    - ``power``
- Propiedades de valor:
    - ``txValue``
    - ``rxValue``
- Propiedades de eventos:
    - ``receiveByteEvent``
    - ``receiveByteEventCallback``
    - ``transmiterFreeEvent``
    - ``transmiterFreeEventCallback``

Valores posibles:

- baudRate: ``1200``, ``2400``, ``4800``, ``9600``, ``19200``, ``38400``, ``57600`` o ``115200``.
- dataBits: ``5`` (o ``0``), ``6``, ``7``, ``8`` o ``9``.
- stopBits: ``1`` (o ``0``) o ``2``.
- parity: ``UART_PARITY_NONE`` (o ``0``), ``UART_PARITY_ODD`` (o ``1``)  o ``UART_PARITY_EVEN`` (o ``2``) .

- power: ``ON``, ``OFF``, ``ENABLE`` o ``DISABLE``

- txValue: Un valor del tipo ``uint8_t``.
- rxValue: {solo lectura} devuelve un valor del tipo ``uint8_t``.

- receiveByteEvent: ``UART_EVENT_DISABLE`` (valor por defecto) o ``UART_EVENT_ENABLE``
- receiveByteEventCallback: Una estructura con el puentero a función y el puntero al parámetro que le pueda pasar el usuario a dicha función.

- transmiterFreeEvent: ``UART_EVENT_DISABLE`` (valor por defecto) o ``UART_EVENT_ENABLE``
- transmiterFreeEventCallback: Una estructura con el puentero a función y el puntero al parámetro que le pueda pasar el usuario a dicha función.


### Métodos de UART

- Getters y Setters de sus propiedades.

- Initialize: ``uartInitialize( UART<i>, UART_BAUDRATE(b) | UART_DATABITS(d) | UART_STOPBITS(s) | UART_PARITY(p) );``
    - b = un valor de baudRate.
    - d = un valor de dataBits.
    - s = un valor de stopBits:.
    - p = un valor de parity.

- Métodos optimizados utilizando buffers:
    - ``uartRead( UART<i>, uint8_t* buffer, bufferSize );``
    - ``uartWrite( UART<i>, uint8_t* buffer, bufferSize );``

- Métodos *legacy*: *(pensemos si los ponemos o no ??)*

    - ``uartReadByte();`` alias de ``uartGetRxValue();``
    - ``uartWriteByte();`` alias de ``gpioSetTxValue();``
    - ``uartConfig();`` alias de ``uartInitialize();``
    - ``uartWriteString();`` *(que opinan de modelar un tipo string_t ??)*

**Configuración**

``void uartConfig( uartMap_t uart, uint32_t baudRate )``

- Parámetro: ``uartMap_t uart`` UART a configurar (ver UART MAP).
- Parámetro: ``uint32_t baudRate`` tasa de  bits.
- Retorna: ``void``.

Posibles configuraciones de baudRate: ``9600, 57600, 115200, etc.``

**Recibir Byte**

``bool_t uartReadByte( uartMap_t uart, uint8_t* receivedByte );``

- Parámetro: ``uartMap_t uart`` UART a configurar (ver UART Map).
- Parámetro: ``uint8_t* byte`` Dirección de memoria a donde se escribirá el dato recibido en caso de que haya un dato para recibir.
- Retorna: ``bool_t`` TRUE si recibió un dato, FALSE en caso contrario.

**Enviar Byte**

``void uartWriteByte( uartMap_t uart, uint8_t byte );``

- Parámetro: ``uartMap_t uart`` UART a configurar (ver UART Map).
- Parámetro: ``uint8_t byte`` Byte a enviar.
- Retorna: ``void``.

**Enviar String**

``void uartWriteString( uartMap_t uart, char* str );``

- Parámetro: ``uartMap_t uart`` UART a configurar (ver UART Map).
- Parámetro: ``char* str`` String a enviar, puede ser un literal, por ejemplo "hola", o un vector de uint8_t terminado en 0 o '\0' (caracter NULL).
- Retorna: ``void``.


## I2C

Manejo del periférico bus comunicación I2C (Inter Integrated Circuits).

**Configuración**

``bool_t i2cConfig( i2cMap_t i2cNumber, uint32_t clockRateHz );``

- Parámetro: ``i2cMap_t i2cNumber`` I2C a configurar (ver I2C Map).
- Parámetro: ``uint32_t clockRateHz`` configuración de velocidad del bus I2C.
- Retorna: ``bool_t`` TRUE si la configuración es correcta.

Posibles configuraciones de clockRateHz: 100000, etc.

**Lectura**
```c
bool_t i2cRead( i2cMap_t  i2cNumber,
                uint8_t  i2cSlaveAddress,
                uint8_t* dataToReadBuffer,
                uint16_t dataToReadBufferSize,
                bool_t   sendWriteStop,
                uint8_t* receiveDataBuffer,
                uint16_t receiveDataBufferSize,
                bool_t   sendReadStop );
```

- Parámetro: ``i2cMap_t i2cNumber`` I2C a leer (ver I2C Map).
- Parámetro: ``uint8_t i2cSlaveAddress`` Dirección del sensor conectado por I2C a leer.
- Parámetro: ``uint8_t* dataToReadBuffer`` puntero al buffer con los bytes a escribir para indicar que se debe leer.
- Parámetro: ``uint16_t dataToReadBufferSize`` tamaño del buffer con los bytes a escribir.
- Parámetro: ``bool_t sendWriteStop`` setear en 1 para enviar stop al finalizar el comando de escritura, con 0 no se envía. Algunos periféricos pueden no necesitar el stop.
- Parámetro: ``uint8_t* receiveDataBuffer`` puntero al buffer donde se almacenarán los datos leídos.
- Parámetro: ``uint16_t receiveDataBufferSize`` tamaño del buffer donde se almacenarán los datos leídos.
- Parámetro: ``bool_t sendReadStop`` setear en 1 para enviar stop al finalizar el comando de lectura, con 0 no se envía. Algunos periféricos pueden no necesitar el stop.
- Retorna: ``bool_t`` TRUE si se pudo leer correctamente.

**Escritura**

```c
bool_t i2cWrite( i2cMap_t  i2cNumber,
                 uint8_t  i2cSlaveAddress,
                 uint8_t* transmitDataBuffer,
                 uint16_t transmitDataBufferSize,
                 bool_t   sendWriteStop );
```

- Parámetro: ``i2cMap_t i2cNumber`` ID de periférico I2C a escribir (ver I2C Map). Actualmente funciona únicamente el I2C0.
- Parámetro: ``uint8_t i2cSlaveAddress`` Dirección del sensor conectado por I2C a escribir.
- Parámetro: ``uint8_t* transmitDataBuffer`` puntero al buffer donde se encuentran los datos a escribir.
- Parámetro: ``uint16_t transmitDataBufferSize`` tamaño del buffer donde se encuentran los datos a escribir.
- Parámetro: ``bool_t sendWriteStop`` setear en 1 para enviar stop al finalizar el comando de escritura, con 0 no se envía. Algunos periféricos pueden no necesitar el stop.
- Retorna: ``bool_t`` TRUE si se pudo escribir correctamente.


## SPI



## Power management

Manejo de modos de consumo del microcontrolador.

**Dormir hasta que ocurra la próxima interrupción**

``void sleepUntilNextInterrupt( void );``

- Parámetro: ninguno.
- Retorna: nada.


## Archivos que contienen estos módulos

**src** (.c):

- sapi_adc.c
- sapi_dac.c
- sapi_gpio.c
- sapi_i2c.c
- sapi_pwm.c
- sapi_rtc.c
- sapi_sct.c
- sapi_sleep.c
- sapi_timer.c
- sapi_uart.c

**inc** (.h):

- sapi_adc.h
- sapi_dac.h
- sapi_gpio.h
- sapi_i2c.h
- sapi_keypad.h
- sapi_pwm.h
- sapi_rtc.h
- sapi_sct.h
- sapi_sleep.h
- sapi_spi.h
- sapi_timer.h
- sapi_uart.h
