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

State etat = START;

volatile State EtatRobot = etat;
volatile State FirstState = START;
volatile bool haveBeenPressed = false;
LED greenLED("B0");        //Debug green
LED redLED("B1");          //Debug red
LectureBP principalReader; //use getBP() on this as a fail safe.

void blink(int time){
    for(int i = 0 ; i< time ; i++){
    redLED.turnON();
    _delay_ms(250);
    redLED.turnOFF();
    _delay_ms(200);
    }
}

void init()
{
    DDRD = 0xff ^ 0x04;

    //clock::setTimerCTC(1600, 1); FAIT PLANTER LE PROGRAMME
}

int main()
{
    init();

    stateFunction states;
    SIRC signal;
    int valeur=0;
    do{
    valeur = signal.getCommand();
    }while (!(valeur <= 4 && valeur >= 1));
    switch(valeur){
        case 1: {EtatRobot = C1; FirstState = C1; break;}
        case 2: {EtatRobot = C2; FirstState = C2; break;}
        case 3: {EtatRobot = C3; FirstState = C3; break;}
        case 4: {EtatRobot = C4; FirstState = C4; break;}
    }
    // TODO faire un code avec interrup pour failsafe 
    // while(!(PIND & 0x04)){
    //     states.readCapteurs();
    // }
    
    while (EtatRobot != END)
    {   
        //END : Robot s'arrête + son aigue 2s
        //S2 : Faire les sons quand il faut sur les points (à vérifier)
        //C4 : Lorsqu'il rentre et lorsqu'il sort d'une boîte : emmetre deux sons aigue de 50ms séparés de 20ms. 
        
        states.readCapteurs();

        switch (EtatRobot)
        {
        case C1:{ 
            blink(1);
            // if (FirstState == START)
            //     FirstState = C1; 
            if (states.c1(FirstState != C1))
                EtatRobot = S2;
           
            break;
            }
        case S2:{
            if (states.s2())
                EtatRobot = PN;
            //blink(500);
            break;
            }
        case PN:{
            if (states.pn())
                EtatRobot = S3;
            //blink(500);
            break;
            }
        case S3:{
            if (states.s3()){
                EtatRobot = C2;
                if(FirstState == EtatRobot)
                EtatRobot = END;
            }
            //blink(500);
            break;
            }
        case C2:{
            blink(2);
            if (FirstState == START)
                FirstState = C2;
            if (states.c2(FirstState != C2))
                EtatRobot = S4;
            break;
            }
        case S4:{
            if (states.s4()){
                EtatRobot = C3;
                if(FirstState == EtatRobot)
                EtatRobot = END;
            }
            //blink(500);
            break;
            }
        case C3:{
            blink(3);
            if (FirstState == START)
                FirstState = C3;
            if (states.c3(FirstState != C3))
                EtatRobot = S5;
            
            break;
            }
        case S5:{
            blink(5);
            if (states.s5())
                EtatRobot = DN;
            //blink(500);
            break;
            }
        case DN:{
            if (states.dn())
                EtatRobot = DNEND;
            //blink(500);
            break;
            }
        case DNEND:{
            if (states.dnend())
                EtatRobot = PA;
            //blink(500);
            break;
            }
        case PA:{
            if (states.pa())
                EtatRobot = S6;
            //blink(500);
            }
        case S6:{
            blink(2);
            if (states.s6()){
                EtatRobot = C4;
                if(FirstState == EtatRobot)
                EtatRobot = END;
            }
            break;
            }
        case C4:{
            blink(4);
            if (FirstState == START)
                FirstState = C4;
            if (states.c4(FirstState != C4)){
                EtatRobot = C1;
            if(FirstState == EtatRobot)
                EtatRobot = END;
            }
            break;
            }
        case END:{
            states.end();
            break;
            }
        case START:
            states.start();
            break;
        case USELESSBUTNEEDED:
        default:
            break;
        }
    }
    states.robot.setMotors(0, 0);

    Sonorite::jouerSonoriteSonAigu();
    _delay_ms(50);
    Sonorite::arreterSon();
    _delay_ms(20);
    Sonorite::jouerSonoriteSonAigu();
    _delay_ms(50);
    Sonorite::arreterSon();
    
    return SUCCESS_CODE;
}
//TODO A tester
// ISR(INT0_vect)
// {   //use as a fail safe can add thing for s3 in this
//     _delay_ms(20); // Debounce
//     if (PIND & 0x04){ // if it's still pressed
//         principalReader.increment();
//         if (EtatRobot == S5 || EtatRobot == DNEND)
//             haveBeenPressed = true;
//     }
// }
