notas:


------------------------------------------------------------

## Suscripción a eventos de un perifércio

``// Set callback function on a peripheral event
periphSetEventCallback( PERIPHi, callbackFunction, myPtr );``


``void userCallbackFunction( void* userPtr ) {
  // User code
}``

------------------------------------------------------------


typedef struct {
    uint16_t port_id;
    uint16_t flags;
} gpio_init_t;

#define GPIO_END_CONFIG  { 0, 0 }
#define GPIO_CONFIG(...) ((const gpio_init_t[])({ __VA_ARGS__ }))

void GPIO_Config(const gpio_init_t *gpio) {

 static int is_init = 0;

 int i;

    if (!is_init)
        init_gpio(GPIO);

    for(i=0; gpio[i].flags; i++)
       config_gpio(gpio[i].por_id, gpio[i].flags);
}
void main () {
    do_noting(GPIO_CONFIG(
        { GPIO8, GPIO_IN  | GPIO_PULL_UP | GPIO_FAST },
        { GPIO7, GPIO_OUT | GPIO_PULL_UP | GPIO_OC },
        { GPIO6, GPIO_IN  | GPIO_PULL_UP | GPIO_FAST },
        { GPIO3, GPIO_OUT | GPIO_PULL_DOWN | GPIO_OC },
        GPIO_END_CONFIG
    ));

    ...
}


-----------------------------------------------------------


0b0001 - GPIO_INPUT | GPIO_NOPULL
0b0011 - GPIO_INPUT | GPIO_PULLUP
0b0101 - GPIO_INPUT | GPIO_PULLDOWN
0b0111 - GPIO_INPUT | GPIO_PULLUP | GPIO_PULLDOWN
0b0111 - GPIO_INPUT | GPIO_PULLUPDOWN






  GPIO_INPUT = (0 << 0),
  GPIO_OUTPUT = (0 << 1),
  GPIO_PUSHPULL = (0 << 1),
  GPIO_OPENCOLLECTOR = (1 << 1),
  GPIO_PULLUP = (1 << 2),
  GPIO_PULLDOWN = (1 << 3),
GPIO_DEFAULT = GPIO_PUSHPULL,



``gpioConfig( GPIOi, GPIO_DIRECTION | GPIO_MODE_FLAG1 | ...  | GPIO_MODE_FLAGn | GPIO_SPEED );``


Posibles GPIO_DIRECTION (requerido):

- GPIO_INPUT
- GPIO_OUTPUT

Posibles GPIO_MODE_FLAGs (opcional) si GPIO_DIRECTION es GPIO_INPUT:

- GPIO_NOPULL (valor por defecto si no se ingresa): sin resistencia de pull-up o pull-down.
- GPIO_PULLUP: a resistor connected to high.
- GPIO_PULLDOWN: a resistor connected to low.
- GPIO_PULLUP | GPIO_PULLDOWN: both a resistor connected to high and a resistor connected to low (only useful in rare cases).
- GPIO_PULLUPDOWN: both a resistor connected to high and a resistor connected to low (only useful in rare cases).


Posibles GPIO_MODE si GPIO_DIRECTION es GPIO_OUTPUT:

- GPIO_PUSHPULL (valor por defecto si no se ingresa): a transistor connects to high, and a transistor connects to low (only one is operated at a time). 

This is the output type that most people think of as "standard". When the output goes low, it is actively "pulled" to low. Conversely, when the output is set to high, it is actively "pushed" toward high.

- GPIO_OPENCOLLECTOR {or GPIO_OPENDRAIN}: A transistor connects to low and nothing else.
- GPIO_OPENCOLLECTOR {or GPIO_OPENDRAIN} | GPIO_PULLUP: a transistor connects to low, and a resistor connects to high.

An Open-Drain output, on the other hand, is only active in one direction. It can pull the pin towards ground, but it cannot drive it high. Imagine the previous image, but without the upper MOSFET. When it is not pulling to ground, the (lower-side) MOSFET is simply non-conductive, which causes the output to float.

For this type of output, there needs to be a pull-up resistor added to the circuit, which will cause the line to go high when not driven low. You can do this with an external part, or by setting the GPIO_PuPd value to GPIO_PuPd_UP.

The name comes from the fact that the MOSFET's drain isn't internally connected to anything. This type of output is also called "open-collector" when using a BJT instead of a MOSFET.

Posibles GPIO_SPEED (opcional):

Se puede aplicar en estos 2 casos:
- GPIO_DIRECTION es GPIO_INPUT. Controla la histéresis de entrada.
- GPIO_DIRECTION es GPIO_OUTPUT y GPIO_MODE es GPIO_PUSHPULL. En este caso controla la frecuencua máxima de cambio de la salida.

