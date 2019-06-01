#ifndef __DEBUG_H__
#define __DEBUG_H__

// SET CLOCK SPEED
#ifndef F_CPU
# define F_CPU 8000000UL
#endif

// Personnalized libraries
#include "uart.h"

// DEBUG DEFINITIONS
#define DEBUG
#define ERRORLIB1900
#define WARNINGLIB1900
#define MISUSEDLIB1900

// Personalized variables
void dev_warn(char char_arr[], int size);
void dev_err(char char_arr[], int size);
void dev_mul(char char_arr[], int size);

#endif // __DEBUG_H__