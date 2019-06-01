#include "uart.h"

#include <avr/io.h>
#ifndef UART_CPP
#define UART_CPP
void UART::init( void ) {
    // diminuer a 2400 bauds. Nous vous donnons la valeur des deux
    // vitesse bauds = frequence / 16*(UBR0+1)
    // premier registres pour vous éviter des complications

    UBRR0H = 0; // partie a gauche de 16 bits (8bits)

    UBRR0L = 0xCF; // partie a droite de 16 bits(8bits) = 207
    //8million /16*208
    // permettre la reception et la transmission par le UART0 on va activer les flags RXEN0 et TXEN0

    //UCSR0A |= (1<<MPCM0) ; 

    UCSR0B |= (1<<RXEN0)| (1<<TXEN0) ; // activer la reception activer la transmission

    // Format des trames: 8 bits, 1 stop bits, none parity

    UCSR0C |= (1<<UCSZ00)| (1<<UCSZ01)  ; // 8 bits
    UCSR0C &= 0b11000111; // usb0s a 0 1 stop bits upm00 upm01 a 0 none parity
}

void transmissionUART ( uint8_t donnee ) {
    /* Wait for empty transmit buffer */
    while ( !( UCSR0A & (1<<UDRE0)) );
    //quand le UDRE0 est a 1 on envoie l information , sinon while
    /* Put data into buffer, sends the data */
    UDR0 = donnee; // envoie au port RS323 a partir de UDR0 octet par octet 
}
unsigned char receive(){
    /* Wait for data to be received */
    while ( !(UCSR0A & (1<<RXC0)) );
    //quand le RXC0 est a 1 on envoie l information , sinon while

    /* Get and return received data from buffer */
    return UDR0;
}

void UART::MemoryToUart(char data){
    transmissionUART(data);
}

void UART::MemoryToUart(char* data,int size){
    uint8_t i;
    for ( i=0; i < size; i++ ) {
        transmissionUART ( data[i] );
    }
}
uint8_t UART::UartToMemory(const uint16_t address){
    Memoire24CXXX memory;
    uint8_t data =  receive();
    memory.ecriture(address,data);
    return data;
}
#endif // !UART_CPP
