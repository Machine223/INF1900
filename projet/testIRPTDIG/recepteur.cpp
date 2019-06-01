#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include "LED.h"
#include "Memoire_24.h"
#include "uart.h"
#include <stdbool.h> 

#include "DIGIRPT.h"
#include "SIRC.h"
#include "uart.h"

int main (){
    DDRA = 0x00;
    DDRB =0xff;  
    SIRC Recepteur;
    UART uart;
    uint8_t valeur = 0;
    valeur = Recepteur.getCommand();
    uart.MemoryToUart(valeur);
    PORTB=0x01;
    return 0;
}