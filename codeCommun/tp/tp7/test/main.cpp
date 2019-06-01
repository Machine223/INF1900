#ifndef F_CPU
#define F_CPU 8000000
#endif
#include <avr/io.h>
#include <avr/delay.h>
#include "Clock.hpp"
int main () 
{
    DDRD=0xff;
    DDRB=0xff;
    int ratio = 0; // le ratio de pwm généré =  ratio/200; 200 REPRESENTE LA VALEUR MAXIMALE QUE PEUT PRENDRE RATIO 
    clock::setTimerCTC(200,1);
    for(;;){ //on reliera la del au broches (D6,D8)
        clock::setPWM(ratio,ratio,1); // chaque 100 ms la led s allume avec une luminosité plus intense
        _delay_ms(150);
        ratio+=10;
        if (ratio>200)// valeur maximale est de 200
            ratio = 0;         
    }
    return 0;
}
