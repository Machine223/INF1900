#include <avr/io.h>
#include "Memoire_24.h"

#ifndef UART_H
#define UART_H
class UART{
    public:
    UART(){init();}
    void MemoryToUart(char data);
    void MemoryToUart(char* data,int size);
    uint8_t UartToMemory(const uint16_t address);
    private:
    void init(void);
};
#endif //UART_H


