#ifndef __LED_H__
#define __LED_H__

// CPU CLOCK SPEED
#ifndef F_CPU
# define F_CPU 8000000UL
#endif

#define ON true
#define HIGH true
#define OFF false
#define LOW false

// C/avr libraries
#include <avr/io.h>

// Personnalized libraries
#include "debug.h"


class LED{
protected:
    char * PORT_;
    bool ON_;

    void init_();
    void initPort_(char * PORT);
    void activatePins_(char * PORT);
    void deactivatePins_(char * PORT);

    
public:
    LED();
    LED(char port[]);
    ~LED();

    bool isON();                    // if it's ON(true) or OFF(false)
    void set(bool newState);        // turn it ON(true) or OFF(false)
    void turn(bool newState);
    void turnON();                  // turn it ON
    void turnOFF();                 // turn it OFF
    
    void setPort(char * newPort);   // set the LED's active PORT
};




#endif // __LED_H__