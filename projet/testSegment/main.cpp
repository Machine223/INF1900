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
#include <stdbool.h> 

// Different speeds
#define FAST 100
#define NORMAL 75
#define SLOW 25

// Different lectures
#define ERROR -1
#define LINE 0
#define LEFT_LINE 1
#define RIGHT_LINE 2
#define BLACK_LINE 3
#define WHITE_LINE 4

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

void displayLED(){
    for (int i = 0; i < 5; i++)
        DEL[i].set(tracker.capteurs[i]);
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
void setDel(){
    DEL[4].setPort("C7"); 
    DEL[3].setPort("C6");  
    DEL[2].setPort("C1");  
    DEL[1].setPort("C0");  
    DEL[0].setPort("A6");  
    calibrer();
}
/*
void C2(){

    if (sum > 5){
        robot.setMotors(SLOW, NORMAL);
    }
    else if (sum == 5){
        ro0bot.setMotors(NORMAL, NORMAL);
    }
    else if(sum < 5){    
        robot.setMotors(NORMAL, SLOW);
    }
    else if (sum == 0){
        robot.setMotors(SLOW, NORMAL);
    }

    // END OF MOVE ON A LINE
    if(nb_Inputs != 0){
        robot.setMotors(NORMAL, NORMAL);
    }
    else if (sum == 0){
        robot.setMotors(SLOW, NORMAL);
    }
}
*/

int readCapteurs(){
    int VALUE = ERROR;
    if(tracker.lecture()){



    }
    return VALUE;
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

void pass(int arg){
    while(readCapteurs() == arg)
        robot.setMotors(NORMAL, NORMAL);
}

void C4(){
    bool isInRectangle = false;             
}

bool oneUp(){
    return (!tracker.capteurs[0] && !tracker.capteurs[1] && !tracker.capteurs[2] && !tracker.capteurs[3]&&  tracker.capteurs[4]) ||(!tracker.capteurs[0] && !tracker.capteurs[1] && !tracker.capteurs[2] && tracker.capteurs[3]&&  !tracker.capteurs[4]) || (!tracker.capteurs[0] && !tracker.capteurs[1] && tracker.capteurs[2] && !tracker.capteurs[3]&&  !tracker.capteurs[4]) || (!tracker.capteurs[0] && tracker.capteurs[1] && !tracker.capteurs[2] && !tracker.capteurs[3]&&  !tracker.capteurs[4]) || (tracker.capteurs[0] && !tracker.capteurs[1] && !tracker.capteurs[2] && !tracker.capteurs[3]&&  !tracker.capteurs[4]);
}


bool AllDown(){
    return (!tracker.capteurs[0] && !tracker.capteurs[1] && !tracker.capteurs[2] && !tracker.capteurs[3]&&  !tracker.capteurs[4]);
}


void C3(){   
    if (tracker.capteurs[0] && tracker.capteurs[1] && tracker.capteurs[2] && tracker.capteurs[3] && tracker.capteurs[4] && !BEG){
        compteur= 0;
       BEG = true;
       do{
           if(tracker.lecture())
        {
            //displayLED();
            sum=5;
            follow();
            //computeDIR();
        }
       }
       while(!oneUp());
    }
    if (BEG  && tracker.capteurs[0] && tracker.capteurs[1] && tracker.capteurs[2]  && !tracker.capteurs[3] && !tracker.capteurs[4] && !RIGHT){
        tableau[index++] =1;    // left 
        tableau[index++] =compteur;
        compteur=0;
        RIGHT = true;
         do{
               if(tracker.lecture())
            {
            //displayLED();
            sum=5;
            follow();
            //computeDIR();
            }
        }
       while(!oneUp());
    }
    if (BEG  && tracker.capteurs[2] && tracker.capteurs[3] && tracker.capteurs[4] && !tracker.capteurs[0] && !tracker.capteurs[1]&& !LEFT){
        tableau[index++] =2;        // right = 2
        tableau[index++] =compteur;
        compteur=0;
        LEFT = true;
         do{
            if(tracker.lecture())
            {
            //displayLED();
                sum=5;
                follow();
            //computeDIR();
            }
       }
       while(!oneUp());
    }
    compteur++;           
}


// ecrire routine de depart pour allumer tout les LED
int Section_3(){
    setDel();
    bool running = true;
    while (running)
    {
        if(tracker.lecture())
        {
            displayLED();
            computeDIR(); 
            follow() ;
            C3();
            if(LEFT && RIGHT && BEG){
                running = false;
            }
        }
    }
    while (!AllDown()){
        if(tracker.lecture())
        {
        computeDIR(); 
        displayLED();
        follow();
        }
    };
    robot.setMotors(0, 0);
    for (int i = 0 ; i<5 ; i++){
        DEL[i].turnOFF();
        _delay_ms(50);
    }
             
    if (tableau[0] == 1 && tableau[2] == 2 ){ // Rouge
        if (double(tableau[3]/tableau[1]) < 1.2) //D2
        {
            DEL[1].turnON();
            _delay_ms(20000);
        }
        else{
            DEL[0].turnON();
            _delay_ms(20000);
        }
    }
    else{ 
            if (double(tableau[3]/tableau[1]) < 1.2) //D2
            {
                DEL[3].turnON();
                _delay_ms(20000);
            }
            else{
                DEL[2].turnON();
                _delay_ms(20000);
            }
        }
    return 0;
}
int main(){
    Section_3();
}