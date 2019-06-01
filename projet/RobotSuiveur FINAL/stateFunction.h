#ifndef F_CPU
#define F_CPU 8000000
#endif

#include <avr/io.h>
#include <util/delay.h>
//#include "pins.h"
//#include "sonorite.h"
#include "tracker.h"
//#include "follower.h"
#include "LED.h"
#include "MCU.h"
#include "SIRC.h"
#include "sonorite.h"
#include <stdbool.h>

#ifndef __STATEFUNCTION_H__
#define __STATEFUNCTION_H__

// Different speeds
#define FAST 150  // 150
#define NORMAL 110 // 90
#define SLOW 80   // 75

// Different lectures
#define ERROR -1
#define LINE 0
#define LEFT_LINE 1
#define RIGHT_LINE 2
#define BLACK_LINE 3
#define WHITE_LINE 4
#define RIGHT 'r'
#define LEFT 'l'


class stateFunction
{

private:
    // Variables
    MCU robot;
    SIRC sirc;

    Tracker tracker;
    bool p0Capteurs[5];
    bool p1Capteurs[5];
    bool p2Capteurs[5];
    bool p3Capteurs[5];
    bool p4Capteurs[5];
    int sum;
    int nb_Inputs;

    LED DEL[5];

    // That's a whole lot of variables to checkout
    // (if they must be here)

    //c3
    int compteur;
    int tableau[4];
    bool BEG;
    uint8_t index;
    int compteurFin;
    bool RIGHT;
    bool LEFT;

    // MISC
    void computeDIR();
    void pushCapteurs();
    bool previousIs(int arg, unsigned int count);

    void box();
    void followLine();
    void followCurve_Slow();
    bool findLine(char arg);
    void turnCorner();
    void pass(int arg);

    bool oneHot();
    bool isLeftCorner();
    bool isLeftLine();
    bool isRightLine();
    bool isBlackLine();
    bool isBlackLine(bool array[]);
    bool isWhiteLine();
    bool isWhiteLine(bool array[5]);

    int waitForSignal();
    void gotoPN(int dotNumber);
    // !MISC

public:
    stateFunction()
    {
        sum = 0;
        nb_Inputs = 0;
        compteur = 0;
        BEG = false;
        index = 0;
        compteurFin = 0;
        RIGHT = false;
        LEFT = false;
        DEL[0].setPort("A7");
        DEL[1].setPort("C6");
        DEL[2].setPort("C7");
        DEL[3].setPort("C0");
        DEL[4].setPort("C1");
    };

    int readCapteurs();
    void displayLED();

    void calibrer();
    bool c1(bool itNeedsToTurn);
    bool s2();
    bool pn();
    bool s3();
    bool c2(bool itNeedsToTurn);
    bool s4();
    bool c3(bool itNeedsToTurn);
    bool s5();
    bool dn();
    bool dnend();
    bool pa();
    bool s6();
    bool c4(bool itNeedsToTurn);
    bool end();
    bool start();
};

#endif //