# picoFirmware release 1.0.0
Septiembre 2016

### Referencia rápida de picoAPI

#### Ejemplos

| Ejemplo          | Descripción                                                          |
| ---------------- | -------------------------------------------------------------------- |
| `picoblinky`     | Destella un LED.                                                     |
| `picoanalog`     | Lee dos entradas analógicas y muestra sus valores.                   |
| `picoecholed`    | Eco por la interface de Debug junto con destello del LED RGB.        |
| `picosd`         | Escribe, lee y agrega (append) datos a un archivo en una tarjeta SD. |
| `picosd2`        | Similar a `picosd` pero usa la API clásica open-write-read-close.    |
| `picoprint`      | Muestra diferentes formatos de impresión por la interface de Debug.  |
| `picopwm`        | Configura dos salidas PWM con diferente ciclo de actividad.          |
| `picospi`        | Uso de SPI: comunicación con un chip CC1101.                         |
| `picoi2c`        | Uso de I2C: comunicación con un chip Si5351.                         |
| `picopingpong`   | Envío y recepción de paquetes usando el transceiver [CC1101](www.ti.com/product/CC1101).|

#### Funciones frecuentes

##### Entrada/Salida Digital

| Función                       | Descripción                          |
| ----------------------------- | ------------------------------------ |
| `picoConfigDigitalInput  `    | Configurar pin como entrada digital. |
| `picoConfigDigitalOutput `    | Configurar pin como salida digital.  |
| `picoDigitalRead         `    | Leer estado de un pin.               |
| `picoDigitalWrite        `    | Escribir estado de un pin.           |
| `picoDigitalToggle       `    | Conmutar estado de un pin.           |

Vea más en [DigitalIO](doc/group__DigitalIO.html).

### Temporización

| Función                       | Descripción                             |
| ----------------------------- | --------------------------------------- |
|    `pausems`                  | Detener programa en milisegundos.       |
|    `pauseus`                  | Detener programa en microsegundos.      |

Vea más en [Timing](doc/group__Timing.html).

### Modulación por ancho de pulso (PWM)

| Función       | Descripción                                                   |
| ------------- | ------------------------------------------------------------- |
| `picoPWMInit` | Inicializar PWM con una frecuencia definida.                  |
| `picoPWMSet ` | Configurar pin como PWM con un determinado ciclo de actividad.|

Vea más en [PWM](doc/group__PWM.html).

### Entrada Analógica

| Función                 | Descripción                            |
| ----------------------- | -------------------------------------- |
| `picoConfigAnalogInput` | Configurar pin como entrada analógica. |
| `picoAnalogRead       ` | Leer entrada analógica.                |

Vea más en [Analog-to-Digital](doc/group__Analog-to-Digital.html).

### Interface de Debug

Al conectase a una PC, la picoCIAA usa un dispositivo CDC (puerto serie virtual)
como interface de Debug. Dicho puerto enumera como `COMn` en sistemas Windows y `/dev/ttyACMn` en sistemas Linux. La interface de Debug puede ser accedida con cualquier terminal de puerto serie como [PuTTY](http://www.putty.org/), HyperTerminal, `minicom`, `GtkTerm`, etc.

| Función        | Descripción                                              |
| -------------- | -------------------------------------------------------- |
| `debugSend   ` | Enviar datos binarios.                                   |
| `debugRecv   ` | Recibir datos binarios.                                  |
| `printString ` | Enviar string terminada en `'\0'`.                       |
| `printInteger` | Convertir entero a string decimal y enviar.              |
| `printHex    ` | Convertir entero a string hexadecimal y enviar.          |

Vea más en [SerialCom](doc/group__SerialCom.html).

### UART

| Función        | Descripción                                              |
| -------------- | -------------------------------------------------------- |
| `picoUARTInit` | Inicializar UART en los pines provistos (Tx y Rx).       |
| `picoUARTSend` | Enviar datos binarios.                                   |
| `picoUARTRecv` | Recibir datos binarios.                                  |

Vea más en [SerialCom](doc/group__SerialCom.html).

### SPI

| Función           | Descripción                           |
| ----------------- | ------------------------------------- |
| `picoSPIInit    ` | Inicializar puerto SPI.               |
| `picoSPITransfer` | Enviar y recibir datos (full-duplex). |

Vea más en [SPI](doc/group__SPI.html).

### I2C

| Función           | Descripción                           |
| ----------------- | ------------------------------------- |
| `picoI2CInit    ` | Inicializar puerto I2C.               |
| `picoI2CTransfer` | Enviar y recibir datos (half-duplex). |

Vea más en [I2C](doc/group__I2C.html).

### Interface para tarjeta SD

Conectar la picoCIAA a la tarjeta SD de la siguiente manera:

| picoCIAA | Señal        | Pin SD       |
| -------- | ------------ | ------------ |
| `P6_11`  | `SPI0_MOSI`  | 2 `CMD/DI`   |
| `P6_12`  | `SPI0_SCK`   | 5 `CLK/SCK`  |
| `P6_13`  | `SPI0_SSEL0` | 1 `DAT3/nCS` |
| `P6_14`  | `SPI0_MISO`  | 7 `DAT0/DO`  |

Funciones:

| Función           | Descripción                                        |
| ----------------- | -------------------------------------------------- |
| `picoSDInit     ` | Inicializar interfaz SPI para tarjeta SD.          |
| `picoSDWriteAll ` | Abrir, escribir datos binarios y cerrar archivo.   |
| `picoSDReadAll  ` | Abrir, leer datos binarios y cerrar archivo.       |
| `picoSDAppendAll` | Abrir, agregar datos binarios y cerrar archivo.    |
| `picoSDOpen     ` | Abrir archivo para lectura y/o escritura.          |
| `picoSDClose    ` | Cerrar archivo.                                    |
| `picoSDRead     ` | Leer datos de un archivo.                          |
| `picoSDWrite    ` | Escribir datos a un archivo.                       |
| `picoSDPrint    ` | Escribir string terminada en `'\0'` en un archivo. |
| `picoSDEndOfFile` | Preguntar si se alcanzó el fin del archivo.        |

Vea más en [SDCard](doc/group__SDCard.html).

### Referencias

- [LPCOpen](www.nxp.com/lpcopen)

### Licencia

MIT License

Copyright (c) 2016, Pablo Ridolfi <br />
Copyright (c) 2016, VICDA Argentina <br />
All rights reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
