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
#define NORMAL 95 // 90
#define SLOW 85   // 75

// Different lectures
#define ERROR -1
#define LINE 0
#define LEFT_LINE 1
#define RIGHT_LINE 2
#define BLACK_LINE 3
#define WHITE_LINE 4
#define RIGHT 'r'
#define LEFT 'l'

// Methods
// bool AllDown(){
//     return (!tracker.capteurs[0] && !tracker.capteurs[1] && !tracker.capteurs[2] && !tracker.capteurs[3]&&  !tracker.capteurs[4]);
// }

class stateFunction
{

private:
    // Variables
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

    //c1
    int signal_; // signal de la cummunication IR
    void ZigZagMag(); // Il cherche la ligne en balayant
    int waitForSignal(); // Attend pour un signal pour les points
    bool goHorizontal(uint8_t Horizontal); //go to the specific point on x
    bool goVertical(uint8_t Vertical); // go to the specific point on y
    void moveForward(int time); // avance
    void turnLeft(int Angle); // tourne a 90 degree a gauche
    void turnRight(int Angle); // tourne a 90 degree a droite
    void halt(); // stop
    void searchForPoint(uint8_t point); // aller au point specifie par l emmetteur
    void goToWhiteLine(); // arrive a la fin de la ligne
    void gotoPN(int dotNumber);

    //c3
    int compteur;
    int tableau[4];
    bool BEG;
    uint8_t index;
    int compteurFin;
    bool RIGHT_;
    bool LEFT_;
    void sideLineCalcul();
    bool AllDown();
    bool AllUp();

    // MISC
    void computeDIR();

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
    bool isWhiteLine();


    // !MISC

public:
    MCU robot;
    
    stateFunction()
    {
        sum = 0;
        nb_Inputs = 0;
        compteur = 0;
        BEG = false;
        index = 0;
        compteurFin = 0;
        signal_ = 0;
        RIGHT_ = false;
        LEFT_ = false;
        DEL[0].setPort("A6");
        DEL[1].setPort("C6");
        DEL[2].setPort("C7");
        DEL[3].setPort("C0");
        DEL[4].setPort("C1");
        calibrer();
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
