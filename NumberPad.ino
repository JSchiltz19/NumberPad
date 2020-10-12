
#include "src/74HC595.h"
#include "src/scan.h"

/*
 * D3	D4	D5	D6	|
 * -----------------|--
 * S18	S19	S20	S21	|Q5
 * S14	S15	S16 S17	|Q4
 * S10	S11	S12	S13	|Q3
 * S6	S7	S8	S9	|Q2
 * S3	S4	S5	S6	|Q1
 *		S1	S2		|Q0
 */
/*
 * D7---STCP
 * D8---DP
 * D9---SHCP
 * Gnd--Gnd
 * Gnd--!	OE?
 * Vcc--Vcc
 * Vcc--_2	MR?
*/

/*************************Personal Macros*************************************/
#define NUM_OF_COLUMS 4
#define NUM_OF_ROWS 6

#define MR 0 //connected to vcc (_2 on datasheet)
#define SHCP 9
#define STCP 7
#define OE 0 //connected to gnd (! on datasheet)
#define DS 8

#define UPDATE_PERIOD 200	//Update period for scanning
/*************************Personal Variables**********************************/
unsigned int old_millis = 0;

void printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int j;
    size_t i;
    for (i = size-1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            Serial.print(byte);
        }
    }
    Serial.print("\n");
}

void setup(){
	Serial.begin(9600);
	pinMode(LED_BUILTIN,OUTPUT);

	unsigned int pins[] = {6, 5, 4, 3}; 
	keyboard keyboard_s = keyboard_init(pins, NUM_OF_COLUMS, NUM_OF_ROWS);	

	S74HC595_pins pin_s = init_pins(MR, SHCP, STCP,  OE, DS);

	while(true)
	{
		unsigned int current_time = (unsigned int)(millis() - old_millis);
		if(current_time >= UPDATE_PERIOD)
		{
			keyboard_s.keystate = 0;
			scan(&keyboard_s, &pin_s);

			//printBits(sizeof(keyboard_s.keystate), &(keyboard_s.keystate));
			Serial.println(keyboard_s.keystate, BIN);
			//Serial.print("   ");
 			//Serial.println(current_time);
				
			old_millis = millis();
		}
	}
}


void loop(){



}
