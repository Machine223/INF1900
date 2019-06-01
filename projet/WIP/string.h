#ifndef __STRING_H__
#define __STRING_H__

// CPU CLOCK SPEED
#ifndef F_CPU
# define F_CPU 8000000UL
#endif

// C/avr libraries
#include <avr/io.h>

// Personnalized libraries
#include "debug.h"


class string{

    char * char_ptr_;
    uint16_t size_;

public:
    string();
    string(char data[], uint16_t size);

    char* getData();
    void setData(char data[], uint16_t size);

    uint16_t getSize();

    void clear();

};

#endif // __STRING_H__