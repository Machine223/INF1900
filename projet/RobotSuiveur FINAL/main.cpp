#ifndef F_CPU
#define F_CPU 8000000
#endif
#include <avr/io.h>
#include <util/delay.h>

#include "clock.h"
#include "lectureBP.h"
#include "LED.h"
#include "tracker.h"

#include "stateFunction.h"

#define ERROR_CODE -1;
#define SUCCESS_CODE 0;



enum State
{
    C1 = 0,
    S2 = 1,
    PN = 2,
    S3 = 3,
    C2 = 4,
    S4 = 5,
    C3 = 6,
    S5 = 7,
    DN = 8,
    DNEND = 9,
    PA = 10,
    S6 = 11,
    C4 = 12,
    END = 13,
    START = 14,
    USELESSBUTNEEDED = 15
};

State etat = S3;

volatile State EtatRobot = etat;
volatile State FirstState = etat;
volatile bool haveBeenPressed = false;
LED greenLED("B0");        //Debug green
LED redLED("B1");          //Debug red
LectureBP principalReader; //use getBP() on this as a fail safe.

void blink(int time){
    redLED.turnON();
    _delay_ms(500);
    redLED.turnOFF();
}

void init()
{
    DDRD = 0xff ^ 0x04;
    clock::setTimerCTC(1600, 1);
}

int main()
{
    init();

    stateFunction states;
    states.calibrer();
    while(!(PIND & 0x04)){
        states.readCapteurs();
    }

    
    
    while (true)
    {
        
        //END : Robot s'arrête + son aigue 2s
        //S2 : Faire les sons quand il faut sur les points (à vérifier)
        //C4 : Lorsqu'il rentre et lorsqu'il sort d'une boîte : emmetre deux sons aigue de 50ms séparés de 20ms. 
        
        states.readCapteurs();

        switch (EtatRobot)
        {
        case C1:
            if (states.c1(FirstState != C1))
                EtatRobot = S2;
            blink(500);
            // if (FirstState == START)
            //     FirstState = C1; 
            
        case S2:
            if (states.s2())
                EtatRobot = PN;
            blink(500);
        case PN:
            if (states.pn())
                EtatRobot = S3;
            blink(500);
        case S3:
            if (states.s3())
                EtatRobot = C2;
            blink(500);
        case C2:
            if (states.c2(FirstState != C2))
                EtatRobot = S4;
            blink(500);
            // if (FirstState == START)
            //     FirstState = C2;
        case S4:
            if (states.s4())
                EtatRobot = C3;
            blink(500);
        case C3:
            if (states.c3(FirstState != C3))
                EtatRobot = S5;
            blink(500);
            // if (FirstState == START)
            //     FirstState = C3;
        case S5:
            if (states.s5())
                EtatRobot = DN;
            blink(500);
        case DN:
            if (states.dn())
                EtatRobot = DNEND;
            blink(500);
        case DNEND:
            if (states.dnend())
                EtatRobot = PA;
            blink(500);
        case PA:
            if (states.pa())
                EtatRobot = S6;
            blink(500);
        case S6:
            if (states.s6())
                EtatRobot = C4;
            blink(500);
        case C4:
            if (states.c4(FirstState != C4))
                EtatRobot = C1;
            blink(500);
            // if (FirstState == START)
            //     FirstState = C4;
        case END:
            states.end();
        case START:
            states.start();
        case USELESSBUTNEEDED:
        default:
            break;
        }
    }
    return SUCCESS_CODE;
}

ISR(TIMER1_COMPA_vect)
{ //dont ever touch this, system clock is working
    clock::sysClock++;
}

ISR(INT0_vect)
{                  //use as a fail safe can add thing for s3 in this
    _delay_ms(20); // Debounce
    if (PIND & 0x04)
    { // if it's still pressed
        principalReader.increment();
        if (EtatRobot == S5 || EtatRobot == DNEND)
            haveBeenPressed = true;
    }
}