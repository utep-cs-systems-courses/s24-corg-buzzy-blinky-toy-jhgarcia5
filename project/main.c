#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "buzzer.h"

#define SW1 BIT0
#define SW2 BIT1
#define SW3 BIT2
#define SW4 BIT3
#define SWITCHES (SW1 | SW2 | SW3 | SW4)

int main(void) {

  //This gets the leds and turns them off
  P1DIR |= LEDS;
  P1OUT &= ~(LED_GREEN | LED_RED);

  //Setting up clocks
  configureClocks();
  enableWDTInterrupts();

  //BUZZER
  //buzzer_init();
  
  //Sets up buttons
  P2REN |= SWITCHES; //resistors for switches
  P2IE |= SWITCHES; //enables interrupts from swicthes
  P2OUT |= SWITCHES; //pull ups for switches
  P2DIR &= ~SWITCHES;  // set switches bits for input

  or_sr(0x18);
}

int secondCount = 0;
int state = 0;
int currLed = 0;
int blinking = 0;
//int buzzerCount = 0;

void switch_interrupt_handler()
{  
  char p2val = P2IN;

  P2IES |= (p2val & SWITCHES);
  P2IES &= (p2val | ~SWITCHES);

  if ((p2val & SW1) == 0) {
    state = 0;
  }

  if ((p2val & SW2) == 0) {
    state = 1;
  }

  if ((p2val & SW3) == 0) {
    state = 2;
  }

  if ((p2val & SW4) == 0) {
    state = 3;
  }
  /*
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
  */
}

void __interrupt_vec(PORT2_VECTOR) Port_2(){
  
  if (P2IFG & SWITCHES){
    P2IFG &= ~SWITCHES;
    switch_interrupt_handler();
    //buzzer_set_period(1000);
  }
}


void __interrupt_vec(WDT_VECTOR) WDT()
{
  /*
  buzzerCount += 1;
  if (buzzerCount >= 250){
    buzzerCount = 0;
    //buzzer_set_period(0);
  }

  if (!blinking) {
    return;
  }
  */
  
  secondCount += 1;

  switch (state){
  case 0:
    
    
    if (secondCount >= 50){
      P1OUT ^= (LED_GREEN | LED_RED);
      secondCount = 0;
    }
    break;

  case 1:
    
    if (secondCount >= 100){
      P1OUT ^= (LED_GREEN | LED_RED);
      secondCount = 0;
    }
    break;

  case 2:
   
    if (secondCount >= 50) {
      if (currLed){
	P1OUT = (P1OUT & ~LED_RED) | LED_GREEN;
	currLed = 0;
      } else {
	P1OUT = (P1OUT & ~LED_GREEN) | LED_RED;
	currLed = 1;
      }
    }
    break;
  case 3:
    if (secondCount >= 25){
      P1OUT ^= LED_GREEN;
      secondCount = 0;
    }
    break;
  }

  
  /*
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
  */
}
