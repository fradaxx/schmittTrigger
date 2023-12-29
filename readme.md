This is my attempt to implement a Schmitt Trigger (trigger w/ hysteresis) Class Library for microcontrollers like Arduino.

Three simple demos are given for Arduino with the library at current stage of development:

- simpleDemo: a very simple sketch that initialize a noninverting trigger with hardcoded thresholds and calculates the output status using the signal on A0 as input; informative messages giving the input value and the output status are sent on the serial port.

- thermostatDemo_DS18B20: a simple on-off thermostat implementation with settable setpoint and hysteresis which controls a digital output in response to temperature measured with a DS18B20 onewire temperature sensor.

- thermostatDemo_LM35: a simple on-off thermostat implementation with settable setpoint and hysteresis which controls a digital output in response to temperature measured with a LM35 analog output temperature sensor.


Please note that for the development I'm using the Visual Micro plug-in w/ Visual Studio 2019 Community Edition; this explains the presence of many additional files other than the classic .h, .cpp and .ino
