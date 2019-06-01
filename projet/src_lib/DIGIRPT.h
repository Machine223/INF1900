  #ifndef __IRPTDIG__H__
 #define __IRPTDIG__H__
 // CPU CLOCK SPEED
 #ifndef F_CPU
 # define F_CPU 8000000UL
 #endif
 // C/avr libraries
 #include <avr/io.h>
 class IRPTDIG{
 private:
    char* activatedPin_;
    void activatePin_(char* pin);   
    void deactivatePin_(char* pin);
    void init_();
    uint8_t isHigh_();
 public:
    IRPTDIG();         // take D2 as a default pin 
    IRPTDIG(char* pin);         // Give pin as string in parameter 
    
    void setPort(char* newPin);   // Activate a specific pin and disactivate the old if changed
    uint8_t read();
 };
 #endif //__IRPT_DIG__H__