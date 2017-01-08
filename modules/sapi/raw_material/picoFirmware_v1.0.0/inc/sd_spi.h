/* Copyright 2016, Pablo Ridolfi
 * Copyright 2016, VICDA Argentina
 * All rights reserved.
 *
 * This file is part of picoAPI.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef _SD_SPI_H_
#define _SD_SPI_H_

/** @addtogroup SDCard
 *  Access to SD cards using SPI0
 *
 *  Connect the picoCIAA to the SDCard as follows:
 *  | picoCIAA | Signal     | SDCard     |
 *  | -------- | ---------- | ---------- |
 *  | P6_11    | SPI0_MOSI  | 2 CMD/DI   |
 *  | P6_12    | SPI0_SCK   | 5 CLK/SCK  |
 *  | P6_13    | SPI0_SSEL0 | 1 DAT3/nCS |
 *  | P6_14    | SPI0_MISO  | 7 DAT0/DO  |
 *
 *  @warning SD interface uses SPI0, do not use SD API and SPI API with SPI0
 *  at the same time!
 *
 *  @{
 */

/*==================[inclusions]=============================================*/

#include "pin.h"

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/

/** file pointer */
typedef void * picoFile;

/** file access types */
typedef enum picoFileAccess {
	picoFILE_READ,   /**< open file for reading */
	picoFILE_WRITE,  /**< open file for writing */
	picoFILE_APPEND  /**< open file for appending */
}picoFileAccess;

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/** init SPI interface to SD card.
 *
 * @return 0 in case of successful initialization, -1 if error
 */
int32_t picoSDInit(void);

/** write data to file, open before and close after operation
 *
 * @param filename name of the file
 * @param data     data to be written
 * @param datalen  length of the data in bytes
 * @return number of bytes written
 */
uint32_t picoSDWriteAll(char * filename, void * data, uint32_t datalen);

/** read data from file, open before and close after operation
 *
 * @param filename name of the file
 * @param data     data to be read
 * @param datalen  length of the data buffer in bytes
 * @return number of bytes read
 */
uint32_t picoSDReadAll(char * filename, void * data, uint32_t datalen);

/** append data to file, open before and close after operation
 *
 * @param filename name of the file
 * @param data     data to append
 * @param datalen  length of the data in bytes
 * @return number of bytes appended
 */
uint32_t picoSDAppendAll(char * filename, void * data, uint32_t datalen);

/** open file for read and write operations
 *
 * @param filename name of the file
 * @param fileAccess @ref picoFileAccess access type (READ, WRITE or APPEND)
 * @return a file pointer @ref picoFile, or NULL on error
 */
picoFile picoSDOpen(char * filename, picoFileAccess fileAccess);

/** close access to file
 *
 * @param file @ref picoFile given by @ref picoSDOpen
 */
void picoSDClose(picoFile file);

/** read data from previously open file
 *
 * @param file @ref picoFile given by @ref picoSDOpen
 * @param data buffer to store data
 * @param len  length of the buffer in bytes
 * @return number of bytes read, or 0 on error
 */
uint32_t picoSDRead(picoFile file, void * data, uint32_t len);

/** write data to previously open file
 *
 * @param file @ref picoFile given by @ref picoSDOpen
 * @param data data to be written
 * @param len length of the data in bytes
 * @return number of bytes written, or 0 on error
 */
uint32_t picoSDWrite(picoFile file, void * data, uint32_t len);

/** write null-terminated string to previously open file
 *
 * @param file @ref picoFile given by @ref picoSDOpen
 * @param string null-terminated string to write
 * @return number of chars written, or 0 on error
 */
uint32_t picoSDPrint(picoFile file, char * string);

/** check end of file
 *
 * @param f @ref picoFile given by @ref picoSDOpen
 * @return true (!= 0) if end of file reached, false (== 0) otherwise
 */
int32_t picoSDEndOfFile(picoFile f);

/*==================[cplusplus]==============================================*/

/** @} */

#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/
#endif /* _SD_SPI_H_ */
