#ifndef F_CPU
#define F_CPU 8000000
#endif
#include <avr/io.h>
#include <util/delay.h>
//#include "pins.h"
//#include "sonorite.h"
#include "tracker.h" 
#include "LED.h" 


// ecrire routine de depart pour allumer tout les LED

int main () {
    // faire la calibration
    DDRD = 0xFF;

    Tracker tracker;
    LED DEL5("B1");  
    LED DEL4("B0");  
    LED DEL3("B7");  
    LED DEL2("B6");  
    LED DEL1("D1");  
    if (tracker.calibrer()) // si le calibrage se fait bien 
    {
        DEL1.turnON();
        _delay_ms(5000);
        DEL1.turnOFF();
    }
    else
    {
        DEL2.turnON();
        _delay_ms(5000);
        DEL2.turnOFF();
    }
    for(;;)
    {
        if(tracker.lecture())
        {
            if(tracker.capteurs[4]){
                DEL5.turnON();
            }
            else{
                DEL5.turnOFF();
            }
            if(tracker.capteurs[3]){
                DEL4.turnON();
            }
            else{
                DEL4.turnOFF();
            }
            if(tracker.capteurs[2]){
                DEL3.turnON();
            }
            else{
                DEL3.turnOFF();
            } 
            if(tracker.capteurs[1]){
                DEL2.turnON();
            }
            else{
                DEL2.turnOFF(); 
            }
            if(tracker.capteurs[0]){
                DEL1.turnON();
            }
            else
            {
                DEL1.turnOFF();
            }
        }
    }
  
    return 0;
}
