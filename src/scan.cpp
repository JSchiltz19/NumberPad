#include "Arduino.h"
#include "scan.h"
#include <math.h>
#include <stdint.h>


#define H_SCAN_DELAY 100

keyboard keyboard_init(unsigned int *_pins, unsigned int _num_of_columns, unsigned int _num_of_rows)
{
	keyboard keyboard_s;
	keyboard_s.pins = _pins;
	keyboard_s.num_of_columns = _num_of_columns;
	keyboard_s.num_of_rows = _num_of_rows;
	keyboard_s.keystate = (unsigned int*)malloc(_num_of_rows * _num_of_columns * sizeof(unsigned int));

	clear_keyboard(&keyboard_s);

	unsigned int i;
	for(i = 0; i< _num_of_columns; i++)
	{
		pinMode(_pins[i], INPUT);
	}

	return keyboard_s;

}

int scan(keyboard *keyboard_s, S74HC595_pins *pin_s)
{
	int ret = 0;
	if(keyboard_s == NULL || pin_s == NULL) return ret + 1;

	unsigned int row = 0;
	unsigned int column = 0;
	uint8_t reg = 1 << (keyboard_s->num_of_rows - 1);
	
	for(row = 0; row < keyboard_s->num_of_rows; row++)
	{
		ret += write_byte(reg, pin_s);
		update_output(pin_s);

		Serial.print("reg = ");
		Serial.println(reg, BIN);
		

		for(column = 0; column < keyboard_s->num_of_columns; column++)
		{
			keyboard_s->keystate[column + (row * keyboard_s->num_of_columns)] = digitalRead(keyboard_s->pins[column]);
			delay(H_SCAN_DELAY);
		}
		
		reg = reg >> 1;
	}
	return ret;
}

void clear_keyboard(keyboard *keyboard_s)
{	
	unsigned int row = 0;
	unsigned int column = 0;
		
	for(row = 0; row < keyboard_s->num_of_rows; row++)
	{
		for(column = 0; column < keyboard_s->num_of_columns; column++)
		{
			keyboard_s->keystate[column + (row * keyboard_s->num_of_columns)] = 0;
		}
	}
}

void print_keyboard(keyboard *keyboard_s)
{
	unsigned int row = 0;
	unsigned int column = 0;
	
	for(row = 0; row < keyboard_s->num_of_rows; row++)
	{
		for(column = 0; column < keyboard_s->num_of_columns; column++)
		{
			/*
			Serial.print(column);
			Serial.print(",");
			Serial.print(row);
			Serial.print("=");
			*/
			Serial.print(keyboard_s->keystate[column + (row * keyboard_s->num_of_columns)]);

			Serial.print("  ");
			delay(10);
		}
		Serial.println("");
	}
	Serial.println("");
}
