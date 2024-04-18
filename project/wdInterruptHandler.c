#include <msp430.h>
#include "buzzer.h"
#include "led.h"
#include "switches.h"

int state = 0;

void __interrupt_vec(WDT_VECTOR) WDT(){

  static int secondCount = 0;
  secondCount += 1;

  switch(state){

  case 0:
    if (secondCount >= 50){
      mode_one();
      secondCount = 0;
    }
    break;
  case 1:
    if (secondCount >= 100){
      mode_two();
      secondCount = 0;
    }
    break;
  case 2:
    if (secondCount >= 50){
      mode_three();
      secondCount = 0;
    }
    break;
  case 3:
    break;
  }
  
}
