//*****************************************************************************
//   +--+
//   | ++----+
//   +-++    |
//     |     |
//   +-+--+  |
//   | +--+--+
//   +----+    Copyright (c) 2013 Code Red Technologies Ltd.
//
//
// Header file for defining Macros to create MTB Buffer within application
//
// Only for use with Cortex-M0+ parts which support the MTB
//
// Usage:
//     __CR_MTB_BUFFER(512)
//       allocates a buffer of 512 bytes in the default ram memory region
//
//    __CR_MTB_BUFFER_EXT(1024,RAM2)
//       allocates a buffer of 1024 bytes in the 2nd (RAM2) ram memory region
//
//*****************************************************************************

#ifndef CR_MTB_BUFFER_H_
#define CR_MTB_BUFFER_H_

#include "cr_section_macros.h"

#define __CR_MTB_BUFFER_EXT(size,bank) \
__SECTION(mtb, bank) \
    __attribute__((aligned(size))) \
        char __mtb_buffer__[size]

#define __CR_MTB_BUFFER(size) __CR_MTB_BUFFER_EXT(size,RAM1)

#endif /* CR_MTB_BUFFER_H_ */
