#include <appdef.hpp>
#include <stdio.h>
#include <stdlib.h>

/*
 * Fill this section in with some information about your app.
 * All fields are optional - so if you don't need one, take it out.
 */
APP_NAME("STDLIB test")
APP_DESCRIPTION("Testing STDLIB")
APP_AUTHOR("PC")
APP_VERSION("1.0.2")

extern "C" int __attribute__((section(".bootstrap.text"))) main(void) {
  fputs("Loading the CP test\n", stdout);
  exit(EXIT_SUCCESS);
}
