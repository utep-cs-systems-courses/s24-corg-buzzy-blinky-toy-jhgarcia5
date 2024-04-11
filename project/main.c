#include <msp430.h>
#include "libTimer.h"
#include "led.h"

//#define LED_RED BIT0
//#define LED_GREEN BIT6
//#define LEDS (BIT0 | BIT6)

#define SW1 BIT3
#define SWITCHES SW1

int main(void) {

  //This gets the leds and turns them off
  P1DIR |= LEDS;
  P1OUT &= ~(LED_GREEN | LED_RED);

  //Setting up clocks
  configureClocks();
  enableWDTInterrupts();

  //Sets up buttons
  P1REN |= SWITCHES; //resistors for switches
  P1IE |= SWITCHES; //enables interrupts from swicthes
  P1OUT |= SWITCHES; //pull ups for switches
  P1DIR &= ~SWITCHES;  // set switches bits for input

  or_sr(0x18);
}

int secondCount = 0;
int state = 0;
int blinking = 0;

void switch_interrupt_handler()
{
  char p1val = P1IN;

  P1IES |= (p1val & SWITCHES);
  P1IES &= (p1val | ~SWITCHES);

  
  state ^= 1;
  if(state){
    P1OUT = (P1OUT & ~LED_RED) | LED_GREEN;
    
  } else {
    P1OUT = (P1OUT & ~LED_GREEN) | LED_RED;
  }

  if (blinking) {
    blinking = 0;
  } else {
    blinking = 1;
  }
  
}

void __interrupt_vec(PORT1_VECTOR) Port_1(){

  if (P1IFG & SWITCHES){
    P1IFG &= ~SWITCHES;
    switch_interrupt_handler();
  }
}


void __interrupt_vec(WDT_VECTOR) WDT()
{

  if (!blinking) {
    return;
  }
  
  secondCount += 1;
  if (secondCount >= 50){
    secondCount = 0;

    if(state){
      P1OUT = (P1OUT & ~LED_RED) | LED_GREEN;
      state = 0;
    } else {
      P1OUT = (P1OUT & ~LED_GREEN) | LED_RED;
      state = 1;
    }
  }
}
