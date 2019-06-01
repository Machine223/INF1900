#ifndef __TRACKER_H__
#define __TRACKER_H__

//#include "tracker.h"
#include "MCU.h"
//#include "global.h"

enum followingType
{
  LIGNE = 0,
  COURBE = 1,
  RECTANGLE = 2,
  DROITE = 3
};

class Follower
{
public:
  Follower();
  bool followLine();       //use everywhere
  bool followCurve();      //use in s2
  bool followRectangle();  //use in s4
  bool followCenterLine(); //use for the line in s3 dans le circuit
private:
  const uint8_t slowSpeed_ = 70;  // 50% de la vitesse
  const uint8_t medSpeed_ = 100;  // 75% de la vitesse
  const uint8_t quickSpeed_ = 150; // 100% de la vitesse
  const uint8_t stopSpeed_ = 0;

  followingType currentDirection; // 
  bool currentState[5];
  //Tracker sensor;
  MCU robot;

};

#endif //__TRACKER_H__
