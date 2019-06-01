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
#include "SIRC.h" 
#include "MCU.h"
#include <stdbool.h> 

// Different speeds
#define SPEED 120

#define FAST 103
#define NORMAL 75
#define SLOW 25

// Different lectures
#define ERROR -1
#define LINE 0
#define LEFT_LINE 1
#define RIGHT_LINE 2
#define BLACK_LINE 3
#define WHITE_LINE 4

#define LEVEL1 880
#define LEVEL2 100
#define LEVEL3 100
#define WIDTH_LINE  12

// Variables
MCU robot;
Tracker tracker;
LED DEL[5];

int sum=0;
int nb_Inputs=0;
//c3
int compteur = 0; 
int tableau[4]; 
bool BEG= false; 
uint8_t index = 0; 
int compteurFin =0; 
bool RIGHT = false;
bool LEFT = false;


// Methods
void calibrer(){
    if (tracker.calibrer())
    {
        for (int i = 0; i < 5; i++) {
            DEL[i].turnON();
            _delay_ms(100);
            DEL[i].turnOFF();
            _delay_ms(50);
        }
        for (int i = 4; 0 <= i; i--) {
            DEL[i].turnON();
            _delay_ms(100);
            DEL[i].turnOFF();
            _delay_ms(50);
        }
        
        for(int j = 0 ; j < 3 ; j++){
            for (int i = 0; i < 5; i++){
                DEL[i].turnON();
                _delay_ms(5);
            }
            _delay_ms(100);
            for (int i = 0; i < 5; i++){
                DEL[i].turnOFF();
                _delay_ms(5);
            }
            _delay_ms(100);
        }
    }
    else
    {
        for (int i = 0; i < 3; i++){
            DEL[1].turnON();
            _delay_ms(1000);
            DEL[1].turnOFF();
            _delay_ms(1000);    
        }
    }
}



void follow(){
    if (sum < 5){
        robot.setMotors(NORMAL,SLOW);
    }
    else if (sum == 5){
        robot.setMotors(NORMAL, NORMAL);
    }
    else if(sum > 5){    
        robot.setMotors(SLOW, NORMAL);
    }
   
}



void displayLED(){
    for (int i = 0; i < 5; i++)
        DEL[i].set(tracker.capteurs[i]);
}



bool oneUp(){
    tracker.lecture();
    return (!tracker.capteurs[0] && !tracker.capteurs[1] && !tracker.capteurs[2] && !tracker.capteurs[3]&&  tracker.capteurs[4]) ||(!tracker.capteurs[0] && !tracker.capteurs[1] && !tracker.capteurs[2] && tracker.capteurs[3]&&  !tracker.capteurs[4]) || (!tracker.capteurs[0] && !tracker.capteurs[1] && tracker.capteurs[2] && !tracker.capteurs[3]&&  !tracker.capteurs[4]) || (!tracker.capteurs[0] && tracker.capteurs[1] && !tracker.capteurs[2] && !tracker.capteurs[3]&&  !tracker.capteurs[4]) || (tracker.capteurs[0] && !tracker.capteurs[1] && !tracker.capteurs[2] && !tracker.capteurs[3]&&  !tracker.capteurs[4]);
}


bool AllDown(){
    tracker.lecture();
    return (!tracker.capteurs[0] && !tracker.capteurs[1] && !tracker.capteurs[2] && !tracker.capteurs[3]&&  !tracker.capteurs[4]);
}
bool AllUp(){
    tracker.lecture();
    return (tracker.capteurs[0] && tracker.capteurs[1] && tracker.capteurs[2] && tracker.capteurs[3]&&  tracker.capteurs[4]);
}

void avancer(){
    robot.setMotors(NORMAL,NORMAL);
    _delay_ms(1900);
    robot.setMotors(0,0);
    _delay_ms(250);
}

void avancerHorizontal(){
    robot.setMotors(NORMAL,NORMAL);
    _delay_ms(1070);
    robot.setMotors(0,0);
    _delay_ms(250);
}
void turn90(uint8_t right){
    if (right == 1){ // turn right
        robot.setMotors(FAST,-(FAST+5));
    }
    else { //turn left
        robot.setMotors(-(FAST+5),FAST);
    }
    _delay_ms(1200);
    robot.setMotors(0,0);
    _delay_ms(100);
}


/*void section1(uint8_t point){
    uint8_t deltaX = (2-(point-1)%3)+2;
    uint8_t deltaY = (2-(point-1)/3)+1;

    for(int i = 0; i < deltaY; i++){
        avancer();
    }
    robot.setMotors(NORMAL,NORMAL+5);
    _delay_ms(500);
    robot.setMotors(0,0);
    _delay_ms(200);
    turn90(0);
    _delay_ms(200);
    for(int i = 0; i < deltaX; i++){
        avancerHorizontal();
    }
    _delay_ms(250);
    
    turn90(1);
    _delay_ms(250);
    robot.setMotors(NORMAL,NORMAL+5);
    _delay_ms(100);
    robot.setMotors(0,0);
    turn90(1);
    _delay_ms(250);


    for(int i = 0; i < deltaX; i++){
        avancerHorizontal();
    }
    _delay_ms(250);
        turn90(0);
    _delay_ms(250);

    for(int i = 0; i < (4-deltaY); i++){
        //balayage();
        robot.setMotors(NORMAL,NORMAL+5);
        _delay_ms(500);
    }

    //PORTC = 0;
    robot.setMotors(0,0);
    _delay_ms(100);
}*/


