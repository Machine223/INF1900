#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include "IRLED.h"

int main (){
    IRLED irLed;
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
    for (;;);               
    return 0; 
}