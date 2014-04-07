
#include "msp430fg4618.h"
#include "intrinsics.h"
#include "lcd.h"

unsigned int cpt;

void init_timer()
{
  __enable_interrupt();
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

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD; // stop watchdog timer
  lcd_init(); // Initialize driver
  P5DIR |= 0x02 ; // Set P5.1 to output direction
  cpt = 0;
  lcd_display_number(cpt);
  init_timer();
  for(;;);
}