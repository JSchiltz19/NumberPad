
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

int _main()
{
	unsigned int pins[] = {6, 5, 4, 3}; 
	keyboard keyboard_s = keyboard_init(pins, NUM_OF_COLUMS, NUM_OF_ROWS);	
	
}

