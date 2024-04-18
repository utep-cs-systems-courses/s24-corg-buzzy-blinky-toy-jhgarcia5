#include <msp430.h>
#include <switches.h>

//Switches on p2
void __interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHES) {
    P2IFG &= ~SWITCHES;
    switch_interrupt_handler();
  }
}
