//*****************************************************************************
// cr_section_macros.h
//
// Set of macros to allow code/data to be placed into alternate memory banks
//*****************************************************************************
//
// Copyright(C) NXP Semiconductors, 2014
// All rights reserved.
//
// Software that is described herein is for illustrative purposes only
// which provides customers with programming information regarding the
// LPC products.  This software is supplied "AS IS" without any warranties of
// any kind, and NXP Semiconductors and its licensor disclaim any and
// all warranties, express or implied, including all implied warranties of
// merchantability, fitness for a particular purpose and non-infringement of
// intellectual property rights.  NXP Semiconductors assumes no responsibility
// or liability for the use of the software, conveys no license or rights under any
// patent, copyright, mask work right, or any other intellectual property rights in
// or to any products. NXP Semiconductors reserves the right to make changes
// in the software without notification. NXP Semiconductors also makes no
// representation or warranty that such application will be suitable for the
// specified use without further testing or modification.
//
// Permission to use, copy, modify, and distribute this software and its
// documentation is hereby granted, under NXP Semiconductors' and its
// licensor's relevant copyrights in the software, without fee, provided that it
// is used in conjunction with NXP Semiconductors microcontrollers.  This
// copyright, permission, and disclaimer notice must appear in all copies of
// this code.
//*****************************************************************************
#ifndef CR_SECTION_MACROS_H_INCLUDED
#define CR_SECTION_MACROS_H_INCLUDED

// A macro for placing text (code), data, or bss into a named RAM section
// These will be automatically placed into the named section by the linker.
//
// RAM banks are numbered starting from 1. The actual configuration is
// dependent on the selected MCU type.
//
// Example:
//        __SECTION(data,RAM1) char buffer[1024] ;
//
// This will place the 1024 byte buffer into the RAM1
//
#define __SECTION_EXT(type, bank, name) __attribute__ ((section("." #type ".$" #bank "." #name)))
#define __SECTION(type, bank) __attribute__ ((section("." #type ".$" #bank)))
#define __SECTION_SIMPLE(type) __attribute__ ((section("." #type)))

#define __DATA_EXT(bank, name) __SECTION_EXT(data, bank, name)
#define __DATA(bank) __SECTION(data, bank)

#define __BSS_EXT(bank, name) __SECTION_EXT(bss, bank, name)
#define __BSS(bank) __SECTION(bss, bank)

// Macros for placing text (code), data, or bss into a section that is automatically
// placed after the vectors in the target image.
#define __AFTER_VECTORS_EXT(name) __attribute__ ((section(".after_vectors.$" #name)))
#define __AFTER_VECTORS __attribute__ ((section(".after_vectors")))

// Macros for causing functions to be relocated to RAM
#define __RAM_FUNC_EXT(name) __attribute__ ((section(".ramfunc.$" #name)))
#define __RAM_FUNC __attribute__ ((section(".ramfunc")))

// Macros to be used in preference to __RAM_FUNC to better match __DATA behaviour
#define __RAMFUNC_EXT(bank, name) __SECTION_EXT(ramfunc, bank, name)
#define __RAMFUNC(bank) __SECTION(ramfunc, bank)

// Macros for placing data or bss into a section that has the NOLOAD option set in the linker script
#define __NOINIT_DEF __SECTION_SIMPLE(noinit)
#define __NOINIT_EXT(bank, name) __SECTION_EXT(noinit, bank, name)
#define __NOINIT(bank) __SECTION(noinit, bank)

// Macros for placing text (code), or rodata into a different (flash) bank
#define __RODATA_EXT(bank,name) __SECTION_EXT(rodata, bank, name)
#define __RODATA(bank) __SECTION(rodata, bank)

#define __TEXT_EXT(bank,name) __SECTION_EXT(text, bank, name)
#define __TEXT(bank) __SECTION(text, bank)

#endif /* CR_SECTION_MACROS_H_INCLUDED */
