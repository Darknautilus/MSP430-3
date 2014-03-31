
#include "msp430fg4618.h"
#include "lcd.h"

unsigned int cpt;

void init_timer()
{
  TACTL = 0x2<<8 &
          0x0<<6 &
          0x1<<4 &
          0x1<<1;
}

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD; // stop watchdog timer
  lcd_init(); // Initialize driver
  P5DIR |= 0x02 ; // Set P5.1 to output direction
  cpt = 0;
  for(;;)
  {
    if(P1IN==0x01 || P1IN==0x02 )
    {
      cpt++;
      P5OUT ^= 0x02 ; // toggle P5.1 (LED4)
      while(P1IN==0x02);
      while(P1IN==0x01);
    }
    lcd_display_number(cpt);
    volatile unsigned int i;
    for(i=0;i<1000;i++);
    
  }
}