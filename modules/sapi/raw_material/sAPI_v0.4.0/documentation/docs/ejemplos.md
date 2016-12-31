# Ejemplos

## EDU-CIAA-NXP

### GPIO

**sapi_gpio_01_switches_leds**

Ejemplo de utilización de GPIO. Este ejemplo enciende un led con cada tecla
de la EDU-CIAA-NXP.

**sapi_gpio_02_blinky**

Ejemplo de utilización de GPIO, Tick y Delay. Este ejemplo hace titilar un
led (blink) de la EDU-CIAA-NXP utilizando un retardo bloqueante (función ``delay()``). Un retardo bloqueante no permite que se ejecuten otras tareas
mientras se está ejecutando.

**sapi_gpio_03_blinky_switch**

Ejemplo de utilización de GPIO, Tick y Delay. Este ejemplo hace titilar un
led (blink) de la EDU-CIAA-NXP utilizando un retardo NO bloqueante (funciónes
``delayConfig()``, ``delayRead()``). Esto permite
manejar otro led con la TEC4 al mismo tiempo que parpadea.

**sapi_gpio_04_led_sequences**

Ejemplo de utilización de GPIO, Tick y Delay. Con TEC1 y TEC 4 maneja la
dirección de movimiento de los leds (secuencia de leds a izquierda o derecha),
mientras que con TEC2 y TEC4 cabia la velocidad de movimiento de lenta a rápida
en la EDU-CIAA-NXP. Utiliza retardo no bloqueante (funciónes ``delayConfig()``,
``delayRead()``) y cambia su valor en ejecución (función ``delayWrite()``).

**sapi_gpio_05_keypad_7segment**

Ejemplo de utilización de Display 7 segmentos y Teclado matricial.


### Tick

**sapi_tick_01_tickHook**

Ejemplo de utilización de GPIO y Tick. Este ejemplo utiliza una función
que se ejecuta cada vez que ocurre un tick para cambiar el valor del LED azul
de la EDU-CIAA-NXP. Confgura la tasa de ticks a 1 tick cada 50ms (velocidad más
lenta soportada).


### UART

**sapi_uart_01_echo**

Ejemplo de utilización de UART. Al iniciar envía varios caracteres y Strings y
luego realiza el eco de todo lo que recibe enviándolo nuevamente por la
UART_USB.

**sapi_uart_02_receive_string_blocking**

**sapi_uart_03_receive_string**

**sapi_uart_04_bridge_esp8266**


### ADC y DAC

**sapi_adc_dac_01**

Ejemplo de utilización de ADC y DAC. También utiliza GPIO, Tick, Delay y
UART. Utiliza dos retardos NO bloqueantes para realizar dos tareas periódicas
sin interferencias. La primera lee el ADC CH1 (AI0), escribe el valor en el DAC
(AO) y envía el dato por la UART_USB. La segunda hace titilar el LED1 10 veces
rápidamente y después cambia el valor del retardo para que titile lentamente.


### ADC y DAC

**sapi_rtc_01**

Ejemplo de utilización de RTC. Además utiliza Delay y UART. Establece la fecha
y hora del reloj de tiempo real y la muestra por UART_USB.


### PWM

**sapi_pwm_01**

Ejemplo de utilización de PWM. Con GPIO y Delay. Muestra 3 saidas PWM sobre
los leds 1, 2 y 3.

### Servomotor angular

**sapi_servo_01**

Ejemplo de utilización de Servomotor angular (0 a 180°) y Delay. El servo
utilizado es el SG90 y va conectado en 5V (cable rojo), GND (cable marrón) y
señal al pin SERVO0 (T_F1 con cable naranja).


### I2C

**sapi_i2c_01_hmc5883l**

Ejemplo de utilización de sensor Magnetómetro (compass) HMC5883L, I2C, Delay y
UART. Este sensor se conecta a la EDU-CIAA-NXP mediante I2C (I2C0) para leer los
valores de campo magnético en (x,y,z) y los muestra por UART.


### SPI

**sapi_spi_01_sdcard_fatfilesystem**


### USB Device



### USB Host

**sapi_usb_host_01_mass_storage_fatfilesystem**


### Sistemas Operativos

**sapi_os_01_seos**

SEOS del ingés Simple Embedded Operating System. 
Ejemplo de Planificador de tareas cooperativo disparado por tiempo 
(Time-Triggered), con el planificador (scheduler) y despachador de tareas 
(dispatcher) todo junto que se ejecuta en una Interrupción periódica de tiempo.
Solamente la primer tarea es Real-Time. La suma de la duración de todas las 
tareas debe ser menor a 1 Tick (1ms en el ejemplo), si alguna se excede un 
poco de tiempo el sistema va a fallar, ya que se perderá temporización.
Las tareas deben ser NO bloqueantes.

**sapi_os_02_seos_bakground_foreground**

SEOS del ingés Simple Embedded Operating System. 
Ejemplo de Planificador de tareas cooperativo disparado por tiempo 
(Time-Triggered). Variante background-foreground. El despachador de tareas 
(dispatcher) en el while(1) (background) y planificador de tareas 
(scheduler) se ejecuta en una Interrupción periódica de tiempo (foreground).
Solamente la primer tarea es Real-Time. La suma de la duración de todas las 
tareas debe ser menor a 1 Tick (1ms en el ejemplo), si alguna se excede un 
poco de tiempo el sistema puede recuperarse, es decir, no pierde 
temporización pero sin embargo se atrasa un poco en la ejecución.
Las tareas deben ser NO bloqueantes.

**sapi_os_03_pont_sch**

Ejemplo de Sistema Operativo Cooperativo Simple de M. J. Pont. En este RTOS 
todas las tareas pueden ser Real-Time si se planifican utilizando offsets 
adecuados y además tienen un comportamiento cooperativo (las tareas deben 
ser NO bloqueantes, la duración de cada tarea menor a 1 Tick si se aplican 
offsets).

Este planificador cooperativo contiene:

 - Estructura de datos del planificador. Contiene información de planificación y ejecución de cada tarea: ``sTask``
 - Función de inicialización del planificador: ``SCH_Init();``
 - Una única RTI que actualice el planificador periódicamente: ``SCH_Update();``
 - Una función de despacho de tareas que arranque la tarea que corresponda ejecutar: ``SCH_Dispatch_Tasks();``
 - Una función para agregar tareas al planificador ``SCH_Add_Task(Task_Name, Delay, Period );``
 - Una función para remover tareas del planificador (si fuese necesario): ``SCH_Delete_Task(char TASK_INDEX);``