This controls the slew rate (the rise time and fall time) of the output signal. The faster the slew rate, the more noise is radiated from the circuit. It is good practice to keep the slew rate slow, and only increase it if you have a specific reason.

- GPIO_SPEED0. (valor por defecto si no se ingresa).
- GPIO_SPEED1.
- GPIO_SPEED2.
- GPIO_SPEED3.
- GPIO_SPEED4.
- GPIO_SPEED5.
- GPIO_SPEED6.
- GPIO_SPEED7.

Posibles DRIVE_STRENGTH (opcional) si GPIO_DIRECTION es GPIO_OUTPUT y GPIO_MODE es GPIO_PUSHPULL:

- GPIO_STRENGTH0 (valor por defecto si no se ingresa).
- GPIO_STRENGTH1.
- GPIO_STRENGTH2.
- GPIO_STRENGTH3.





- GPIO_NORMAL_STRENGTH (valor por defecto si no se ingresa).
- GPIO_LOW_STRENGTH.
- GPIO_MEDIUM_STRENGTH.
- GPIO_HIGH_STRENGTH.

               IN
4444 3322 1111 0000
0000 0000 0000 0000  16 bits (uint16_t)

half-byte:

0 - GPIO_INPUT and GPIO_MODE (4 valores)

0b0001 - GPIO_INPUT
0b0001 - GPIO_INPUT | GPIO_NOPULL
0b0011 - GPIO_INPUT | GPIO_PULLUP
0b0101 - GPIO_INPUT | GPIO_PULLDOWN
0b0111 - GPIO_INPUT | GPIO_PULLUP | GPIO_PULLDOWN
0b0111 - GPIO_INPUT | GPIO_PULLUPDOWN

1 - GPIO_OUTPUT and GPIO_MODE (3 val)

       str spd mode
111111
543210 987 654 3210
xFRAEL 00s 00s OPPI
 aisde   t   p p /
 lsygv   r   e eDUO
 linee   e   e nop
 inc l   n   d  w
 ngh     g     dn
 g r     h     n
000000 000 000 0000 val

0b0001 - GPIO_OUTPUT
0b0001 - GPIO_OUTPUT | GPIO_PUSHPULL
0b0010 - GPIO_OUTPUT | GPIO_OPENCOLLECTOR
0b0010 - GPIO_OUTPUT | GPIO_OPENDRAIN
0b0110 - GPIO_OUTPUT | GPIO_OPENCOLLECTOR | GPIO_PULLUP
0b0110 - GPIO_OUTPUT | GPIO_OPENDRAIN | GPIO_PULLUP


2 - GPIO_SPEED (Slew rate o histéresis), son 8 valores posibles.

3 - DRIVE_STRENGTH, son 8 valores posibles.

4 - Interrupts (GPIO events when GPIO_MODE is GPIO_INPUT)

Each GPIO pin, when configured as a general-purpose input, can be configured as an interrupt source to the ARM. Several interrupt generation sources are configurable:

Level-sensitive (high/low)

0b0001 - GPIO_LEVEL
0b0101 - GPIO_LEVEL | GPIO_LEVEL_HIGH
0b1001 - GPIO_LEVEL | GPIO_LEVEL_LOW
0b1101 - GPIO_LEVEL | GPIO_LEVEL_HIGH | GPIO_LEVEL_LOW
0b1101 - GPIO_LEVEL | GPIO_LEVEL_BOTH

Edge (Rising/falling)

0b0010 - GPIO_EDGE
0b0110 - GPIO_EDGE | GPIO_EDGE_RISING
0b1010 - GPIO_EDGE | GPIO_EDGE_FALLING
0b1110 - GPIO_EDGE | GPIO_EDGE_RISING | GPIO_EDGE_FALLING
0b1110 - GPIO_EDGE | GPIO_EDGE_BOTH

Asynchronous Edge (Rising/falling)

0b0011 - GPIO_ASYNCHRONOUS_EDGE
0b0111 - GPIO_ASYNCHRONOUS_EDGE | GPIO_EDGE_RISING
0b1011 - GPIO_ASYNCHRONOUS_EDGE | GPIO_EDGE_FALLING
0b1111 - GPIO_ASYNCHRONOUS_EDGE | GPIO_EDGE_RISING | GPIO_EDGE_FALLING
0b1111 - GPIO_ASYNCHRONOUS_EDGE | GPIO_EDGE_BOTH


``gpioSetEventCallback( GPIOi, GPIO_EDGE | GPIO_EDGE_RISING, callbackFunction, myPtr );``

``// Set callback function on a peripheral event
periphSetEventCallback( PERIPHi, callbackFunction, myPtr );``


``void userCallbackFunction( void* userPtr ) {
  // User code
}``


