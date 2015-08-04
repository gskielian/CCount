#include <EEPROM.h>
#define OUTPUT_PIN 5
#define ANALOG_PIN A0

//character
char ch;

//eeprom address
int addr = 0;

//analog value
int analog_value;


void setup () {
	pinMode(OUTPUT_PIN, OUTPUT);
	digitalWrite(OUTPUT_PIN,LOW);

	Serial.begin(115200);
} 


void loop() {

	//INSTRUCTIONS
	print_instructions();

	//wait for input
	while(Serial.available() == 0){}

	//get serial input
	ch = Serial.read();

	if ( ch == 'p' ) { 
		digitalWrite(OUTPUT_PIN ,HIGH);
		delayMicroseconds(200); //delay 100us
		digitalWrite(OUTPUT_PIN,LOW);
	} else if (ch == 'r') {    
		analog_value=analogRead(ANALOG_PIN);
		Serial.print("Analog read is now "); Serial.println(analog_value);
		Serial.print("Voltage is now "); Serial.println(analog_value/1023.0*5);
	} else if (ch == 's') {    
		analog_value=analogRead(ANALOG_PIN);
		Serial.print("Analog read is now "); Serial.println(analog_value);

		EEPROM.write(addr, analog_value);
		Serial.print("Analog read stored on uC EEPROM address"); Serial.println(addr);

		//make sure we loop back (cannot go over 512)
		addr=(addr + 1)%512;
	} else if (ch == 'd') {    
		for (int i = 0; i < 512; i++) {
			Serial.print("Address "); Serial.print(i); Serial.print(" has value "); Serial.println(EEPROM.read(i));
		}
	} else {
		delay(10);
	}


	Serial.println("--------------------------------------------------------------------------------");

}

void print_instructions() {
	Serial.println("Instructions:");

	Serial.println("");

	Serial.print("enter \"p\" for a 300us pulse on pin "); Serial.println(OUTPUT_PIN); 
	Serial.print("enter \"r\" to read the voltage on the capacitor via pin "); Serial.println(ANALOG_PIN); 
	Serial.print("enter \"s\" to store analog read on eeprom address "); Serial.println(addr); 
	Serial.println("enter \"d\" to print all eeprom values");

	Serial.println("");
}
