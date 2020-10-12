
#include <Arduino.h>
#include "74HC595.h"


/*
typedef struct
{
//	Type		  Symbol Width	// Description					| Active Lvl
	unsigned char MR	: 1;	// Master Reset					| Active 0
	unsigned char SHCP	: 1;	// Shift Register Clock Input	| Active 1
	unsigned char STCP	: 1;	// Storage Register Input		| Active 1
	unsigned char OE	: 1;	// Output Enable Input			| Active 0
	unsigned char DS	: 1;	// Serial Data Input			| Active 1

}S74HC595; 

typedef struct
{
//	Type		  Symbol// Description					| Active Lvl
	unsigned char MR;	// Master Reset					| Active 0
	unsigned char SHCP;	// Shift Register Clock Input	| Active 1
	unsigned char STCP;	// Storage Register Input		| Active 1
	unsigned char OE;	// Output Enable Input			| Active 0
	unsigned char DS;	// Serial Data Input			| Active 1
}S74HC595_pins
*/

S74HC595_pins init_pins(unsigned int _MR, unsigned int _SHCP, unsigned int _STCP, unsigned int _OE, unsigned int _DS)
{
	S74HC595_pins pin_s;
	pin_s.MR = _MR;
	pin_s.SHCP = _SHCP;
	pin_s.STCP = _STCP;
	pin_s.OE = _OE;
	pin_s.DS = _DS;

	return pin_s;
}

unsigned int write_bit(unsigned char _DS, S74HC595_pins *pin_s)
{
	unsigned int ret = 0;
	if(_DS != 0 || _DS !=1)
	{
		return ++ret;
	}
	digitalWrite(pin_s->DS, _DS);
	shift_register(pin_s);
	digitalWrite(pin_s->DS, 0);
	return ret;
}

// Shifts in the least significant bit first
unsigned int write_byte(unsigned char byte, S74HC595_pins *pin_s)
{
	unsigned int ret = 0;

	unsigned char _DS = 0;
	int bit_pos;
	for(bit_pos = 0; bit_pos < sizeof(byte); bit_pos++)
	{
		_DS = (byte & (1 << bit_pos)) >> bit_pos;
		ret += write_bit(_DS, pin_s);
	}

	return ret;
}

void update_output(S74HC595_pins *pin_s)
{
	digitalWrite(pin_s->STCP,0);
	digitalWrite(pin_s->STCP,1);
	digitalWrite(pin_s->STCP,0);
}

unsigned int clear_register(S74HC595_pins *pin_s)
{
	unsigned int ret = 0;
	digitalWrite(pin_s->MR, 1);
	digitalWrite(pin_s->MR, 0);
	digitalWrite(pin_s->MR, 1);
	return ret;
}

unsigned int shift_register(S74HC595_pins *pin_s)
{
	unsigned int ret = 0;
	digitalWrite(pin_s->SHCP,0);
	digitalWrite(pin_s->SHCP,1);
	digitalWrite(pin_s->SHCP,0);
	return ret;
}

unsigned int show_register(S74HC595_pins *pin_s)
{
	unsigned int ret = 0;
	digitalWrite(pin_s->OE, 0);
	return ret;
}

unsigned int hide_register(S74HC595_pins *pin_s)
{
	unsigned int ret = 0;
	digitalWrite(pin_s->OE, 1);
	return ret;
}



