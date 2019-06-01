 #ifndef __IRPT_CPP__
 #define __IRPT_CPP__
 #include "IRPT.h"

void IRPT::init_(){
	activatedPin_= 7;
	activatePin_(activatedPin_);
}
IRPT::IRPT(){
	init_();
}

IRPT::IRPT(uint8_t pin){
	activatedPin_= pin;
	activatePin_(activatedPin_);
}

uint8_t IRPT::read(){
	 return isHigh_();
}

 uint8_t IRPT::isHigh_() {
    return ((can().lecture(7)>>2) <3);
}
 void IRPT::activatePin_(uint8_t pin){
     // select the port letter
     switch(pin){
        case '0':
            DDRA &= ~0x01;
            break;
        case '1':
            DDRA &= ~0x02;
            break;
        case '2':
            DDRA &= ~0x04;
            break;
        case '3':
            DDRA &= ~0x08;
            break;
        case '4':
            DDRA &= ~0x10;
            break;
        case '5':
            DDRA &= ~0x20;
            break;
        case '6':
            DDRA &= ~0x40;
            break;
        case '7':
            DDRA &= ~0x80;
            break;
     }
 }
 
 void IRPT::setPort(uint8_t newPin){
     // Set the new pins to OUTPUT (activate them)
	 activatedPin_= newPin;
	 activatePin_(activatedPin_);
 }


 #endif // __IRPT_CPP__