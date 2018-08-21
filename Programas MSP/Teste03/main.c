#include <msp430g2553.h>
#define sec 1000000


#pragma vector = PORT1_VECTOR
__interrupt void permuta(void)
{
  P1OUT ^= BIT0 + BIT6;
  __delay_cycles(sec/6);
  
  P1IFG &= ~BIT1;
}

int main(void)
{
// control    password     hold
    WDTCTL =    WDTPW +   WDTHOLD;
    
  //P1DIR |=  BIT0 + BIT6;   // P1.0 E P1.6 COMO SA�DA
  //P1DIR &= ~BIT1;          // P1.1 COMO ENTRADA (MESMO N�O PRECISANDO)
  P2DIR |=   0xFF;                   // DEFINE TODOS OS PORTS DE P2 COMO SA�DA
  P2OUT =    BIT0;
  P1REN |=   BIT1 + BIT2;            // ATIVAR O RESISTOR DE PULL UP/DOWN
  P1IE  |=   BIT1 + BIT2;            // ATIVA AS INTERRUP��ES NO PINO P1.1 E P1.2
  P1IFG &= ~(BIT1 + BIT2);           // RETIRA AS INTERRUP��ES PENDENTES
  P1OUT |=   BIT1 + BIT2;            // DEFINO QUE O RESISTOR � PULL UP 
  __enable_interrupt();
    
    while(1)
    {
     
    
    }

}