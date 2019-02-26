
#define F_CPU 8000000 
#include <avr/io.h> 
#include <util/delay.h> 
void setPort()
{
  DDRA = 0xff; // PORT A est en mode sortie
  DDRB = 0xff; // PORT B est en mode sortie
  DDRC = 0xff; // PORT C est en mode sortie
  DDRD = 0x00; // PORT D est en mode ENTREE
}
void attendre(float temps)
{
for(int i =0; i< (int)(temps); i++ )
{
  _delay_us(90);
}
  
}

void signalPWM (double ratio,float b)
{
  float temps = 0; 
  while (temps < 2000)
  {
    PORTB=0x02;
    attendre(ratio*b*10);
    PORTB=0x00;
    attendre((1-ratio)*b*10);
    temps += b;

  }
}

int main()
{
  setPort();

 PORTB=0x00;
 _delay_ms(2000);
  signalPWM(0.25 ,16.666666666);
   signalPWM(0.5 ,16.666666666);
      signalPWM(0.75 ,16.666666666);
 PORTB=0x02;
 _delay_ms(2000);
PORTB=0x00;
 _delay_ms(2000);
  signalPWM(0.25 ,2.5);
   signalPWM(0.5 ,2.5);
      signalPWM(0.75 ,2.5);
PORTB=0x02;
 _delay_ms(2000);
PORTB=0x00;



  return 0; 
}
