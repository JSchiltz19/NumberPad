#include "main.c"

void setup(){
	Serial.begin(9600);
	pinMode(LED_BUILTIN,OUTPUT);
	_main();
}


void loop(){
	Serial.println("Your mom is a pussy");
	digitalWrite(LED_BUILTIN,HIGH);
	delay(1000);
	digitalWrite(LED_BUILTIN,LOW);
    delay(500);
}
