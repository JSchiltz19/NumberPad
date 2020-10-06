#ifndef SCAN_H
#define SCAN_H

#include "74HC595.h"

typedef struct
{
	unsigned int * pins;
	unsigned int num_of_columns;
	unsigned int num_of_rows;
	unsigned int keystate;
}keyboard;

keyboard keyboard_init(unsigned int *_pins, unsigned int _num_of_columns, unsigned int _num_of_rows);
int scan(keyboard *keybaord_s, S74HC595_pins *pin_s);

#endif
