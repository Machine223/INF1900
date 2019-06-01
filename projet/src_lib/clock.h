#ifndef __CLOCK_H__
#define __CLOCK_H__
#ifndef F_CPU
#define F_CPU 8000000
#endif // !F_CPU
#define A 'a'                // clock side A
#define B 'b'                // clock side B
// C/avr libraries
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
// Personnalized libraries
//#include "debug.h"
namespace clock
{
        void ajustementPWM (uint8_t val);
        static volatile unsigned int sysClock = 0;
        void setTimerGlobal();
        void setTimerCTC(int time, int timerNumber);
        void setPWM(int strength, int timerNumber);
    void setPWM(int strengthLeft, int strengthRight, int timerNumber);
};
#endif // __CLOCK_H__