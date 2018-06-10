/*
Name:       thermostatDemo.ino
Function:	Demonstration Sketch for the schmittTrigger Class Library
			Simple DS18B20-based thermostat with settable setpoint and hysteresis
			This sketch uses the analog value acquired on A0 to set the setpoint

Created:	06/06/2018 12:14:00

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
#include "OneWire.h"
#include "DallasTemperature.h"


#define ONE_WIRE_BUS		2	// Digital input to connect the data pin of the DS18B20
#define RELAY_CONTROL		12	// Digital pin to control the output relay
#define SETPOINT_ANALOG_IN	0	// Analog pin to read the setpoint

#define DEBUG
#define TRIGGER_TYPE	(triggerType_t) NOT_INVERTING	// Heater control w/ low-level activated relay modules
#define	MIN_TEMP		(double) 20.0	// Minimum settable temperature [degC]
#define MAX_TEMP		(double) 50.0	// Maximum settable temperature [degC]
#define HYST			(double) 0.5	// Regulation hysteresis [degC]

// Setup a oneWire instance to communicate with any OneWire devices  
// (not just Maxim/Dallas temperature ICs) 
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);


schmittTrigger st;	// schmittTrigger instance
double sp, t, lt, ht; // setpoint, actual temperature, low threshold, high threshold


void setup()
{
	sensors.begin();
	Serial.begin(115200);
	Serial.println("Arduino + DS18B20 Thermostat w/ hysteresis and settable threshold");
	sp = MIN_TEMP + analogRead(SETPOINT_ANALOG_IN)*(MAX_TEMP - MIN_TEMP) / 1024; // read analog input 0 and scales valute to [MIN_TEMP, MAX_TEMP] interval
	st.beginSP(TRIGGER_TYPE, sp, HYST, 1); // Initialise the trigger using the setpoint/hysteresis mode
	pinMode(RELAY_CONTROL, OUTPUT);
}

void loop()
{
	delay(100);
	sensors.requestTemperatures(); // Send the command to get temperature readings
	t = sensors.getTempCByIndex(0);
	sp = MIN_TEMP + analogRead(SETPOINT_ANALOG_IN)*(MAX_TEMP - MIN_TEMP)/1024; // Scale the analog input value to [MIN_TEMP, MAX_TEMP] interval
	st.changeSetpoint(sp, HYST);

	bool nos = st.evaluate(t);
	digitalWrite(RELAY_CONTROL, nos);

#ifdef DEBUG
	Serial.print("Setpoint: ");
	Serial.print(sp, 1);
	Serial.print(" degC, ");
	Serial.print("Current Temperature: ");
	Serial.print(t, 1);
	Serial.print(" degC, ");
	Serial.print("Heater status: ");
	Serial.println(nos?"OFF":"ON");
#endif
}
