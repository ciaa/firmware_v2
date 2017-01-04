# Principios de diseño de la biblioteca sAPI

El modelo de la biblioteca se compone de las siguientes capas:

- **Board:** Contiene las definiciones de conectores (pines, borneras, otros conectores) y la asociación con cada IPCore (cada IPCore ocupa uno o más conectores).
- **SoC**: Conjunto de IPCores.
- **IPCore:** IPCore genérico dentro de un SoC. Por ejemplo todos los periféricos.

## IPCore

Se basa en definir IPCores abstractos lo más genéricos posibles, logrando independencia de la arquitectura. Esta independecia es deseada para que actúe como HAL (Hardware Abstraction Layer).

Los periféricos básicos a modelar seran:

- GPIO0 a GPIOn.
- UART0 a UARTn.
- ADC0_CH0 a ADCn_CHm.
- DAC0 a DACn.
- TIMER0 a TIMERn.
- I2C0 a I2Cn.
- SPI0 a SPIn.

Cada uno de los IPCores tendrá un conjunto de "propiedades". 

Estas propiedades se agrupan en una estructura asociada al periférico. La estructura es el área donde se encuentra mapeado el IPCore y no es accesible desde el API pública más alla de como un indice con nombre (I2C0=0, SPI1=1, UART4=3, etc.).

Se diferencian dos tipos de IPCores:

- **IPCore con existencia física en el SoC a modelar:** No son "creables" sino "iniciables", además, tienen definidos nombres prefijados que no podemos destruir o crear dos veces. Es decir, no podemos tener 10 SPI apuntando al mismo elemento fisico, SPI0; es SPI0 desde que el software arranca hasta que termina o se destrulle el chip.
- **IPCore virtual:** En cuanto a los periféricos "virtuales" como un chip conectado al I2C o al SPI, se les deben asignar estructuras específicas porque no existen hasta que se "crean" e "inician" (análogo al new de C++).

De esta manera, para GPIO, I2C, SPI, UART, o cualquier otro periférico físico, basta con que el nombre asignado por el CORE/BSP, para uno virtual, hay que crear su espacio en memoria ( por ejemplo, con una estructura ``eepromi2c_t eeprom1;``), luego inicializarlo y finalmente usarlo.

### API pública de acceso a IPCores

- Inicializar el IPCore (enciende el IPCore de ser necesario y lo inicializa con la configuración más típica utilizada): ``<ipCore>Initialize( <IPCOREi>, <mostCommonPropertyValue> | <MODIFY_FLAG1> | ... | <MODIFY_FLAGn> );``

- Asignar valor de una propiedad: ``<ipCore>Set<PropertyName>( <IPCOREi>, <propertyValue> | <MODIFY_FLAG1> | ... | <MODIFY_FLAGn> );``

- Obtener valor de una propiedad: ``<propertyValue> = <ipCore>Get<PropertyName>( <IPCOREi> );``

- Ejemplo de cambio de una propiedad teniendo en cuenta el valor previo:``<ipCore>Set<PropertyName>( <IPCOREi>, <ipCore>Get<PropertyName>( <IPCOREi> ) | <MODIFY_FLAG> );``

- Propiedades más comunes que encontraremos en un periférico:
   - configParamName: Un valor de configuración del periférico.
   - power: Para encender o apagar el IPCore.
   - value: Un valor a leer o escribir.
   - eventName: Un evento asociado al periférico (interrupción u otro).
   - eventNameCallback: Una estructura con el puentero a función y el puntero al parámetro que le pueda pasar el usuario a dicha función. (interrupción u otro).


### Modelo de GPIO

GPIO modela un único pin de entrada/salida de porpósito general.

#### Propiedades de GPIO

- Propiedades de configuración:
    - ``mode`` *(o direction? que les gusta más?)*
    - ``speed``
    - ``power``
- Propiedades de valor:
    - ``value``
- Propiedades de eventos:
    - ``event``
    - ``eventCallback``

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
        - ``GPIO_PUSHPULL | GPIO_STRENGTH<i>`` (i=0...7)
        - ``GPIO_OPENCOLLECTOR`` ( es equivalente también ``GPIO_OPENDRAIN``)
        - ``GPIO_OPENCOLLECTOR | GPIO_PULLUP``
- speed: ``GPIO_SPEED<i>`` (i=0...7)

- power: ``ON``, ``OFF``, ``ENABLE`` o ``DISABLE``

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


#### Métodos de GPIO

Getters y Setters de todas sus propiedades, por ejemplo:

- ``gpioSetMode( GPIO<i>, GPIO_INPUT | GPIO_PULLUP );``
- ``gpioMode = gpioGetMode( GPIO<i> );``

- ``gpioSetValue( GPIO<i>, value );``
- ``gpioValue = gpioGetValue( GPIO<i> );``

Alias de los anteriores:

- ``gpioRead();`` alias de ``gpioGetValue();``
- ``gpioWrite();`` alias de ``gpioSetValue();``
- ``gpioConfig();`` alias de ``gpioSetMode();``


### Modelo de UART

UART modela un transmisor/receptor asincrónico universal (coumnmente llamado *puerto serie*).

#### Propiedades de UART

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


#### Métodos de UART

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



