/*
 *  COPYRIGHT (c) 1989-2012.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.org/license/LICENSE.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <bsp.h> /* for device driver prototypes */
#include "tmacros.h"
#include <rtems/untar.h>
#include <rtems/error.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "initial_filesystem_tar.h"

const char rtems_test_name[] = "TAR 1";

/* forward declarations to avoid warnings */
rtems_task Init(rtems_task_argument argument);
void test_untar_from_memory(void);
void test_untar_from_file(void);
void test_untar_chunks_from_memory(void);

#define TARFILE_START initial_filesystem_tar
#define TARFILE_SIZE  initial_filesystem_tar_size

void test_cat(
  char *file,
  int   offset_arg,
  int   length
);

void test_untar_from_memory(void)
{
  rtems_status_code sc;
  rtems_printer     printer;

  rtems_print_printer_printf(&printer);

  printf("Untaring from memory - ");
  sc = Untar_FromMemory_Print((void *)TARFILE_START, TARFILE_SIZE, &printer);
  if (sc != RTEMS_SUCCESSFUL) {
    printf ("error: untar failed: %s\n", rtems_status_text (sc));
    exit(1);
  }
  printf ("successful\n");

  /******************/
  printf( "========= /home/test_file =========\n" );
  test_cat( "/home/test_file", 0, 0 );

  /******************/
  printf( "========= /symlink =========\n" );
  test_cat( "/symlink", 0, 0 );

}

void test_untar_from_file(void)
{
  int                fd;
  int                rv;
  ssize_t            n;

  puts( "Copy tar image to test.tar" );
  /* Copy tar image from object to file in IMFS */
  fd = open( "/test.tar", O_CREAT|O_TRUNC|O_WRONLY, 0777 );
  rtems_test_assert( fd != -1 );

  n = write( fd, TARFILE_START, TARFILE_SIZE );
  rtems_test_assert( n == TARFILE_SIZE );
  close( fd );

  /* make a directory to untar it into */
  rv = mkdir( "/dest", 0777 );
  rtems_test_assert( rv == 0 );

  rv = chdir( "/dest" );
  rtems_test_assert( rv == 0 );

  /* Untar it */
  rv = Untar_FromFile( "/test.tar" );
  printf("Untaring from file - ");
  if (rv != UNTAR_SUCCESSFUL) {
    printf ("error: untar failed: %i\n", rv);
    exit(1);
  }
  printf ("successful\n");

  /******************/
  printf( "========= /dest/home/test_file =========\n" );
  test_cat( "/dest/home/test_file", 0, 0 );

  /******************/
  printf( "========= /dest/symlink =========\n" );
  test_cat( "/dest/symlink", 0, 0 );
}

void test_untar_chunks_from_memory(void)
{
  rtems_status_code sc;
  rtems_printer     printer;
  int rv;
  Untar_ChunkContext ctx;
  unsigned long counter = 0;
  char *buffer = (char *)TARFILE_START;
  size_t buflen = TARFILE_SIZE;

  rtems_print_printer_printf(&printer);

  /* make a directory to untar it into */
  rv = mkdir( "/dest2", 0777 );
  rtems_test_assert( rv == 0 );

  rv = chdir( "/dest2" );
  rtems_test_assert( rv == 0 );

  printf( "Untaring chunks from memory - " );
  Untar_ChunkContext_Init(&ctx);
  do {
    sc = Untar_FromChunk_Print(&ctx, &buffer[counter], (size_t)1 , &printer);
    rtems_test_assert(sc == RTEMS_SUCCESSFUL);
    counter ++;
  } while (counter < buflen);
  printf("successful\n");

  /******************/
  printf( "========= /dest2/home/test_file =========\n" );
  test_cat( "/dest2/home/test_file", 0, 0 );

  /******************/
  printf( "========= /dest2/symlink =========\n" );
  test_cat( "/dest2/symlink", 0, 0 );

}

rtems_task Init(
  rtems_task_argument ignored
)
{
  TEST_BEGIN();

  test_untar_from_memory();
  puts( "" );
  test_untar_from_file();
  puts( "" );
  test_untar_chunks_from_memory();

  TEST_END();
  exit( 0 );
}


/* NOTICE: the clock driver is explicitly disabled */
#define CONFIGURE_APPLICATION_DOES_NOT_NEED_CLOCK_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER

#define CONFIGURE_MAXIMUM_TASKS            1
#define CONFIGURE_LIBIO_MAXIMUM_FILE_DESCRIPTORS 5

#define CONFIGURE_INITIAL_EXTENSIONS RTEMS_TEST_INITIAL_EXTENSION

#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

#define CONFIGURE_INIT
#include <rtems/confdefs.h>
