#ifndef DBUG_CPP
#include "uart.h"
#include "debug.h"

// DEBUG ERROR
#ifdef DEBUG
    #ifdef ERRORLIB1900
        #define ERROR_DISPLAY(x,y) displayMessageOverUSB.MemoryToUart(x,y)
    #endif // ERRORLIB1900
#endif // DEBUG

void dev_err(char char_arr[], int size){ 
    UART displayMessageOverUSB;
    #ifdef ERROR_DISPLAY
        ERROR_DISPLAY(char_arr, size);
    #endif // ERROR_DISPLAY
}


// DEBUG WARNING
#ifdef DEBUG
    #ifdef WARNINGLIB1900
        #define WARNING_DISPLAY(x,y) displayMessageOverUSB.MemoryToUart(x,y)
    #endif // WARNINGLIB1900
#endif // DEBUG

void dev_warn(char char_arr[], int size){
    UART displayMessageOverUSB;
    #ifdef WARNINGLIB1900
        WARNING_DISPLAY(char_arr, size);
    #endif // WARNINGLIB1900
}


// DEBUG MISS USED LIB
#ifdef DEBUG
    #ifdef MISUSEDLIB1900
        #define MISS_USED_DISPLAY(x,y) displayMessageOverUSB.MemoryToUart(x,y)
    #endif // MISUSEDLIB1900
#endif // DEBUG

void dev_mul(char char_arr[], int size){
    UART displayMessageOverUSB;
    #ifdef MISUSEDLIB1900
        MISS_USED_DISPLAY(char_arr, size);
    #endif // MISUSEDLIB1900
}

#endif // !DBUG_CPP