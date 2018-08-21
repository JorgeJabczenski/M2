#include <MSP430G2553.h>

#define sec 1000000
int JORGE = BIT0;
int DR = 0;


#pragma vector = PORT1_VECTOR
__interrupt void interrupt1 (void){

  if ((P1IFG & BIT2) == BIT2){
    if (JORGE == BIT3 || JORGE == BIT4){
      P2OUT = 0xFF;
      __delay_cycles(sec*2);
      P2OUT = JORGE;
    }
    P1IFG &= ~(BIT2 + BIT1);
  }
  
  if ((P1IFG & BIT1) == BIT1){
    if (JORGE == BIT3 || JORGE == BIT4){
      P2OUT = 0x00;
      __delay_cycles(sec*2);
      P2OUT = JORGE;
    }  
    P1IFG &= ~(BIT2 + BIT1);
  }
}


int main( void )
{

  WDTCTL = WDTPW + WDTHOLD;
  

  P2DIR = 0xFF;
  P2OUT = 0;
  P2OUT |= BIT0;
  P2SEL &= ~(BIT6 + BIT7);
  
  P1IE  |= BIT2 + BIT1;
  P1IES |= BIT2 + BIT1;
  //P1IFG &= ~(BIT0 + BIT1);
  P1IFG = 0;
  P1REN |= BIT2 + BIT1;
  P1OUT |= BIT2 + BIT1;
  __enable_interrupt();
  
  __delay_cycles(sec/10);
  
 
  
  while(1)
  {

    if (!DR)
      JORGE = JORGE << 1;
      
    if (DR)
      JORGE = JORGE >> 1;
      
    
    if (JORGE == BIT7)
      DR = 1; 
    
    if (JORGE == BIT0)
      DR = 0;
    
    
    P2OUT = JORGE;
    __delay_cycles(sec/10);
    
  } // WHILE

}