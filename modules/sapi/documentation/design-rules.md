# Principios de diseño

Se basa en definir periféricos abstractos y lo más genéricos posibles, logrando
independencia de la arquitectura. Esta independecia es deseada para que actúe
como HAL (Hardware Abstraction Layer).

Se diseña además una API sencilla en la que la mayoría de las funciones son
del tipo:

- nombreModuloConfig();
- nombreModuloRead();
- nombreModuloWrite();

Utiliza nombres sencillos al estilo de la biblioteca *Wiring*, pero en lugar del
concepto de *pin* utiliza el concepto *periférico*, para lograr una API
unificada, sin importar el número de pines que tenga un cierto perifécico.

En moduloConfig() que reciba parámetros con OR entre cada uno (VER SI ES APLICABLE EN TODOS).

Los periféricos de una placa se llamarán:

- GPIO0 a GPIOn.
- ADC0_CH0 a ADCn_CHm.
- UART0 a UARTn.

Pero también se podrán usar los nombres de la serigrafía de la placa como un alias.