2 bits (4 valores)
00
01
10
11

3 bits (8 valores)
000
001
010
011
100
101
110
111

4 bits (16 valores)
0000
0001
0010
0011
0100
0101
0110
0111
1000
1001
1010
1011
1100
1101
1110
1111



--------------------------------------------------------------


open drain push pull

    The push-pull output actually uses two transistors. Each will be on to drive the output to the appropriate level: the top transistor will be on when the output has to be driven high and the bottom transistor will turn on when the output has to go low.

    The open-drain output lacks the top transistor. When the output has to go high you simply turn off the bottom transistor, but the line is now pulled high only by the pullup resistor.

    Your micro allows you to select between the two types, which means that by setting some bits in some register you actually enable/ disable the top transistor and enable/disable the pullup (if internal, otherwise you just disable the top transistor and have to use an external pullup)

    The advantage of the push-pull output is the higher speed, because the line is driven both ways. With the pullup the line can only rise as fast as the RC time constant allows. The R is the pullup, the C is the parasitic capacitance, including the pin capacitance and the board capacitance.
    The push-pull can typically source more current. With the open-drain the current is limited by the R and R cannot be made very small, because the lower transistor has to sink that current when the output is low; that means higher power consumption.

    However, the open-drain allows you to cshort several outputs together, with a common pullup. This is called an wired-OR connection. Now you can drive the output low with any of the IO pins. To drive it high all ouputs have to be high. This is advantageous in some situations, because it eliminates the external gates that would otherwise be required.


--------------------------------------------------------------


tickConfig( TICK_MS(1) ); o tickStart( TICK_MS(1) );
tickEnabeling( ENABLE );
tickSetCallback( function );

typedef tick_t uint64_t;

#define TICK_MS(t) ((typedef)(t))
#define TICK_S(t)  (((typedef)(t))*1000)

¿Porque alguien que solo quiere usar el Systick para medir intervalos tendria que tener en cuenta el callback?

--------------------------------------------------------------

UART_9600_8N1      UART_BAUDRATE(9600)
UART_57600_8N1     UART_BAUDRATE(57600)
UART_115200_8N1    UART_BAUDRATE(115200)

UART_PARITY_NONE   0
UART_PARITY_ODD    1
UART_PARITY_EVEN   2

--------------------------------------------------------------
string_t, La idea sería:

Pensando en "voz alta" para no usar memoria dinámica podríamos definirlo como una estructura que tenga un puntero al comienzo del vector con el texto y su cantidad de caracteres:

- String: string_t

typedef struct{
   char * strPtr;
   uint32_t strLen;
} string_t;

Entonces el uso sería:

string_t mensaje = newString();
msgArray"hola";

stringInitialize( mensaje )

--------------------------------------------------------------


// FUNCTION POINTER VECTOR EXAMPLE

// Función para no tener NULL pointer
   void dummy(void){
   }

// Definición de un tipo con typedef.
   typedef void (*voidFunctionPointer_t)(void);

// Definición de una variable con el tipo de typedef, incializo en dummy (NULL)
   voidFunctionPointer_t voidFunctionPointer[2] = {dummy, dummy};

// Ejecuto la funcion
   (* voidFunctionPointer[0] )();
   (* voidFunctionPointer[1] )();

// Asigno una funcion a cada posición del vector
   voidFunctionPointer[0] = ledB;
   voidFunctionPointer[1] = led1;



--------------------------------------------------------------


## Archivos que componen la biblioteca

**ACTUALIZAR:**

**src** (.c):

- sapi_7_segment_display.c
- sapi_adc.c
- sapi_board.c
- sapi_dac.c
- sapi_datatypes.c
- sapi_delay.c
- sapi_gpio.c
- sapi_hmc5883l.c
- sapi_i2c.c
- sapi_isr_vector.c
- sapi_keypad.c
- sapi_pwm.c
- sapi_rtc.c
- sapi_sct.c
- sapi_servo.c
- sapi_sleep.c
- sapi_spi.c
- sapi_tick.c
- sapi_timer.c
- sapi_uart.c

**inc** (.h):

- sapi_7_segment_display.h
- sapi_adc.h
- sapi_board.h
- sapi_dac.h
- sapi_datatypes.h
- sapi_delay.h
- sapi_gpio.h
- sapi_hmc5883l.h
- sapi_i2c.h
- sapi_isr_vector.h
- sapi_keypad.h
- sapi_peripheral_map.h
- sapi_pwm.h
- sapi_rtc.h
- sapi_sct.h
- sapi_servo.h
- sapi_sleep.h
- sapi_spi.h
- sapi_tick.h
- sapi_timer.h
- sapi_uart.h
- sapi.h


