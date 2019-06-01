/* MCU.cpp */
#ifndef MCU_CPP
#define MCU_CPP

#include "MCU.h"


MCU::MCU(){init();}

void MCU::init()
{
	clockNumber = 0;

	// Initializing the motor pins as output
	DDRB |= (1 << LEFTMOTOR0);
	DDRB |= (1 << LEFTMOTOR1);
	DDRB |= (1 << RIGHTMOTOR0);
	DDRB |= (1 << RIGHTMOTOR1);
}

void MCU::setMotors(int16_t leftSpeed, int16_t rightSpeed){
	cli();
		_delay_ms(10);
		if(leftSpeed <= 0){
			leftSpeed *= -1;
			PORTB |= (1 << LEFTMOTOR1);
		}else{
			PORTB &= ~(1 << LEFTMOTOR1);
		}
		if(rightSpeed <= 0){
			rightSpeed *= -1;
			PORTB |= (1 << RIGHTMOTOR1);
		}else{
			PORTB &= ~(1 << RIGHTMOTOR1);
		}
		clock::setPWM(leftSpeed,rightSpeed,clockNumber);
	sei();
}



#endif