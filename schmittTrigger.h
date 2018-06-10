/*
Name:       schmittTrigger.h
Function:	Header file for the schmittTrigger Class Library

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

#ifndef SCHMITT_TRIGGER_H
#define SCHMITT_TRIGGER_H


typedef enum {
	NOT_INVERTING = 0,
	INVERTING = 1
} triggerType_t;

class schmittTrigger
{
public:
	schmittTrigger();
	void beginTH(triggerType_t triggerType, double lowThreshold, double highThreshold, int defaultOutputStatus); // to fully configure the trigger using thresholds
	void beginSP(triggerType_t triggerType, double setpoint, double hysteresis, int defaultOutputStatus); // to fully configure the trigger using setpoint and hysteresis
	void changeThresholds(double lowThreshold, double highThreshold); // to change thresholds "on the fly"
	void changeSetpoint(double setpoint, double hysteresis); // to change thresholds "on the fly" specifing setpoint and hysteresis
	~schmittTrigger();

	bool evaluate(double input);

private:
	triggerType_t _TRIGGERTYPE = NOT_INVERTING; // Trigger Type (INVERTING or NOT_INVERTING)
	bool _POS = 0;	// previous output status
	double _HT = 0; // High Threshold
	double _LT = 0; // Low Threshold
};
	
#endif // SCHMITT_TRIGGER_H
