#ifndef __SIRC_CPP__
#define __SIRC_CPP__
#include "SIRC.h"

void SIRC::init_(){
//    DDRB|=0x03;
    BEG = 0xAA;
    END = 0xFF;
}
SIRC::SIRC(){
    init_();
}
SIRC::SIRC(IRLED outputLED){
    led = outputLED;
}
// Writing PART
void SIRC::write(uint8_t data, uint8_t size){

    clock::ajustementPWM(104);
    // data is the data to be transmitted
    // size is the length of the data to be transmitted: 12, 15  or 20 bits.
    writeSTART_();
    for (uint8_t i = 0; i < COMMAND_DIMENSION; i++){
    write_(data & 1);             // write the LSB
    data = data >> 1;             // data is the same data, shifted one left (so that the next bit is the LSB)
    }
    write1_(); //TV Adress code
    for (uint8_t i = 0; i < size - COMMAND_DIMENSION; i++){
    write0_();             // write the LSB
    }
    writeEND_();
}
void SIRC::write_(bool bit){
    bit ? write1_() : write0_();
}
void SIRC::write1_(){
    // 1 (HIGH) is a 1.2ms HIGH and 0.6ms LOW pulse
    TCCR1A |= (1<<COM1A0); //Allow PWM, we could replace it with led.turnON() but it wastes time
    _delay_ms(1.2);
    TCCR1A &= ~(1<<COM1A0); //Stops PWM, we could replace it with led.turnOFF() but it wastes time
    _delay_ms(0.6);
}
void SIRC::write0_(){
    // 0 (LOW) is a 0.6ms HIGH and 0.6ms LOW pulse
    TCCR1A |= (1<<COM1A0); 
    _delay_ms(0.6);
    TCCR1A &= ~(1<<COM1A0);
    _delay_ms(0.6);
}
void SIRC::writeSTART_(){
    // Start is a 2.4ms HIGH and 0.6ms LOW pulse
    TCCR1A |= (1<<COM1A0); 
    _delay_ms(2.4);
    TCCR1A &= ~(1<<COM1A0);
    _delay_ms(0.6);
}
void SIRC::writeEND_(){
    // END is a 10.0ms+ LOW pulse
    TCCR1A &= ~(1<<COM1A0);
    _delay_ms(10);
}
// Reading PART
void SIRC::waitForBegginning_(){
    // waits for the start signal of the protocol
    while(readPulse_() != BEG);
}
int SIRC::readPulse_(){
    // Generally speaking, the read frequency is 40kHz
    // This is defined by the readFrequency variable
    // Seek for signal HIGH
    uint8_t index = 0; // calculate the width pulse
    while(IRReader.read() ==0){
        // if it's been more than 10ms, it's the END
        _delay_us(200);
        index ++;
        if (index == 45 )//(maxWait < clock::sysClock)
            return END;
    }
    index = 0;//int risingEdge = clock::sysClock;
    // Seek for signal LOW
    do{
        _delay_us(200);
        index ++;
    }
    while(IRReader.read()==1);
    //double diff = (clock::sysClock - risingEdge);
    // Get the relative percentages of success in order 
    // to identify the most probable signal received
    if(index>=10) // 10*0.2 = 2.0 +  ~0.2 ms execution time
        return BEG;
    else if (index>=5) // 5*0.2 = 1 ms +  ~0.2 wasted time
        return 1;
    else return 0;
    
    // [0] BEGINNING ~2.4ms
    // [1] HIGH (logical 1) ~1.2ms
    // [2] LOW (logical 0) ~0.6ms
}
uint8_t SIRC::getCommand(){
    return getSignal();
}
int SIRC::read(){
    int bytes = 0; //contains final result
    uint8_t index = 0; //define the protocole version 
    int nextBit=0 ; // contains the value returned by read Pulse(END,BEG,1,0) 
    waitForBegginning_(); // wait for the start signal
    while (true){
       nextBit = readPulse_();
        if (nextBit != END){
            bytes |= (nextBit << index); // shifts (the new bit) right by (total number of recieved bits)
            index++;                          
        }
        else{ // signal corresponds to the end signal
            PROTOCOLE_ = index; 
            return bytes; // return value
        }
    }
}
int SIRC::getSignal(){
    int binaryValues[VERIFICATION_NUMBER];
    //UART uart ;
    int decimalValue = 0;
    for(int i =0; i<VERIFICATION_NUMBER; i++ ){
        binaryValues[i] = read();
    }
    for(int i =0; i<VERIFICATION_NUMBER; i++ ){
            int base = 1; 
            int value = binaryValues[i];
            decimalValue =0;
            while (base!= 128) { 
                decimalValue += (value & 1)*base;
                value = value >> 1;   
                base = base * 2; 
            }
            base = 1;
            int adress = 0;
            int baseSeuil = 1;
            for (int i =0; i< (PROTOCOLE_- COMMAND_DIMENSION); i++) //Adress
                baseSeuil = baseSeuil*2;
            while (base!= baseSeuil) { 
                adress += (value&1)*base;
                value = value >> 1;   
                base = base * 2;
            }
            if(adress==1) 
                binaryValues[i] = decimalValue;
            else
                binaryValues[i] = 0;
    }
    int Occurency = 0; int maxOccurency=0;
    for(int i = 0; i < VERIFICATION_NUMBER; i++){
        for(int j = 0; j < VERIFICATION_NUMBER; j++){
            if (binaryValues[i]==binaryValues[j])
                Occurency++;
            if (Occurency>maxOccurency){
                decimalValue = binaryValues[i];
                maxOccurency =   Occurency;
                if(Occurency>3)
                    break;
            }
        }
    }
    return decimalValue; 
}

#endif // __SIRC_CPP__