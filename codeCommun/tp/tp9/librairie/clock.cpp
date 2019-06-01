#include "clock.h"

void clock::setPWM(int strength, int timerNumber){
	clock::setPWM(strength, strength, timerNumber);
}

void clock::setPWM(int strengthA, int strengthB, int timerNumber)
{
													   // param: strength of activation of each side
		cli();										   // Stop interruption to set up register
		if (strengthA > 200 || strengthB > 200) // check if the strength if small enough to not break the fct.
			return;
		if (strengthA < 0 || strengthB < 0) // check if the strength are above 0 to be a pwm
			return;
		uint8_t lengthA = ((strengthA * 255) / 200);  // convert the A strength to a value between 0 and 255
		uint8_t lengthB = ((strengthB * 255) / 200); // convert the B strength to a value between 0 and 255
		// =====================
		// Start of testing zone
		// =====================
		switch (timerNumber) // reset the register
		{
		case 0: // clock 0
			EICRA |= (1 << ISC00);
			OCR0A = lengthA;										// Set the first comparator to interrupt on the left value
			OCR0B = lengthB;										// Set the second comparator to interrupt on the right value
			// Start to clear register
			TCCR0A &= ~(1 << WGM01);
			TCCR0B &= ~((1 << CS02) | (1 << CS00));
			TIMSK0 &= ~(1 << OCIE0A);
			// End of clearing
			TCCR0A |= (1 << COM0A1 | 1 << COM0B1 | 1 << WGM00);
			TCCR0B |= (1 << CS02);
			break;
		case 1: // clock 1
			EICRA |= (1 << ISC00);
			OCR1A = lengthA;										// Set the first comparator to interrupt on the left value
			OCR1B = lengthB;										// Set the second comparator to interrupt on the right value
			// Start to clear register
			TCCR1B &= ~((1 << WGM12) | (1 << CS12) | (1 << CS10));
			TIMSK1 &= ~(1 << OCIE1A);
			// End of clearing
			TCCR1A |= ((1 << WGM10) | (1 << COM1A1) | (1 << COM1B1)); // Set the pwm on 8 bit mode
			TCCR1B |= (1 << CS11);									// Set the clk/1024 preset
			TCCR1C = 0;
			break;
		case 2:	// clock 2
			EICRA |= (1 << ISC00);
			OCR2A = lengthA;										// Set the first comparator to interrupt on the left value
			OCR2B = lengthB;										// Set the second comparator to interrupt on the right value
			// Start to clear register
			TCCR2A &= ~(1 << WGM21);
			TCCR2B &= ~((1 << CS22) | (1 << CS20)); 
			TIMSK2 &= ~(1 << OCIE2A);
			// End of clearing
			TCCR2A |= (1 << COM2A1 | 1 << COM2B1 | 1 << WGM20);
			TCCR2B |= (1 << CS21);
			break;
		default:
			break;
		}
		// ====================
		// End of testing zone
		// ====================
		sei(); // Allow interruptions again
}


void clock::setTimerCTC(float ftime, int timerNumber)
{
	cli();
	int prescaler = 255;
	if (timerNumber != 1)			// Check if is not the timer 1 : at 16bits
	{								// Blocking interrupt for the init
		if (ftime < 0 || 255 < ftime) // check if the number of clock can be deal with the ctc
			return;
	}
	else
	{
		ftime *= ((float)((float)F_CPU / (float)prescaler) / (float)1000);
		if (ftime > 65535)
			return;
	}
	int time = (int)ftime;
	// cette procédure ajuste le registre EIMSK
	// de l’ATmega324PA pour permettre les interruptions externes
	EIMSK |= (1 << INT0);
	EICRA |= (1 << INT0);
	sei();				 // Allow interrupt again
	switch (timerNumber) // Adjust register based on timer number
	{
	case 0: // Timer 0
		// Start of reseting register
		TCCR0A &= ~(1 << COM0A1 | 1 << COM0B1 | 1 << WGM00);
		TCCR0B &= ~(1 << CS02);
		// end of reseting register
		TCNT0 |= 0;
		OCR0A |= time;						   // Place the comparator to proc to time*1024 clock pulse
		TCCR0A |= (1 << WGM01);				   // Activate the ctc mode
		TCCR0B |= ((1 << CS02) | (1 << CS00)); // Activate the clock/ 1024 preset
		TIMSK0 |= ((1 << OCIE0A));
		break;
	case 1:
		// Start of reseting register
		TCCR1A &= ~((1 << WGM10) | (1 << COM1A1) | (1 << COM1B1)); // Set the pwm on 8 bit mode
		TCCR1B &= ~(1 << CS11);									// Set the clk/1024 preset
		// end of reseting register
		TCNT1 |= 0;
		OCR1A |= time;
		TCCR1A |= 0;
		TCCR1B |= ((1 << WGM12) | (1 << CS02) | (1 << CS00));
		TIMSK1 |= ((1 << OCIE1A));
		break;
	case 2: // Timer 2
		// start of reseting register
		TCCR2A &= ~(1 << COM2A1 | 1 << COM2B1 | 1 << WGM20);
		TCCR2B &= ~(1 << CS21);
		// end of reseting register
		TCNT2 |= 0;
		OCR2A |= time;						   // Place the comparator to proc to time*1024 clock pulse
		TCCR2A |= (1 << WGM21);				   // Activate the ctc mode
		TCCR2B |= ((1 << CS22) | (1 << CS20)); // Activate the clock/ 1024 preset
		TIMSK2 |= ((1 << OCIE2A));
		break;
	default:
		break;
	}
}