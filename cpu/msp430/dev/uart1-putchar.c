#include <stdio.h>
#include "dev/uart1.h"

#if defined(__MSP430_HEADER_VERSION__) && __MSP430_HEADER_VERSION__ < 1074
int
putchar(int c)
{
  uart1_writeb((char)c);
  return c;
}
#endif
