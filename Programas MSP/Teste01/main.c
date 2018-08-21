
#include <msp430g2553.h>

void delay(unsigned int time){
  for(int i = 0; i < time; i++);
}

void piscapisca(){
  P1OUT ^= BIT0 + BIT6;
  delay(10000);
      
  P2OUT ^= BIT3 + BIT1;
  delay(25000);
      
  P1OUT ^= BIT0 + BIT6;
  delay(10000);
      
  P2OUT ^= BIT1 + BIT5;
  delay(25000);
      
  P1OUT ^= BIT0 + BIT6;
  delay(10000);
      
  P2OUT ^= BIT5 + BIT3;
  delay(25000);
}

int main( void )
{
  // Stop watchdog timer to prevent time out reset
   WDTCTL = WDTPW + WDTHOLD;
  
   P1DIR |= BIT0 + BIT6;
   //P1OUT &= 0;
   P1OUT |= BIT0;
   
   P2DIR |= BIT3 + BIT1 + BIT5;
   P2OUT &= 0;
   //P2OUT |= BIT3;

    while(1)
    {
      if(!(P1IN & BIT3)){
         //P1OUT ^= BIT0 + BIT6;
        piscapisca();
    }
    
    delay(1000);
  }
}
