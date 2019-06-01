 #ifndef __IRLED_CPP__
 #define __IRLED_CPP__
 #include "IRLED.h"

IRLED::IRLED(){
    init_();
    char param[] = {'D','6'};
    //init_port(param);
    clock::ajustementPWM(104); // configurate registers for a 38KHz PWM
}

void IRLED::turnON(){
    // We need to pulse the LED at 38kHz
     // Stops PWM on D6
    TCCR1A |= (1<<COM1A0); //Allow PWM
    ON_ = true;
}

void IRLED::turnOFF(){
    // select the port letter
    TCCR1A &= ~(1<<COM1A0);// STOPS PWM on D6
    ON_ = false;
}

 #endif // __IRLED_CPP__