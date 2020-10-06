
#include "scan.h"

keyboard keyboard_init(unsigned int *_pins, unsigned int _num_of_columns, unsigned int _num_of_rows)
{
	keyboard keyboard_s;
	keyboard_s.pins = _pins;
	keyboard_s.num_of_columns = _num_of_columns;
	keyboard_s.num_of_rows = _num_of_columns;
	keyboard_s.keystate = 0;
	
	return keyboard_s;

}

int scan(keyboard *keyboard_s, S74HC595_pins *pin_s)
{
	int ret = 0;
	int num_of_rows = 5; //make into a keyboard_s struct
	int num_of_columns = 5; //also make into the keyboard_s struct
	unsigned int row = 0;
	unsigned int column = 0;
	
	write_bit(1, pin_s);
	show_register(pin_s);

	for(row = 0; row < keyboard_s->num_of_rows; row++)
	{
		for(column = 0; column < keyboard_s->num_of_columns; column++)
		{
			keyboard_s->keystate |= (digitalRead(keyboard_s->pins[column]) << ((keyboard_s->num_of_columns * row) + column));
		}
		shift_register(pin_s);
	}
	return ret;
}
