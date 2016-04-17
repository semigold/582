#include "contiki.h"
#include "dev/leds.h"
#include "dev/button-sensor.h"
#include <stdio.h> /* For printf() */
#include <math.h>

#define Num 200

int __attribute__((section(".persistent"))) init_flag = 0;
int __attribute__((section(".persistent"))) t = 0;
int __attribute__((section(".persistent"))) j = 1;
int __attribute__((section(".persistent"))) len = 334;
int __attribute__((section(".persistent"))) i = 334;
int __attribute__((section(".persistent"))) q = 0;
int __attribute__((section(".persistent"))) k = 0;
int __attribute__((section(".persistent"))) h = 0;
int __attribute__((section(".persistent"))) nines = 0;
int __attribute__((section(".persistent"))) predigit = 0;
int __attribute__((section(".persistent"))) A[] = {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};
//-----------------------------------------------------------------
PROCESS(pi_process, "pi demo example");
AUTOSTART_PROCESSES(&pi_process);
//-----------------------------------------------------------------
PROCESS_THREAD(pi_process, ev, data)
{
	PROCESS_EXITHANDLER(goto exit);
	PROCESS_BEGIN();

	/* Initialize stuff here. */
	while(1) {

		for(; j < Num + 1; ++j) {
			q = 0;
			i = len;     
			for(; i > 0; --i) {
				int x  = 10 * A[i-1] + q*i;
				A[i-1] = x % (2*i - 1);
				q = x / (2*i - 1);
			}

			A[0] = q%10;
			q    = q/10;

			if (9 == q) {
				++nines;
			}
			else if (10 == q) {
				uart_printf("%d", predigit + 1);
				k = 0;
				for (; k < nines; ++k) {
					uart_printf("%d", 0);
				}
				predigit, nines = 0;
			}
			else {
				uart_printf("%d", predigit);
				predigit = q;

				if (0 != nines) {    
					h = 0;
					for (; h < nines; ++h) {
						uart_printf("%d", 9);
					}

					nines = 0;
				}
			}
		}
		uart_printf("%d", predigit);
		__delay_cycles(F_CPU);
	}
exit:
	leds_off(LEDS_ALL);
	PROCESS_END();
}
