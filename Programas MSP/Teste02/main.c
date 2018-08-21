
#include <msp430g2553.h>

#define sec 1000000


int led_aceso = BIT0;
int sentido = 0;

#pragma vector = PORT1_VECTOR
 __interrupt void tiro (void)
{ 
  // DETECTAR SE O BOTÃO FOI APERTADO NO MOMENTO QUE O LED CENTRAL ESTAVA ACESO
  if (led_aceso == BIT1){
  
  P2OUT = BIT0 + BIT1 + BIT2;
  __delay_cycles(sec*2);
  
  // REINICIAR A SEQUÊNCIA
  if (sentido){
    P2OUT = BIT2;
    led_aceso = BIT2;
  }
  else {
    P2OUT = BIT0;
    led_aceso = BIT0;
  }
  
  }
  
  P1IFG &= ~BIT3; // RESETA A FLAG DE INTERRUPÇÃO
}



int main( void )
{
  
  WDTCTL = WDTPW + WDTHOLD;
  
  P2DIR |=  BIT0 + BIT1 + BIT2; // DEFINE P2.0, P1.2 E P2.2 COMO SAIDA
  P2OUT |=  led_aceso;          // LIGA O PRIMEIRO LED VERDE DA SEQUÊNCIA
  P2OUT &= ~(BIT1 + BIT2);      // DESLIGA OS DEMAIS LEDS
  
  P1REN |=  BIT3;   // HABILITA RESISTOR DE PULL-UP (1)/ PULL-DOWN(0)
  P1OUT |=  BIT3;   // DEFINE QUE O RESISTOR É DE PULL-UP
  P1IE  |=  BIT3;   // ENABLE INTERRUPÇÃO NO BOTÃO
  P1IES |=  BIT3;   // DEFINE A INTERRUPÇÃO COMO BORDA DE DESCIDA
  //P1IES &= ~BIT3; // DEFINE A INTERRUPÇÃO COMO BORDA DE SUBIDA
  
  P1IFG &= ~BIT3;       // TIRA QUALQUER INTERRUPÇÃO PENDENTE
  __enable_interrupt(); // HABILITA AS INTERRUPÇÕES EM GERAL
 
  while(1){
    
    if (sentido == 0){
      if (led_aceso < 4){
        led_aceso = led_aceso  << 1;
        P2OUT = led_aceso;
        __delay_cycles(sec/2);
      } else {
        sentido = 1;
      }
    }
    
    if (sentido == 1){
      if (led_aceso > 1){
        led_aceso = led_aceso >> 1 ;
        P2OUT = led_aceso;
        __delay_cycles(sec/2);
      } else {
        sentido = 0;
      }
    }

  } // end while
  
}
