#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include "IRLED.h"
#include "clock.h"


int main (){
    IRLED irLed;
    //clock::ajustementPWM(104);<
    DDRD = 0xff;

//    irLed.turnON();
    for (;;){
    irLed.turnON();
    _delay_ms(2.4);
    irLed.turnOFF();
    _delay_ms(0.6);
    irLed.turnON();
    _delay_ms(1.2);
    irLed.turnOFF();
    _delay_ms(0.6);
    irLed.turnON();
    _delay_ms(1.2);
    irLed.turnOFF();
    _delay_ms(0.6);
    irLed.turnON();
    _delay_ms(1.2);
    irLed.turnOFF();
    _delay_ms(0.6);
    irLed.turnON();
    _delay_ms(0.6);
    irLed.turnOFF();
    _delay_ms(0.6);
    irLed.turnON();
    _delay_ms(1.2);
    irLed.turnOFF();
     irLed.turnON();
    _delay_ms(1.2);
    irLed.turnOFF();
    _delay_ms(0.6); irLed.turnON();
    _delay_ms(1.2);
    irLed.turnOFF();
    _delay_ms(0.6); 
    irLed.turnON();
    _delay_ms(0.6);
    irLed.turnOFF();
    _delay_ms(0.6); irLed.turnON();
    _delay_ms(0.6);
    irLed.turnOFF();
    _delay_ms(0.6); irLed.turnON();
    _delay_ms(1.2);
    irLed.turnOFF();
    _delay_ms(0.6); irLed.turnON();
    _delay_ms(1.2);
    irLed.turnOFF();
    _delay_ms(0.6);


    _delay_ms(10);
    }
 
                  
    return 0; 
}