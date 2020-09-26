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

unsigned int write_register(S74HC595 *reg_s, S74HC595_pins *pin_s)
{
	unsigned int ret = 0;
	digitalWrite(pin_s->DS, reg_s->DS);
	clock_shcp(pin_s);
	return ret;
}
unsigned int clear_register(S74HC595 *reg_s, S74HC595_pins *pin_s)
{
	unsigned int ret = 0;
	digitalWrite(pin_s->MR, 0);
	digitalWrite(pin_s->MR, 1);
	return ret;
}

unsigned int shift_register(S74HC595_pins *pin_s)
{
	unsigned int ret = 0;
	clock_stcp(pin_s);
	return ret;
}

unsigned int show_register(S74HC595 *reg_s, S74HC595_pins *pin_s)
{
	unsigned int ret = 0;
	digitalWrite(pin_s->OE, 0);
	return ret;
}

unsigned int hide_register(S74HC595 *reg_s, S74HC595_pins *pin_s)
{
	unsigned int ret = 0;
	digitalWrite(pin_s->OE, 1);
	return ret;
}

// This is practically the same as write_register except it takes a bit instead
// of the S94HC595 struct
unsigned int w_rite_bit(unsigned char bit, S74HC595_pins *pin_s)
{
	unsigned int ret = 0;
	if(bit == 0 || bit == 1)
	{
		S74HC595 reg_s;
		reg_s.MR = 1;
		reg_s.SHCP = 0;
		reg_s.STCP = 0;
		reg_s.OE = 1;
		reg_s.DS = bit;
		write_registers(&reg_s, pin_s);
		return ret;
	}
	else
	{
		++ret;
		return ret;
	}
}

unsigned int w_rite_byte(unsigned char byte, S74HC595_pins *pin_s)
{
	unsigned int ret = 0;

	return ret;
}

void clock_shcp(S74HC595_pins *pin_s)
{
	digitalWrite(pin_s->SHCP, 1);
	digitalWrite(pin_s->SHCP,0);
}

void clock_stcp(S74HC595_pins *pin_s)
{
	digitalWrite(pin_s->STCP, 1);
	digitalWrite(pin_s->STCP,0);
}




