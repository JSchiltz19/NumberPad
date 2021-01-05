
//#include "src/74HC595.h"
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
#define NUM_OF_COLUMNS 4
#define NUM_OF_ROWS 6

#define MR 0 //connected to vcc (_2 on datasheet)
#define SHCP 9
#define STCP 7
#define OE 0 //connected to gnd (! on datasheet)
#define DS 8

#define UPDATE_PERIOD 1000	//Update period for scanning
/*************************Personal Variables**********************************/
unsigned int old_millis = 0;
unsigned int pins[] = {3, 4, 5, 6}; 

void setup(){
	Serial.begin(9600); //Begin Serial
	while(!Serial);

	pinMode(LED_BUILTIN, OUTPUT); //Set LED pinmode

	delay(2000);	//Wait a bit

	digitalWrite(pins[0], LOW);
	digitalWrite(pins[1], LOW);
	digitalWrite(pins[2], LOW);
	digitalWrite(pins[3], LOW);
	pinMode(pins[0], INPUT);
	pinMode(pins[1], INPUT);
	pinMode(pins[2], INPUT);
	pinMode(pins[3], INPUT);
	while(true){
		digitalWrite(DS,HIGH);
		delay(10);
		Serial.println("CLock IN");
		for(int i = 0; i <8; i++){
			digitalWrite(SHCP, HIGH);
			delay(100);
			digitalWrite(SHCP, LOW);
			delay(100);
		}	
		Serial.println("Storage Clock");
		digitalWrite(STCP, HIGH);
		delay(100);
		digitalWrite(STCP, LOW);
		delay(100);
	}
	keyboard keyboard_s = keyboard_init(pins, NUM_OF_COLUMNS, NUM_OF_ROWS);	//Initiate keyboard struct
	if(&keyboard_s == NULL)
	{
		Serial.println("keyboard = NULL");
		while(1);
	}
	S74HC595_pins pin_s = init_pins(MR, SHCP, STCP,  OE, DS);	//Initiate pins struct and pin modes
	if(&pin_s == NULL)
	{
		Serial.println("Pins = NULL");
		while(1);
	}

	while(true)
	{
		int error = 0;
		unsigned int current_time = (unsigned int)(millis() - old_millis);	//Get current time
		if(current_time >= UPDATE_PERIOD)	//Run keyscan at every Update Period
		{

			clear_keyboard(&keyboard_s);

			error += scan(&keyboard_s, &pin_s); // Calls scan.h

			print_keyboard(&keyboard_s);

			if(error > 0)
			{
				Serial.print("Error = ");
				Serial.println(error);
				break;
			}

			old_millis = millis();
		}
	}
}


void loop(){
}

