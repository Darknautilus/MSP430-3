
#include "msp430fg4618.h"
#include "intrinsics.h"
#include "lcd.h"

unsigned int cpt;

void init_timer()
{
  __enable_interrupt();
  
  P1IE = 3; // enables interrupts on P1.0 and P1.1
  
  TACCR0 = 10486;
  TACTL = 2<<8 | // SMCLK
          0<<6 | // divided by 1
          1<<4 ; // UP mode
  TACCTL0 = 1<<4;
}

#pragma vector=TIMERA0_VECTOR
__interrupt void mon_traitant_interruption_timer(void)
{
  lcd_display_number(cpt);
  cpt++;
}

#pragma vector=PORT1_VECTOR
__interrupt void mon_traitant_interruption_bouton(void)
{
  if(P1IFG & 1) // si on a appuyé sur S1
  {
    cpt = 0; // on remet le compteur à 0
    lcd_display_number(cpt);
  }
  else if(P1IFG & 2)// si on a appuyé sur S2
  {
    // on start/stop le timer
    TACTL = TACTL ^ (1<<4);
  }
  P1IFG = 0; // on réinitialise les flags pour pas provoquer une autre interruption
}

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD; // stop watchdog timer
  lcd_init(); // Initialize driver
  cpt = 0;
  lcd_display_number(cpt);
  init_timer();
  for(;;);
}