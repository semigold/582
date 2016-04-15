#include "contiki.h"
#include "dev/leds.h"
#include "dev/button-sensor.h"
#include <stdio.h> /* For printf() */
#include <math.h>

#define Num 100

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
int __attribute__((section(".persistent"))) A[334] = {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};
//-----------------------------------------------------------------
PROCESS(blink_process, "blink example");
AUTOSTART_PROCESSES(&blink_process);
//-----------------------------------------------------------------
PROCESS_THREAD(blink_process, ev, data)
{
	PROCESS_EXITHANDLER(goto exit);
	PROCESS_BEGIN();

	/* Initialize stuff here. */

	SENSORS_ACTIVATE(button_sensor);
	SENSORS_ACTIVATE(button_sensor2);

	while(1) {
		/* Do the rest of the stuff here. */


		//leds_toggle(LEDS_GREEN);
		//leds_off(LEDS_ALL);
		// PROCESS_WAIT_EVENT_UNTIL((ev==sensors_event) && (data == &button_sensor));
		//PROCESS_WAIT_EVENT_UNTIL(ev==sensors_event);
		//PROCESS_WAIT_EVENT();
		int p = 0;
		while(p < 10){ 
			leds_toggle(LEDS_GREEN);
			__delay_cycles(1000000);
			//uart_printf("he");        
			p++;		
		}
		//int r = 0;
		//for(; r < len; ++r) {
    		//	uart_printf("%d", A[r]);
   		 //}
		//PROCESS_WAIT_EVENT_UNTIL((ev==sensors_event) && (data == &button_sensor2));

		//PROCESS_WAIT_EVENT_UNTIL(ev==sensors_event);
		//PROCESS_WAIT_EVENT();

		//leds_toggle(LEDS_YELLOW);

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
		//while(1){
		//	uart_printf("****************************************************************************************************************************************************************************************************************");

		//}
		__delay_cycles(5000000);
	}
exit:
	leds_off(LEDS_ALL);
	PROCESS_END();
}
