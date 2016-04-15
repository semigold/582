#include "adc.h"
#include "dev/leds.h"

#define ADC_MONITOR_FREQUENCY 8000
#define ADC_MONITOR_THRESHOLD 3.0
uint32_t fram_location = 0;
void initAdcMonitor(void)
{

    //P1DIR |= BIT0;
    //P1OUT &= ~BIT0;
    /* Initialize timer for ADC trigger. */
    TA0CCR0 = (F_CPU/ADC_MONITOR_FREQUENCY);
    TA0CCR1 = TA0CCR0/2;
    TA0CCTL1 = OUTMOD_3;
    TA0CTL = TASSEL__SMCLK | MC__UP;

    /* Configure internal 2.0V reference. */
    while(REFCTL0 & REFGENBUSY);
    REFCTL0 |= REFVSEL_1 | REFON;
    while(!(REFCTL0 & REFGENRDY));

    /*
     * Initialize ADC12_B window comparator using the battery monitor.
     * The monitor will first enable the high side to the monitor voltage plus
     * 0.1v to make sure the voltage is sufficiently above the threshold. When
     * the high side is triggered the interrupt service routine will switch to
     * the low side and wait for the voltage to drop below the threshold. When
     * the voltage drops below the threshold voltage the device will invoke the
     * compute through power loss shutdown function to save the application
     * state and enter complete device shutdown.
     */
    ADC12CTL0 = ADC12SHT0_2 | ADC12ON;
    ADC12CTL1 = ADC12SHS_1 | ADC12SSEL_0 | ADC12CONSEQ_2 | ADC12SHP;
    ADC12CTL3 = ADC12BATMAP;
    ADC12MCTL0 = ADC12INCH_31 | ADC12VRSEL_1 | ADC12WINC;
    ADC12HI = (uint16_t)(4096*((ADC_MONITOR_THRESHOLD+0.1)/2)/(2.0));
    ADC12LO = (uint16_t)(4096*(ADC_MONITOR_THRESHOLD/2)/(2.0));
    ADC12IFGR2 &= ~(ADC12HIIFG | ADC12LOIFG);
    ADC12IER2 = ADC12HIIE;
    ADC12CTL0 |= ADC12ENC;

    if (fram_location == 100) {
        //P1OUT |= BIT0;
        leds_on(LEDS_GREEN);
    }
    else {
        //P1OUT &= ~BIT0;
        leds_on(LEDS_RED);
    }

   //leds_on(LEDS_GREEN); 
}

void stopAdcMonitor(void)
{
    /* Stop the timer, reference and ADC. */
    TA0CTL &= ~MC_3;
    REFCTL0 &= ~REFON;
    ADC12CTL0 &= ~(ADC12ENC | ADC12ON);
}

//#pragma vector = ADC12_VECTOR
//__interrupt void ADC12_ISR(void)

ISR(ADC12, power_loss) 
{
    switch(__even_in_range(ADC12IV, 36)) {
        case 0:        break;        // Vector  0: No interrupt
        case 2:        // Vector  2: ADC12MEMx Overflow
        case 4:        // Vector  4: Conversion time overflow
        case 6:                // Vector  6: Window comparator high side
            /* Disable the high side and enable the low side interrupt. */
            ADC12IER2 &= ~ADC12HIIE;
            ADC12IER2 |= ADC12LOIE;
            ADC12IFGR2 &= ~ADC12LOIFG;
            break;
        case 8:                // Vector  8: Window comparator low side
            /* Stop the ADC monitor and enter device shutdown with 64ms timeout. */
            stopAdcMonitor();
            ctpl_enterShutdown(CTPL_SHUTDOWN_TIMEOUT_64_MS);

            if (fram_location == 100) {
                fram_location = 0;
            }
            else {
                fram_location = 100;
            }


            /* Reinitialize the ADC monitor since the ADC state is not retained. */
            //initAdcMonitor();
            break;
        default: break;
    }
}

