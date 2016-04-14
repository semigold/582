#include <stdio.h>
#include "dev/uart0.h"

#if defined(__MSP430_HEADER_VERSION__) && __MSP430_HEADER_VERSION__ < 1074
int
putchar(int c)
{
  uart0_writeb((char)c);
  return c;
}
#endif
