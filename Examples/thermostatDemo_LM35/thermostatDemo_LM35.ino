/*
Name:       thermostatDemo_LM35.ino
Function:	Demonstration Sketch for the schmittTrigger Class Library
			Simple LM35-based thermostat with settable setpoint and hysteresis
			This sketch uses the analog value acquired on A0 to set the setpoint

Created:	13/06/2018 10:18:00

Copyright (c) 2018, Francesco Adamo - Polytechnic University of Bari - Italy
e-mail: francesco.adamo@poliba.it

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*/

#include "schmittTrigger.h"

#define VREF		(double) 5.0				// Voltage reference for analog inpu
#define K			(double) 100*(VREF/1023)	// transducer constant [degC/LSB]

#define RELAY_CONTROL		12	// Digital pin to control the output relay
#define SETPOINT_ANALOG_IN	0	// Analog pin to read the setpoint
#define LM35_ANALOG_IN		1	// Analog pin to read the setpoint

//#define DEBUG
#define TRIGGER_TYPE	(triggerType_t) NOT_INVERTING	// Heater control w/ low-level activated relay modules
#define	MIN_TEMP		(double) 20.0	// Minimum settable temperature [degC]
#define MAX_TEMP		(double) 50.0	// Maximum settable temperature [degC]
#define HYST			(double) 2.0	// Regulation hysteresis [degC]


schmittTrigger st;	// schmittTrigger instance
double sp, t, lt, ht; // setpoint, actual temperature, low threshold, high threshold


void setup()
{
	//analogReference(INTERNAL); // Switch the ADC reference input to the 1.1 V internal reference
	sp = MIN_TEMP + analogRead(SETPOINT_ANALOG_IN)*(MAX_TEMP - MIN_TEMP) / 1024; // read analog input 0 and scales valute to [MIN_TEMP, MAX_TEMP] interval
	st.beginSP(TRIGGER_TYPE, sp, HYST, HIGH); // Initialise the trigger using the setpoint/hysteresis mode
	pinMode(RELAY_CONTROL, OUTPUT);
	Serial.begin(115200);
	#ifdef DEBUG
		Serial.println("Arduino + LM35 Thermostat w/ hysteresis and settable threshold");
	#endif
}

void loop()
{
	delay(1000);
	sp = MIN_TEMP + analogRead(SETPOINT_ANALOG_IN)*(MAX_TEMP - MIN_TEMP) / 1024; // Scale the analog input value to [MIN_TEMP, MAX_TEMP] interval
	double tl = sp - HYST / 2;
	double th = sp + HYST / 2;
	t = (double) K*analogRead(LM35_ANALOG_IN);

	bool nos = st.evaluate(t); // new output state
	digitalWrite(RELAY_CONTROL, nos ? HIGH : LOW);

	Serial.print(tl, 1);
	Serial.print(", ");
	Serial.print(th, 1);
	Serial.print(", ");
	Serial.println(t, 1);
}
