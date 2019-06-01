#ifndef __MCU_H__
#define __MCU_H__

// CPU CLOCK SPEED
#ifndef F_CPU
# define F_CPU 8000000UL
#endif

// C/avr libraries
#include <avr/io.h>
#include <avr/interrupt.h>
// Personnalized libraries
#include "pins.h"
#include "clock.h"

class MCU {
private:
	void init();
	uint8_t clockNumber;

public:
	MCU();
	void setMotors(int16_t leftSpeed,
		int16_t rightSpeed);    // sets speed manually : {left speed}, {right speed} 

protected:
};

#endif // __MCU_H__