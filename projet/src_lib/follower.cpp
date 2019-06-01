#ifndef __TRACKER_CPP__
#define __TRACKER_CPP__

#include "follower.h"

Follower::Follower(){
    //sensor.calibrer();
}

bool Follower::followLine(){  
    // Go forward 
    DDRB = 0xff;
    

    int sum=0;
    int nb_Inputs=0;
    for (int i = 0 ; i<5 ; i++)
    {
        //currentState[i] = GLOBAL::Capteurs[i];
        sum +=  currentState[i] * ((2*i) +1);
        nb_Inputs += currentState[i];
    }
    if (nb_Inputs == 0){
        //return false;
    }
    sum /=nb_Inputs;
    
    if (sum < 5){
        robot.setMotors(20,100);
    }
    if (sum == 5){
        robot.setMotors(100,100);
    }
    if(sum > 5)
    {
        robot.setMotors(100,20);
    }
    return true;
  }


  #endif //__TRACKER_CPP__

  