#include "contiki.h"
#include "dev/leds.h"
#include "dev/button-sensor.h"
#include <stdio.h> /* For printf() */

//-----------------------------------------------------------------
PROCESS(blink_process, "blink example");
AUTOSTART_PROCESSES(&blink_process);
//-----------------------------------------------------------------
PROCESS_THREAD(blink_process, ev, data)
{
    PROCESS_EXITHANDLER(goto exit);
    PROCESS_BEGIN();
    
    /* Initialize stuff here. */
    
    printf("++++++++++++++++++++++++++++++\n");
    printf("+  LESSON 1, FIRST EXERCISE  +\n");
    printf("++++++++++++++++++++++++++++++\n");
    printf("+ Blink app w/ button sensor +\n");
    printf("++++++++++++++++++++++++++++++\n\n");
    
    SENSORS_ACTIVATE(button_sensor);
    SENSORS_ACTIVATE(button_sensor2);
    //leds_on(LEDS_ALL);
    printf("+     All leds are on     +\n\n");
    printf("Press the user button to begin\n\n");
    
    while(1) {
        /* Do the rest of the stuff here. */
        
        
        //leds_toggle(LEDS_GREEN);
        //leds_off(LEDS_ALL);
        PROCESS_WAIT_EVENT_UNTIL((ev==sensors_event) && (data == &button_sensor));
        //PROCESS_WAIT_EVENT_UNTIL(ev==sensors_event);
        //PROCESS_WAIT_EVENT();
        
        leds_toggle(LEDS_GREEN);

        PROCESS_WAIT_EVENT_UNTIL((ev==sensors_event) && (data == &button_sensor2));
        //PROCESS_WAIT_EVENT_UNTIL(ev==sensors_event);
        //PROCESS_WAIT_EVENT();
        
        leds_toggle(LEDS_RED);
    }
    
exit:
    leds_off(LEDS_ALL);
    PROCESS_END();
}
