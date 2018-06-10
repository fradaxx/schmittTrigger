This is my attempt to implement a Schmitt Trigger (trigger w/ hysteresis) Class Library for microcontrollers like Arduino.

Two demos are given with the library until now:

    simpleDemo: a very simple sketch that initialize a noninverting trigger with hardcoded thresholds and calculates the output status using the signal on A0 as input; informative messages giving the input value and the output status are sent on the serial port.
    thermostatDemo: a simple on-off thermostat implementation with settable setpoint and hysteresis which controls a digital output in response to temperature measured with a DS18B20 onewire temperature sensor.

Please note that for the development I'm using the Visual Micro plug-in w/ Visual Studio 2017 Community Edition; this explains the presence of many additional files other that the classic .h, .cpp and .ino