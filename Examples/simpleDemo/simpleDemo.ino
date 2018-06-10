/*
    Name:       simpleDemo.ino
	Function:	Demonstration Sketch for the schmittTrigger Class Library
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

#define DEBUG
#define LOW_THRESHOLD	(double) 2.5 // Low Threshold [V]
#define HIGH_THRESHOLD	(double) 3.0 // High Threshold [V]
#define TRIGGER_TYPE	(triggerType_t) NOT_INVERTING


schmittTrigger st;
double ain;


void setup()
{
	Serial.begin(115200);
	st.beginTH(TRIGGER_TYPE, LOW_THRESHOLD, HIGH_THRESHOLD, 0);
	pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
	delay(100);
	ain = 5.0*analogRead(0)/1024;
	bool nos = st.evaluate(ain);
	digitalWrite(LED_BUILTIN, nos);

#ifdef DEBUG
	Serial.print(ain, 2);
	Serial.print(" V, ");
	Serial.println(nos);
#endif
}