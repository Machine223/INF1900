#ifndef __IRPTDIG__CPP__
 #define __IRPTDIG__CPP__
 #include "DIGIRPT.h"
IRPTDIG::IRPTDIG(){
        init_();
}
IRPTDIG::IRPTDIG(char* pin){
        activatedPin_= pin;
        activatePin_(activatedPin_);
}
uint8_t IRPTDIG::read(){
         return isHigh_();
}
 uint8_t IRPTDIG::isHigh_() {
     if (!(PINA & 0x80))
        return 1;
    return 0;
}
void IRPTDIG::deactivatePin_(char * PORT){
   // select the port letter
    switch(PORT[0]){
        case 'A':
        case 'a':
            // select the port number
            switch(PORT[1]){
                case '0':
                    DDRA |= 0x01;
                    break;
                case '1':
                    DDRA |= 0x02;
                    break;
                case '2':
                    DDRA |= 0x04;
                    break;
                case '3':
                    DDRA |= 0x08;
                    break;
                case '4':
                    DDRA |= 0x10;
                    break;
                case '5':
                    DDRA |= 0x20;
                    break;
                case '6':
                    DDRA |= 0x40;
                    break;
                case '7':
                    DDRA = 0x80;
                    break;
            }
            break;
        case 'B':
        case 'b':
            // select the port number
            switch(PORT[1]){
                case '0':
                    DDRB |= 0x01;
                    break;
                case '1':
                    DDRB |= 0x02;
                    break;
                case '2':
                    DDRB |= 0x04;
                    break;
                case '3':
                    DDRB |= 0x08;
                    break;
                case '4':
                    DDRB |= 0x10;
                    break;
                case '5':
                    DDRB |= 0x20;
                    break;
                case '6':
                    DDRB |= 0x40;
                    break;
                case '7':
                    DDRB |= 0x80;
                    break;
            }
            break;
        case 'C':
        case 'c':
            // select the port number
            switch(PORT[1]){
                case '0':
                    DDRC |= 0x01;
                    break;
                case '1':
                    DDRC |= 0x02;
                    break;
                case '2':
                    DDRC |= 0x04;
                    break;
                case '3':
                    DDRC |= 0x08;
                    break;
                case '4':
                    DDRC |= 0x10;
                    break;
                case '5':
                    DDRC |= 0x20;
                    break;
                case '6':
                    DDRC |= 0x40;
                    break;
                case '7':
                    DDRC |= 0x80;
                    break;
            }
            break;
        case 'D':
        case 'd':
            // select the port number
            switch(PORT[1]){
                case '0':
                    DDRD |= 0x01;
                    break;
                case '1':
                    DDRD |= 0x02;
                    break;
                case '2':
                    DDRD |= 0x04;
                    break;
                case '3':
                    DDRD |= 0x08;
                    break;
                case '4':
                    DDRD |= 0x10;
                    break;
                case '5':
                    DDRD |= 0x20;
                    break;
                case '6':
                    DDRD |= 0x40;
                    break;
                case '7':
                    DDRD |= 0x80;
                    break;
            }
            break;
        // There is no default, 
        // if no characters match,
        // do not activate anything
    }
}
void IRPTDIG::activatePin_(char * PORT){
    // select the port letter
    switch(PORT[0]){
        case 'A':
        case 'a':
            // select the port number
            switch(PORT[1]){
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
            break;
        case 'B':
        case 'b':
            // select the port number
            switch(PORT[1]){
                case '0':
                    DDRB &= ~0x01;
                    break;
                case '1':
                    DDRB &= ~0x02;
                    break;
                case '2':
                    DDRB &= ~0x04;
                    break;
                case '3':
                    DDRB &= ~0x08;
                    break;
                case '4':
                    DDRB &= ~0x10;
                    break;
                case '5':
                    DDRB &= ~0x20;
                    break;
                case '6':
                    DDRB &= ~0x40;
                    break;
                case '7':
                    DDRB &= ~0x80;
                    break;
            }
            break;
        case 'C':
        case 'c':
            // select the port number
            switch(PORT[1]){
                case '0':
                    DDRC &= ~0x01;
                    break;
                case '1':
                    DDRC &= ~0x02;
                    break;
                case '2':
                    DDRC &= ~0x04;
                    break;
                case '3':
                    DDRC &= ~0x08;
                    break;
                case '4':
                    DDRC &= ~0x10;
                    break;
                case '5':
                    DDRC &= ~0x20;
                    break;
                case '6':
                    DDRC &= ~0x40;
                    break;
                case '7':
                    DDRC &= ~0x80;
                    break;
            }
            break;
        case 'D':
        case 'd':
            // select the port number
            switch(PORT[1]){
                case '0':
                    DDRD &= ~0x01;
                    break;
                case '1':
                    DDRD &= ~0x02;
                    break;
                case '2':
                    DDRD &= ~0x04;
                    break;
                case '3':
                    DDRD &= ~0x08;
                    break;
                case '4':
                    DDRD &= ~0x10;
                    break;
                case '5':
                    DDRD &= ~0x20;
                    break;
                case '6':
                    DDRD &= ~0x40;
                    break;
                case '7':
                    DDRD &= ~0x80;
                    break;
            }
            break;
    }
}
 
 void IRPTDIG::setPort(char* newPin){
     // Set the new pins to OUTPUT (activate them)
     deactivatePin_(activatedPin_);
         activatedPin_= newPin;
         activatePin_(activatedPin_);
 }
 void IRPTDIG::init_(){
        activatedPin_= "A7";
        activatePin_(activatedPin_);
}
 #endif // __IRPT_DIG_CPP__