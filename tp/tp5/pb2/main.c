
#define F_CPU 8000000 
#include <avr/io.h> 
#include <util/delay.h> 
#include <avr/interrupt.h> //Controle avec Interrupts 
#include <stdbool.h> 

void initialisationUART ( void ) {

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
//quand le UDRE0 est a 1 on envoie linformation , sinon while
/* Put data into buffer, sends the data */
UDR0 = donnee; // envoie au port RS323 a partir de UDR0 octet par octet 
}
int main()
{

    char mots[21] = "Le robot en INF1900\n";

    initialisationUART();
    uint8_t i, j;

    for ( i = 0; i < 100; i++ ) {

        for ( j=0; j < 20; j++ ) {

        transmissionUART ( mots[j] );

        }

    }

}

