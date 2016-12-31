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

## Capas de software

![Imagen "sapi-modulos-capas.png" no encontrada](assets/img/sapi-modulos-capas.png "Módulos y capas de la biblioteca sAPI")
