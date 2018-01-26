# Firmware v2
Firmware v2 is a C language software development environment for embedded
systems. At the moment it focuses specifically on the programming of 
microcontrollers.

## IMPORTANT

**This environment is under construction!!**

**Always use the [released versions](../../releases) because in these all examples are tested and the API documentation is consistent. The master branch may contain inconsistencies because this environment is currently under development.**

## Supported targets
- LPC11U68
- LPC1769
- LPC4337 (M4 and M0 cores)
- LPC54102 (M4 and M0+ cores)

## Supported boards
- CIAA-NXP and EDU-CIAA-NXP (www.proyecto-ciaa.com.ar)
- LPCXpresso with LPC1769
- LPCXpresso with LPC54102
- LPCXpresso with LPC11U68

## Available libraries
- [sAPI](https://github.com/epernia/sapi) (only for EDU-CIAA-NXP board).
- [CMSIS](http://www.arm.com/products/processors/cortex-m/cortex-microcontroller-software-interface-standard.php). and [LPCOpen](https://www.lpcware.com/lpcopen).
- [CMSIS-DSPLIB](http://www.keil.com/pack/doc/CMSIS/DSP/html/index.html).
- [lwip](http://lwip.wikia.com/wiki/LwIP_Wiki).
- [FreeRTOS](http://www.freertos.org/).

## Supported toolchains
- gcc-arm-none-eabi

## Usage
* Make sure you have an ```arm-none-eabi-*``` toolchain configured in your ```PATH```. If you don't have it, download [GCC ARM Embedded](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm).
* ```git clone https://github.com/pridolfi/workspace.git && cd workspace```
* ```cp project.mk.template project.mk```
* Define ```PROJECT```, ```TARGET``` and ```BOARD``` (optional) variables in ```project.mk``` according to the project you want to compile.
* Compile with ```make```.
* Clean with ```make clean```. Clean for all targets with ```make clean_all```.
* Download to target via OpenOCD with ```make download```.

## This environment is based on

- **Workspace** by Pablo Ridolfi: <https://github.com/pridolfi/workspace>
- **sAPI** by Eric pernia: <https://github.com/epernia/sapi>

