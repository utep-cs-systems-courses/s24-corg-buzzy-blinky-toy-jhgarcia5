#include <msp430.h>
#include "libTimer.h"

void configureClocks(){
  WDTCTL = WDTPW + WDTHOLD;//Disable Watchdog Timer
  BCSCTL1 = CALBC1_16MHZ;  // Set DCO to 16 Mhz
  DCOCTL = CALDCO_16MHZ;
  BCSCTL2 &= ~(SELS);     // SMCLK source = DCO
  BCSCTL2 |= DIVS_3;      // SMCLK = DCO / 8
}

void enableWDTInterrupts()
{


  WDTCTL = WDTPW |
    WDTTMSEL |
    WDTCNTCL |
    1;
  IE1 |= WDTIE;
  
}

void timerAUpmode()
{

  TA0CCR0 = 0;
  TA0CCR1 = 0;
  TA0CCTL1 = OUTMOD_3;/* Toggle p1.6 when timer=count1 */
  // Timer A control:
  //  Timer clock source 2: system clock (SMCLK)
  //  Mode Control 1: continuously 0...CCR0
  TACTL = TASSEL_2 + MC_1;
}
