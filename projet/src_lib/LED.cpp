#ifndef __LED_CPP__
#define __LED_CPP__

#include "LED.h"


LED::LED(){
}

LED::LED(char port[]){
    init_();
    initPort_(port);
}

void LED::init_() {
    PORT_ = 0;
    ON_ = false;
}

void LED::initPort_(char * PORT){
    // Set the new pins to OUTPUT (activate them)
    PORT_ = PORT;
    activatePins_(PORT_);
}

void LED::activatePins_(char * PORT){
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
                    DDRA |= 0x80;
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
    ON_ = false;
}

void LED::deactivatePins_(char * PORT){
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
        // There is no default, 
        // if no characters match,
        // do not activate anything
    }
    ON_ = false;
}

bool LED::isON(){
    return ON_;
}

void LED::set(bool newState){
    if (newState == true){
        turnON();
    }
    else
    {
        turnOFF();
    }
}

void LED::turn(bool newState){
    set(newState);
}

void LED::turnON(){
    // select the port letter
    switch(PORT_[0]){
        case 'A':
        case 'a':
            // select the port number
            switch(PORT_[1]){
                case '0':
                    PORTA |= 0x01;
                    break;
                case '1':
                    PORTA |= 0x02;
                    break;
                case '2':
                    PORTA |= 0x04;
                    break;
                case '3':
                    PORTA |= 0x08;
                    break;
                case '4':
                    PORTA |= 0x10;
                    break;
                case '5':
                    PORTA |= 0x20;
                    break;
                case '6':
                    PORTA |= 0x40;
                    break;
                case '7':
                    PORTA |= 0x80;
                    break;
            }
            break;
        case 'B':
        case 'b':
            // select the port number
            switch(PORT_[1]){
                case '0':
                    PORTB |= 0x01;
                    break;
                case '1':
                    PORTB |= 0x02;
                    break;
                case '2':
                    PORTB |= 0x04;
                    break;
                case '3':
                    PORTB |= 0x08;
                    break;
                case '4':
                    PORTB |= 0x10;
                    break;
                case '5':
                    PORTB |= 0x20;
                    break;
                case '6':
                    PORTB |= 0x40;
                    break;
                case '7':
                    PORTB |= 0x80;
                    break;
            }
            break;
        case 'C':
        case 'c':
            // select the port number
            switch(PORT_[1]){
                case '0':
                    PORTC |= 0x01;
                    break;
                case '1':
                    PORTC |= 0x02;
                    break;
                case '2':
                    PORTC |= 0x04;
                    break;
                case '3':
                    PORTC |= 0x08;
                    break;
                case '4':
                    PORTC |= 0x10;
                    break;
                case '5':
                    PORTC |= 0x20;
                    break;
                case '6':
                    PORTC |= 0x40;
                    break;
                case '7':
                    PORTC |= 0x80;
                    break;
            }
            break;
        case 'D':
        case 'd':
            // select the port number
            switch(PORT_[1]){
                case '0':
                    PORTD |= 0x01;
                    break;
                case '1':
                    PORTD |= 0x02;
                    break;
                case '2':
                    PORTD |= 0x04;
                    break;
                case '3':
                    PORTD |= 0x08;
                    break;
                case '4':
                    PORTD |= 0x10;
                    break;
                case '5':
                    PORTD |= 0x20;
                    break;
                case '6':
                    PORTD |= 0x40;
                    break;
                case '7':
                    PORTD |= 0x80;
                    break;
            }
            break;
        // There is no default, 
        // if no characters match,
        // do not activate anything
    }
    ON_ = true;
}

void LED::turnOFF(){
    // select the port letter
    switch(PORT_[0]){
        case 'A':
        case 'a':
            // select the port number
            switch(PORT_[1]){
                case '0':
                    PORTA &= ~0x01;
                    break;
                case '1':
                    PORTA &= ~0x02;
                    break;
                case '2':
                    PORTA &= ~0x04;
                    break;
                case '3':
                    PORTA &= ~0x08;
                    break;
                case '4':
                    PORTA &= ~0x10;
                    break;
                case '5':
                    PORTA &= ~0x20;
                    break;
                case '6':
                    PORTA &= ~0x40;
                    break;
                case '7':
                    PORTA &= ~0x80;
                    break;
            }
            break;
        case 'B':
        case 'b':
            // select the port number
            switch(PORT_[1]){
                case '0':
                    PORTB &= ~0x01;
                    break;
                case '1':
                    PORTB &= ~0x02;
                    break;
                case '2':
                    PORTB &= ~0x04;
                    break;
                case '3':
                    PORTB &= ~0x08;
                    break;
                case '4':
                    PORTB &= ~0x10;
                    break;
                case '5':
                    PORTB &= ~0x20;
                    break;
                case '6':
                    PORTB &= ~0x40;
                    break;
                case '7':
                    PORTB &= ~0x80;
                    break;
            }
            break;
        case 'C':
        case 'c':
            // select the port number
            switch(PORT_[1]){
                case '0':
                    PORTC &= ~0x01;
                    break;
                case '1':
                    PORTC &= ~0x02;
                    break;
                case '2':
                    PORTC &= ~0x04;
                    break;
                case '3':
                    PORTC &= ~0x08;
                    break;
                case '4':
                    PORTC &= ~0x10;
                    break;
                case '5':
                    PORTC &= ~0x20;
                    break;
                case '6':
                    PORTC &= ~0x40;
                    break;
                case '7':
                    PORTC &= ~0x80;
                    break;
            }
            break;
        case 'D':
        case 'd':
            // select the port number
            switch(PORT_[1]){
                case '0':
                    PORTD &= ~0x01;
                    break;
                case '1':
                    PORTD &= ~0x02;
                    break;
                case '2':
                    PORTD &= ~0x04;
                    break;
                case '3':
                    PORTD &= ~0x08;
                    break;
                case '4':
                    PORTD &= ~0x10;
                    break;
                case '5':
                    PORTD &= ~0x20;
                    break;
                case '6':
                    PORTD &= ~0x40;
                    break;
                case '7':
                    PORTD &= ~0x80;
                    break;
            }
            break;
        // There is no default, 
        // if no characters match,
        // do not activate anything
    }
    ON_ = false;
}

void LED::setPort(char * newPort){
    // Reset the active pins to INPUT (deactivate them)
    deactivatePins_(PORT_);
    // Set the new pins to OUTPUT (activate them)
    initPort_(newPort);
}

LED::~LED(){
    deactivatePins_(PORT_);
}

#endif // __LED_CPP__