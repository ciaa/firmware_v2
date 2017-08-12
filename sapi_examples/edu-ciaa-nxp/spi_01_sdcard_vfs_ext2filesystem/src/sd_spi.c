/* Copyright 2014, ChaN
 * Copyright 2016, Matias Marando
 * Copyright 2016, Eric Pernia
 * All rights reserved.
 *
 * This file is part of Workspace.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/*==================[inlcusiones]============================================*/

#include "sd_spi.h"   // <= su propio archivo de cabecera
#include "sapi_spi.h"
#include "sapi.h"     // <= Biblioteca sAPI
#include "ff.h"       // <= Biblioteca FAT FS

#include <string.h>    /* <= string header */
#include "test_fs.h"  /* <= own header */
#include "ext2.h"
#include "ooc.h"
#include "device.h"
#include "mmcSPI.h"

/*==================[definiciones y macros]==================================*/

#define TEST_BUFFER_SIZE 1024

/*==================[definiciones de datos internos]=========================*/
/* buffer to store 10 blocks of the block device */
uint8_t buffer[TEST_BUFFER_SIZE];

/*==================[definiciones de datos externos]=========================*/

/** \brief Filesystem drivers declaration
 *
 * Here are the drivers defined in the lower layer file system implementations (in ext2.c, fat.c, etc.)
 *
 */
extern filesystem_driver_t ext2_driver;

/*==================[declaraciones de funciones internas]====================*/

static void test_fill_buffer(uint8_t *buffer, uint16_t size);
static int test_check_buffer(uint8_t *buffer, uint16_t size);
void task(void);

/*==================[declaraciones de funciones externas]====================*/

// FUNCION que se ejecuta cada vezque ocurre un Tick
bool_t diskTickHook( void *ptr );


/*==================[funcion principal]======================================*/

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void ){

   // ---------- CONFIGURACIONES ------------------------------
   // Inicializar y configurar la plataforma
   boardConfig();

   // SPI configuration
   spiConfig( SPI0 );

   // Inicializar el conteo de Ticks con resolución de 10ms,
   // con tickHook diskTickHook
   tickConfig( 10, diskTickHook );

   // ------ PROGRAMA QUE ESCRIBE EN LA SD -------

   task();
   gpioWrite( LEDG, ON );

   // ---------- REPETIR POR SIEMPRE --------------------------
   while( TRUE )
   {
      sleepUntilNextInterrupt();
   }

   // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
   // directamenteno sobre un microcontroladore y no es llamado/ por ningun
   // Sistema Operativo, como en el caso de un programa para PC.
   return 0;
}

