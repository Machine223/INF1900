// #ifndef __DLED_CPP__
// #define __DLED_CPP__

// #include "DLED.h"

// void DLED::init_(){
//     greenPORT = 0;
//     redPORT = 0;
// }

// void DLED::initPort_(char * PORT, char color){
//     //if (color == GREEN)
        
//     //else if (color == RED)

// }

// DLED::DLED(){
//     init_();
// }

// DLED::DLED(char redPORT[], char greenPORT[]){
//     init_();
//     setPort(greenPORT, GREEN);
//     setPort(redPORT, RED);
// }

// DLED::~DLED(){

// }


// bool DLED::isON(){
//     return (greenLED.isON() || redLED.isON());
// }

// bool DLED::isON(char color){
//     if (color == GREEN)
//         return greenLED.isON();
//     else if (color == RED)
//         return redLED.isON();
//     return false;
// }

// bool DLED::isGreenON(){
//     return greenLED.isON();
// }

// bool DLED::isRedON(){
//     return redLED.isON();
// }

// void DLED::set(char color){
//     if (color == GREEN)
//         turnGreenON();
//     else if (color == RED)
//         turnRedON();
// }

// void DLED::turnGreenON(){
//     redLED.turn(OFF);
//     greenLED.turn(ON);
// }

// void DLED::turnGreen(bool newState){
//     if (newState)
//         redLED.turn(OFF);
//     greenLED.set(newState);
// }

// void DLED::turnRedON(){
//     greenLED.turn(OFF);
//     redLED.turn(ON);
// }

// void DLED::turnRed(bool newState){
//     if (newState)
//         greenLED.turn(OFF);
//     redLED.set(newState);
// }

// void DLED::turnOFF(){
//     redLED.turn(OFF);
//     greenLED.turn(OFF);
// }


// char * DLED::getGreenPort(){
//     return greenPORT;
// }

// char * DLED::getRedPort(){
//     return redPORT;
// }

// void DLED::setPorts(char newGreenPort[], char newRedPort[]){
//     setPort(newGreenPort, GREEN);
//     setPort(newRedPort, RED);
// }

// void DLED::setPort(char newPort[], char color){
//     if (color == GREEN){
//         greenPORT = newPort;
//         greenLED.setPort(greenPORT);
//     }
//     else if (color == RED){
//         redPORT = newPort;
//         redLED.setPort(redPORT);
//     }
// }

// #endif // __DLED_CPP__