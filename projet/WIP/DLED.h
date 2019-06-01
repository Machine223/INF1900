// #ifndef __DLED_H__
// #define __DLED_H__

// // CPU CLOCK SPEED
// #ifndef F_CPU
// # define F_CPU 8000000UL
// #endif

// #define ON true
// #define HIGH true
// #define OFF false
// #define LOW false

// #define RED 'r'
// #define GREEN 'g'

// // C/avr libraries
// #include <avr/io.h>

// // Personnalized libraries
// #include "LED.h"
// #include "debug.h"


// class DLED {
// private:
//     LED greenLED();
//     char * greenPORT;
//     LED redLED();
//     char *redPORT;

//     void init_();
//     void initPort_(char*,char);
    
//     DLED();
// public:
//     DLED(char redPORT[], char greenPORT[]);
//     ~DLED();

//     bool isON();
//     bool isON(char color);
//     bool isGreenON();
//     bool isRedON();
//     void set(char color);
//     void turnGreenON();
//     void turnGreen(bool newState);
//     void turnRedON();
//     void turnRed(bool newState);
//     void turnOFF();
    
//     char * getGreenPort();
//     char * getRedPort();
//     void setPorts(char newGreenPort[], char newRedPort[]);
//     void setPort(char newPort[], char color);
// };




// #endif // __DLED_H__