#ifndef __PINS_H__
#define __PINS_H__
 
// PINS commented are not used by US
// PINS uncommented must be assigned a new name
// Please keep indentation

#define LED0        PINA0  // FREE THEM NIPPLES (TEST) IR1 Tracker sensor
#define LED1        PINA1  // FREE THEM NIPPLES (TEST) IR2 Tracker sensor
#define LED2        PINA2  // FREE THEM NIPPLES (TEST) IR3 Tracker sensor
#define LED3        PINA3  // FREE THEM NIPPLES (TEST) IR4 Tracker sensor
#define LED4        PINA4  // FREE THEM NIPPLES (TEST) IR5 Tracker sensor
#define LED5        PINA5  // FREE THEM NIPPLES (TEST)
#define LED6        PINA6  // FREE THEM NIPPLES (TEST)
#define LED7        PINA7  // FREE THEM NIPPLES (TEST)
 
//#define             PINB0   
//#define             PINB1   
#define LEFTMOTOR1  PINB2  
#define RIGHTMOTOR0 PINB3   // 0C0A
#define LEFTMOTOR0  PINB4   // OC0B
#define RIGHTMOTOR1 PINB5   
//#define             PINB6   
//#define             PINB7   

//#define             PINC0   // MEMORY - SCL (USB)
//#define             PINC1   // MEMORY - SDA (USB)
//#define             PINC2   // MEMORY
//#define             PINC3   // MEMORY
//#define             PINC4   // MEMORY
//#define             PINC5   // MEMORY
//#define             PINC6   // MEMORY
//#define             PINC7   // MEMORY

//#define LEFTMOTOR0  PIND0   // DCMOTOR LEFT - RXD0
//#define RIGHTMOTOR0 PIND1   // DCMOTOR RIGHT - TXD0
//#define LEFTMOTOR1  PIND2   // DCMOTOR LEFT - INT0 - RXD1
//#define RIGHTMOTOR1 PIND3   // DCMOTOR RIGHT - INT1 - TXD1
#define CLK1B       PIND4   // OC1B
#define CLK1A       PIND5   // OC1A
#define CLK2B       PIND6   // OC2B 
#define CLK2A       PIND7   // OC2A 

#endif // __PINS_H__