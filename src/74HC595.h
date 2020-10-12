#ifndef M_74HC595_H 
#define M_74HC595_H


typedef struct
{
//	Type		  Symbol Width	// Description					| Active Lvl
	unsigned char MR	: 1;	// Master Reset					| Active LOW
	unsigned char SHCP	: 1;	// Shift Register Clock Input	| Active HIGH
	unsigned char STCP	: 1;	// Storage Register Input		| Active HIGH
	unsigned char OE	: 1;	// Output Enable Input			| Active LOW
	unsigned char DS	: 1;	// Serial Data Input			| Active HIGH

}S74HC595; 

typedef struct
{
//	Type		  Symbol// Description					| Active Lvl
	unsigned char MR;	// Master Reset					| Active LOW
	unsigned char SHCP;	// Shift Register Clock Input	| Active HIGH
	unsigned char STCP;	// Storage Register Input		| Active HIGH
	unsigned char OE;	// Output Enable Input			| Active LOW
	unsigned char DS;	// Serial Data Input			| Active HIGH
}S74HC595_pins;

unsigned int write_bit(unsigned char _DS, S74HC595_pins *pin_s);
unsigned int write_byte(unsigned char byte, S74HC595_pins *pin_s);

void update_output(S74HC595_pins *pin_s);
unsigned int clear_register(S74HC595_pins *pin_s);
unsigned int shift_register(S74HC595_pins *pin_s);
unsigned int show_register(S74HC595_pins *pin_s);
unsigned int hide_register(S74HC595_pins *pin_s);

S74HC595_pins init_pins(unsigned int _MR, unsigned int _SHCP, unsigned int _STCP, unsigned int _OE, unsigned int _DS);
 
#endif
