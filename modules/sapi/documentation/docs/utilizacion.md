# Utilización de la biblioteca

## EDU-CIAA-NXP

Para usar la biblioteca bajar la release actual desde github:

[https://github.com/epernia/sAPI](https://github.com/epernia/sAPI)

y copiar la carpeta sapi_bm en **Firmware/modules**.

Luego copiar el proyecto bare_metal de **Firmware/examples** y renombrarlo, por
ejemplo, **miProyectoConSapi** y modificar el Makefile del mismo dentro de la
carpeta **mak** cambiando la última linea de:

``MODS += externals$(DS)drivers``

por:

``MODS += modules$(DS)sapi_bm``

Para usarla en el programa incluir

``#include "sapi.h"``

en el archivo .c donde se requiera.

Ya no es necesario incluir **chip.h** ya que la propia biblioteca sAPI lo
incluye.

La sAPI también maneja el vector de interrupción, es por esto que es necesario
eliminar el archivo **vector.c** que trae el ejemplo **bare_metal**.
