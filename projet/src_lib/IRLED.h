 #ifndef __IRLED_H__
 #define __IRLED_H__

 // CPU CLOCK SPEED
 #ifndef F_CPU
 # define F_CPU 8000000UL
 #endif

 // C/avr libraries
 #include <avr/io.h>

// Personnalized Libraries
#include "LED.h"
#include "clock.h"

 // personnalized 
 class IRLED : public LED {
 private:
    // FROM LED
    // char * PORT_;
    // bool ON_;

    // virtual void init_();
    // virtual void initPort_(char * PORT);
    // virtual void activatePins_(char * PORT);
    // virtual void deactivatePins_(char * PORT);

    
 public: 
    IRLED();
    
    void set(bool newState);
    void turn(bool newState);
    void turnON();
    void turnOFF();
 };


 #endif //__IRPT_CPP__