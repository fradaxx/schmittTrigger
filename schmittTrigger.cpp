/*
Name:       schmittTrigger.cpp
Function:	Source file for the schmittTrigger Class Library

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

schmittTrigger::schmittTrigger()
{
}

void schmittTrigger::beginTH(triggerType_t triggerType, double lowThreshold, double highThreshold, int defaultOuputStatus)
{
	_TRIGGERTYPE = triggerType;
	_LT = lowThreshold;
	_HT = highThreshold;
	_POS = defaultOuputStatus;
}

void schmittTrigger::beginSP(triggerType_t triggerType, double setpoint, double hysteresis, int defaultOuputStatus)
{
	_TRIGGERTYPE = triggerType;
	_LT = setpoint - hysteresis / 2.0;
	_HT = setpoint + hysteresis / 2.0;
	_POS = defaultOuputStatus;
}

// to change thresholds "on the fly"
void schmittTrigger::changeThresholds(double lowThreshold, double highThreshold)
{
	_LT = lowThreshold;
	_HT = highThreshold;
}

// to change thresholds "on the fly" specifing setpoint and hysteresis
void schmittTrigger::changeSetpoint(double setpoint, double hysteresis)
{
	_LT = setpoint - hysteresis/2.0;
	_HT = setpoint + hysteresis/2.0;
}

bool schmittTrigger::evaluate(double input)
{
	bool nos;
	bool A = (input < _LT);
	bool B = (input > _HT);

	switch (_TRIGGERTYPE) {
		case INVERTING:
			nos = A || (_POS && !B);
			break;

		case NOT_INVERTING:
			nos = B || (_POS && !A);
			break;
	}

	_POS = nos;
	return nos;
}

schmittTrigger::~schmittTrigger()
{
}