void section1_9(uint8_t point){
    uint8_t deltaX = (2-(point-1)%3)+2;
    uint8_t deltaY = (2-(point-1)/3)+1;

    for(int i = 0; i < deltaY; i++){
        avancer();
    }
    robot.setMotors(NORMAL,NORMAL+5);
    _delay_ms(1200);
    robot.setMotors(0,0);
    _delay_ms(200);
    turn90(0);
    _delay_ms(200);
    for(int i = 0; i < deltaX; i++){
        avancerHorizontal();
    }
    _delay_ms(250);
    
    turn90(1);
    _delay_ms(250);
    robot.setMotors(NORMAL,NORMAL+5);
    _delay_ms(100);
    robot.setMotors(0,0);
    turn90(1);
    _delay_ms(250);


    for(int i = 0; i < deltaX; i++){
        avancerHorizontal();
    }
    _delay_ms(250);
        turn90(0);
    _delay_ms(250);

    for(int i = 0; i < (4-deltaY); i++){
        //balayage();
        avancer();
    }

    //PORTC = 0;
    robot.setMotors(0,0);
    _delay_ms(100);
}

void section1_1(uint8_t point){
    uint8_t deltaX = (2-(point-1)%3)+2;
    uint8_t deltaY = (2-(point-1)/3)+1;

    for(int i = 0; i < deltaY; i++){
        avancer();
    }
    robot.setMotors(NORMAL,NORMAL+5);
    _delay_ms(1000);
    turn90(0);
    _delay_ms(100);

    for(int i = 0; i < deltaX; i++){
        avancerHorizontal();
    }
       avancerHorizontal();
    _delay_ms(250);
    
    turn90(1);
    _delay_ms(250);

    turn90(1);
    _delay_ms(250);


    for(int i = 0; i < deltaX; i++){
        avancerHorizontal();
    }
    _delay_ms(250);
    turn90(0);
    _delay_ms(250);

    for(int i = 0; i < (4-deltaY); i++){
        avancer();
    }

    //PORTC = 0;
    robot.setMotors(0,0);
    _delay_ms(100);
}

void section1_5(uint8_t point){
    uint8_t deltaX = (2-(point-1)%3)+2;
    uint8_t deltaY = (2-(point-1)/3)+1;

    for(int i = 0; i < deltaY; i++){
        //balayage();
        avancer();
    }
    robot.setMotors(NORMAL,NORMAL+5);
    _delay_ms(800);
    turn90(0);
        _delay_ms(100);

    for(int i = 0; i < deltaX; i++){
        avancer();
    }
    _delay_ms(250);
    
    
    turn90(1);
    _delay_ms(250);

    turn90(1);
    _delay_ms(250);


    for(int i = 0; i < deltaX; i++){
        avancer();
    }
    _delay_ms(250);
    turn90(0);
    _delay_ms(250);

    for(int i = 0; i < (4-deltaY); i++){
        //balayage();
        avancer();
    }

    //PORTC = 0;
    robot.setMotors(0,0);
    _delay_ms(100);
}
void moveToPoint(uint8_t point){
switch (point){
    case 1:{}
    case 2:{}
    case 3:{section1_1(point); break;}
    case 4:{}
    case 5:{}
    case 6:{section1_5(point); break;}
    case 7:{}
    case 8:{}
    case 9:{section1_9(point); break;}
}
}
void setDel(){
    DEL[4].setPort("C7"); 
    DEL[3].setPort("C6");  
    DEL[2].setPort("C1");  
    DEL[1].setPort("C0");  
    DEL[0].setPort("A6");  
    calibrer();
}

void computeDIR(){
    sum=0;
    nb_Inputs=0;

    for (int i = 0 ; i<5 ; i++)
    {
        sum +=  tracker.capteurs[i] * ((2*i) +1);
        nb_Inputs += tracker.capteurs[i];
    }
    nb_Inputs != 0 ? sum /= nb_Inputs : sum = 0;
}
void goToEndLine(){
       while (!AllUp()){
        tracker.lecture();
        displayLED();
        computeDIR(); 
        follow();
}}
void goToWhiteLine(){
       while (!AllDown()){
        tracker.lecture();
        displayLED();
        computeDIR();
        if(sum < 5)
           robot.setMotors(NORMAL,NORMAL);   
         else
           follow();
        } 
}

// ecrire routine de depart pour allumer tout les LED
int Section_1(){
    DDRA = 0x00;
    //DDRB= 0x30;
    //PORTB &= ~(0x30);
    setDel();
    SIRC signal;
    int point = 0;
    while (!(point <10 && point>0))
        point = signal.getCommand();
    while (AllDown()){
        robot.setMotors(SLOW,FAST);
        tracker.lecture();
        displayLED();
    }
    goToEndLine();
        moveToPoint(point);
    goToWhiteLine();
    robot.setMotors(0, 0);
    return 0;
}
int main(){
    Section_1();
}   
