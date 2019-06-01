# avr_API
This is a library for an avr atmega324pa

# Table of contents
1. [Introduction](#introduction)  
    1. [Normes](#avr_api/normes)  
    2. [To Discuss](#avr_api/toDiscuss)  
2. [Descripion of the library](#descriptionOfTheLibrary)  
3. [Analog](#analog)  
    1. [analog/files](#analog/files)  
    2. [analog/include](#analog/include)  
    3. [analog/description](#analog/description)  
    4. [analog/functions](#analog/functions)  
        a. [analog/functions/read](#analog/functions/read)  
4. [Can](#can)  
    1. [can/files](#can/files)  
    2. [can/include](#can/include)  
    3. [can/description](#can/description)  
    4. [can/functions](#can/functions)  
        a. [can/functions/lecture](#can/functions/lecture)  
5. [Clock](#clock)  
    1. [clock/files](#clock/files)  
    2. [clock/include](#clock/include)  
    3. [clock/description](#clock/description)  
    4. [clock/functions](#clock/functions)  
        a. [clock/functions/setPWM](#clock/functions/setPWM)  
        b. [clock/functions/setSignalPWM](#clock/functions/setSignalPWM)  
        c. [clock/functions/setTimerCTC](#clock/functions/setTimerCTC)  
6. [DCMotor](#DCMotor)  
    1. [DCMotor/files](#DCMotor/files)  
    2. [DCMotor/include](#DCMotor/include)  
    3. [DCMotor/description](#DCMotor/description)  
    4. [DCMotor/functions](#DCMotor/functions)  
        a. [DCMotor/functions/setSpeed](#DCMotor/functions/setSpeed)  
        b. [DCMotor/functions/getSpeed](#DCMotor/functions/getSpeed)  
        c. [DCMotor/functions/addSpeed](#DCMotor/functions/addSpeed)  
        d. [DCMotor/functions/removeSpeed](#DCMotor/functions/removeSpeed)  
7. [MCU](#MCU)  
    1. [MCU/files](#MCU/files)  
    2. [MCU/include](#MCU/include)  
    3. [MCU/description](#MCU/description)  
    4. [DCMotor/functions](#MCU/functions)  
        a. [MCU/functions/halt](#MCU/functions/halt)  
        b. [MCU/functions/resume](#MCU/functions/resume)  
        c. [MCU/functions/turnLeft](#MCU/functions/turnLeft)  
        d. [MCU/functions/turnRight](#MCU/functions/turnRight)  
        e. [MCU/functions/moveForward](#MCU/functions/moveForward)  
        f. [MCU/functions/moveBackward](#MCU/functions/moveBackward)  
        g. [MCU/functions/setMotors](#MCU/functions/setMotors)  
        h. [MCU/functions/moveRobot](#MCU/functions/moveRobot)  
        i. [MCU/functions/setRollingSpeed](#MCU/functions/setRollingSpeed)  
        j. [MCU/functions/setMovement](#MCU/functions/setMovement)  
8. [TEMPLATE](#TEMPLATE)  
    1. [TEMPLATE/files](#TEMPLATE/files)  
    2. [TEMPLATE/include](#TEMPLATE/include)  
    3. [TEMPLATE/description](#TEMPLATE/description)  
    4. [TEMPLATE/functions](#TEMPLATE/functions)  
        a. [TEMPLATE/functions/FUNCTION_DECLARACTION1](#TEMPLATE/functions/FUNCTION_DECLARATION1)  
        b. [TEMPLATE/functions/FUNCTION_DECLARACTION2](#TEMPLATE/functions/FUNCTION_DECLARATION2)  

<a name="introduction"></a>
## Normes <a name="avr_api/normes"></a>
	- Google normes (cpplint)
	- Camel case
	- '_' after the private variable name

## To Discuss <a name="avr_api/toDiscuss"></a>
	- mettre le nom des librairies en suivant le format camelCase (ex.: Clock.hpp => clock.hpp)
	- make clean : s'assurer qu'il supprime tout les .o .a .hex .out
	- make : creer juste le .o du main
	- Il faut que le makefile compile comme il le faut

# Description of the Library <a name="descriptionOfTheLibrary"></a>
notes :
	- order libraries in alphabetical order
	- use the template (located at the end of the README.md)


# Analog <a name="analog"></a>
## Files <a name="analog/files"></a>
 * Analog.hpp

## Include <a name="analog/include"></a>
 * can.h
 * avr/io.h
 * avr/interrupt.h
 
## Description <a name="analog/description"></a>
This is an upgrade of the interface given by the teacher that allow to get analog data from the port A with only one line of code. this interface need only the configuration of the PortA (1 where the analog data will be sent) to return the numeric version of the data. To work this interface need for the voltage divider on the main circuit board to be set correctly.

## Functions <a name="analog/functions"></a>
### uint8_t Read(uint8_t configuration) <a name="analog/functions/read"></a>
	-parameter: the configuration of portA on a uint8_t [1,2,4,8,16,32,64,128]
		place a 1 where the analog captor is connected
	-return value: the 8 most bits significative data as a uint8_t



# CAN <a name="can"></a>
## Files <a name="can/files"></a>
 * can.h
 * can.cpp 
 
## Include <a name="can/include"></a>
 * avr/io.h

## Description <a name="can/description"></a>
"can.h" and "can.cpp" are responsible for the conversion 
from analog to digital on any pins from the PORTA
 
## Functions <a name="can/functions"></a>
### uint16_t lecture(uint8_t pin) <a name="can/functions/lecture"></a>
	-parameters: which pin from PORTA to read from
	-return value: returns the digital value mapped from [0, 5]V -> [0, 255]
	-description: 



# Clock <a name="clock"></a>
## Files <a name="clock/files"></a>
 * Clock.hpp

## Include <a name="clock/include"></a>
 * avr/io.h
 * avr/interrupt.h
 * util/delay.h

## Description <a name="clock/description"></a>
Clock is an api used to instantiate ctc timer with the clock 0 and 2 of the board easily and make the adjust to these clock easily. It also provide a function to set and a function to adjust the pwm with the timer 1 allowing an easy use of these components.

## Functions <a name="clock/functions"></a>
### void setPWM(int left,int right) <a name="clock/functions/setPWM"></a>
	-parameters: the fraction where the pwm is on [0 to 200]
	-return value: none
	-description:
### void setSinglePWM(int strength, char side) <a name="clock/functions/setSignalPWM"></a>
	-parameters: the fraction where the pwm is on [0 to 200] and the side to adjust [l,L,r,R]
	-return value: none
	-description:
### void setTimerCTC(int time, int timerNumber) <a name="clock/functions/setTimerCTC"></a>
	-parameters: the number of (clk/1024) before the interrupt [0 to 255] and wich clock to use [0,2]
	-return value: none
	-description:



# DCMotor <a name="DCMotor"></a>
## Files <a name="DCMotor/files"></a>
 * DCMotor.h
 * DCMotor.cpp

## Include <a name="DCMotor/include"></a>
 * avr/io.h
 * avr/interrupt.h

## Description <a name="DCMotor/description"></a>
"DCMotor.h" and "DCMotor.cpp" are responsible for the physical motors and their properties.

## Functions <a name="DCMotor/functions"></a>
### void setSpeed(int16_t speed) <a name="DCMotor/functions/setSpeed"></a>
	-parameters:  
	-return value:  
	-description: 
### int16_t getSpeed() <a name="DCMotor/functions/getSpeed"></a>
	-parameters:  
	-return value:  
	-description: 
### void addSpeed(int16_t var) <a name="DCMotor/functions/addSpeed"></a>
	-parameters:  
	-return value:  
	-description: 
### void removeSpeed(int16_t var) <a name="DCMotor/functions/removeSpeed"></a>
	-parameters:  
	-return value:  
	-description: 



# MCU <a name="MCU"></a>
## Files <a name="MCU/files"></a>
 * MCU.h
 * MCU.cpp 
 
## Include <a name="MCU/include"></a>
 * DCMotor.h
 * avr/io.h
 * avr/interrupt.h

## Description <a name="MCU/description"></a>
This is the motors control unit, or MCU for short. It's task is to 
manage the motors and thus the movement of the robot.
 
## Functions <a name="MCU/functions"></a>
### void halt() <a name="MCU/functions/halt"></a>
	-parameters: 
	-return value:  
	-description:
### void resume() <a name="MCU/functions/resume"></a>
	-parameters: 
	-return value:  
	-description:
### void turnLeft(uint8_t degreesSecond) <a name="MCU/functions/turnLeft"></a>
	-parameters: 
	-return value:  
	-description:
### void turnRight(uint8_t degreesSecond) <a name="MCU/functions/turnRight"></a>
	-parameters: 
	-return value:  
	-description:
### void moveForward(uint8_t speed) <a name="MCU/functions/moveForward"></a>
	-parameters: 
	-return value:  
	-description:
### void moveBackward(uint8_t speed) <a name="MCU/functions/moveBackward"></a>
	-parameters: 
	-return value:  
	-description:
### void setMotors(uint16_t leftSpeed, uint16_t rightSpeed) <a name="MCU/functions/setMotors"></a>
	-parameters: 
	-return value:  
	-description: 
### protected functions <a name="MCU/functions/protectedFunctions"></a>
### void moveRobot(int16_t speed, int16_t degreesSecond) <a name="MCU/functions/moveRobot"></a>
	-parameters: 
	-return value:  
	-description:
### void setRollingSpeed(int16_t degreesSecond) <a name="MCU/functions/setRollingSpeed"></a>
	-parameters: 
	-return value:  
	-description:
### void setMovement() <a name="MCU/functions/setMovement"></a>
	-parameters: 
	-return value:  
	-description:



\=============================================================================

				**TEMPLATE** 
									
\=============================================================================

# NAMEOFTHEMODULE <a name="TEMPLATE"></a>
## Files <a name="TEMPLATE/files"></a>
 * NAMEOFTHEFILE.h
 * NAMEOFTHEFILE.cpp 
 * OR 
 * NAMEOFTHEFILE.hpp 

## Include <a name="TEMPLATE/include"></a>
 * NAMEOFTHEINLUDEDFILE1.hpp 
 * NAMEOFTHEINLUDEDFILE2.h 
 * ETC.h

## Description <a name="TEMPLATE/description"></a>
Include a brief description of what the module does and why it's here (needed) 
 
## Functions <a name="TEMPLATE/functions"></a>
### TYPE FUNCTION_DECLARATION1(int param1, char param2) <a name="TEMPLATE/functions/FUNCTION_DECLARATION1"></a>
	-parameters: short description of what is expected in the parameters 
			ex.: param1 range [0, 100], it is the note of the student. param2 if  
				of range [a, f] or range[A, F], it is the grade of the student. 
	-return value: short description of what's returned 
	-description: description of the purpose of this function 
### TYPE FUNCTION_DECLARATION2(bool trueorfalse, ...) <a name="TEMPLATE/functions/FUNCTION_DECLARATION2"></a>
	- ...
	-
			
