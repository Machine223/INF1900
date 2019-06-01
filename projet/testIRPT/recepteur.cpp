#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include "LED.h"
#include "IRPT.h"

int main (){
    DDRB |= 0x03;
    IRPT IRSensor(7);
    LED led("B0");
    for (;;)
        PORTB= IRSensor.read();             
    return 0; 
}