/*==================[definiciones de funciones internas]=====================*/
void task(void)
{
   MmcSPI mmc0;
   filesystem_info_t *fs;
   file_desc_t *file0, *file1, *file2, *file3;

   uint8_t buffer[TEST_BUFFER_SIZE];
   ext2_format_param_t format_parameters;

   int32_t ret;
   uint32_t lret;

   /* init CIAA kernel and devices */
   //ciaak_start();
   ret=vfs_init(); if(ret < 0) while(1);

   /* Basic test
    * This secuence test the basic operation of MMC device.
    * Open the device, get info block, erase a block and verify or cleared,
    * write a block, read this block and verify the data read is same as writed
    * finally close the device
    */

   /* Create device and initialize it */
   ooc_init_class(MmcSPI);
   mmc0 = mmcSPI_new(); if(NULL == mmc0) while(1);
   ret = mmcSPI_init(mmc0); //if(ret < 0) while(1);
   if(0 == ret)
   {
      // Turn ON LEDG if the write operation was successful
      gpioWrite( LEDG, ON );
   }
   else
   {
         // Turn ON LEDR if the write operation was fail
         gpioWrite( LEDR, ON );
   }
   //while(1);

   /* Create file system object with device and fs driver */
   ret = filesystem_create(&fs, (Device) mmc0, &ext2_driver); if(ret < 0) while(1);

   /* format */
   /* Set ext2 format parameters */
   format_parameters.partition_size = 10*1024;
   format_parameters.block_size = 1024;
   format_parameters.block_node_factor = 4;

   ret = vfs_format(&fs, (void *)&format_parameters);
   if(0 == ret)
   {
      // Turn ON LEDG if the write operation was successful
      gpioWrite( LED3, ON );
   }
   else
   {
      // Turn ON LEDR if the write operation was fail
      gpioWrite( LED1, ON );
   }
   while(1);
   /* mount */
   ret = vfs_mkdir("/mount", 0); if(ret < 0) while(1);

   //ASSERT_SEQ(2);

   ret = vfs_mount("/mount/ext2", &fs); if(ret < 0) while(1);

   //ASSERT_SEQ(3);

   ret = vfs_mkdir("/mount/ext2/dir0", 0); if(ret < 0) while(1);
   ret = vfs_mkdir("/mount/ext2/dir1", 0); if(ret < 0) while(1);
   ret = vfs_mkdir("/mount/ext2/dir2", 0); if(ret < 0) while(1);
   ret = vfs_mkdir("/mount/ext2/dir2/dir3", 0); if(ret < 0) while(1);

   //ASSERT_SEQ(4);
   /* Show actual vfs tree */
   //ret=vfs_print_tree(); if(ret < 0) while(1);

   //ASSERT_SEQ(5);
   /* Fixme: Duplicated file in ext2. Error not handled */
   ret = vfs_open("/mount/ext2/file0", &file0, VFS_O_CREAT); if(ret < 0) while(1);
   ret = vfs_open("/mount/ext2/file1", &file1, VFS_O_CREAT); if(ret < 0) while(1);
   //ret=vfs_print_tree(); if(ret < 0) while(1);

   //ASSERT_SEQ(6);

   ret = vfs_open("/mount/ext2/dir2/file2", &file2, VFS_O_CREAT); if(ret < 0) while(1);
   ret = vfs_open("/mount/ext2/dir2/file3", &file3, VFS_O_CREAT); if(ret < 0) while(1);
   ret = vfs_close(&file0); if(ret < 0) while(1);
   ret = vfs_close(&file1); if(ret < 0) while(1);
   ret = vfs_close(&file2); if(ret < 0) while(1);
   ret = vfs_close(&file3); if(ret < 0) while(1);

   //ASSERT_SEQ(7);

   ret = vfs_open("/mount/ext2/file0", &file0, 0); if(ret < 0) while(1);
   test_fill_buffer(buffer, TEST_BUFFER_SIZE);
   lret = vfs_write(&file0, buffer, TEST_BUFFER_SIZE); if(lret < 0) while(1);
   ret = vfs_close(&file0); if(ret < 0) while(1);
   ret = vfs_open("/mount/ext2/file0", &file0, 0); if(ret < 0) while(1);
   memset(buffer, 0, TEST_BUFFER_SIZE);
   lret = vfs_read(&file0, buffer, TEST_BUFFER_SIZE); if(lret != TEST_BUFFER_SIZE) while(1);
   ret = test_check_buffer(buffer, TEST_BUFFER_SIZE); if(ret < 0) while(1);
   lret = vfs_read(&file0, buffer, TEST_BUFFER_SIZE); if(lret != 0) while(1);

   //ASSERT_SEQ(8);

   //ret=vfs_print_tree(); if(ret < 0) while(1);
   ret = vfs_close(&file0); if(ret < 0) while(1);
   ret = vfs_unlink("/mount/ext2/dir2/file2"); if(ret < 0) while(1);
   ret = vfs_unlink("/mount/ext2/dir2/file3"); if(ret < 0) while(1);
   ret = vfs_open("/mount/ext2/dir2/file4", &file0, VFS_O_CREAT); if(ret < 0) while(1);
   ret = vfs_open("/mount/ext2/dir2/file5", &file1, VFS_O_CREAT); if(ret < 0) while(1);
   ret = vfs_close(&file1); if(ret < 0) while(1);
   //ret=vfs_print_tree(); if(ret < 0) while(1);

   //ASSERT_SEQ(9);

   ret = vfs_open("/mount/ext2/dir2/file5", &file3, VFS_O_CREAT); if(ret < 0) while(1);
   test_fill_buffer(buffer, TEST_BUFFER_SIZE);
   lret = vfs_write(&file3, buffer, TEST_BUFFER_SIZE); if(lret != TEST_BUFFER_SIZE) while(1);
   memset(buffer, 0, TEST_BUFFER_SIZE);
   lret = vfs_lseek(&file3, 0, SEEK_SET); if(lret != 0) while(1);
   lret = vfs_read(&file3, buffer, TEST_BUFFER_SIZE); if(lret != TEST_BUFFER_SIZE) while(1);
   ret = test_check_buffer(buffer, TEST_BUFFER_SIZE); if(ret < 0) while(1);
   ret = vfs_close(&file3); if(ret < 0) while(1);
}

static void test_fill_buffer(uint8_t *buffer, uint16_t size)
{
   uint16_t i;

   for(i=0; i<size; i++)
   {
      buffer[i] = i%10 + 0x30;   /* ASCII desde 0 a 9 */
   }
}

static int test_check_buffer(uint8_t *buffer, uint16_t size)
{
   uint16_t i;
   //printf( "test_assert_buffer(): Differences\n",
   //                  "buff\t\tseq\n");
   for(i=0; i<size; i++)
   {
      if(buffer[i] != i%10 + 0x30)
      {
         //printf("%c\t\t%c\n",buffer[i],i%10 + 0x30);
      }
   }
   if(i==size)
   {
   //printf( "test_assert_buffer(): OK, no differences\n");
   }
   return 0;
}

/*==================[definiciones de funciones externas]=====================*/

// FUNCION que se ejecuta cada vezque ocurre un Tick
bool_t diskTickHook( void *ptr ){
   disk_timerproc();   // Disk timer process
   return 1;
}


/*==================[fin del archivo]========================================*/
