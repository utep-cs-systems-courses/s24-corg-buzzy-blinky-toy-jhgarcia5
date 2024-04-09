#include <msp430.h>
#include "libTimer.h"
#include "led.h"

int main(void) {

  P1DIR |= LEDS;
  P1OUT &= ~LED_GREEN;
  P1OUT |= LED_RED;

  configureClocks();
  enableWDTInterrupts();

  or_sr(0x18);
}

int secondCount = 0;

void
__interrupt_vec(WDT_VECTOR) WDT()
{

  secondCount += 1;
  if (secondCount >= 250){
    secondCount = 0;
    P1OUT ^= LED_GREEN;
  }
}
