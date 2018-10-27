#include <Arduino.h>
#include <Servo.h>
#include "defines.h"
#include "servoSensor.h"

int servoPin = 6;
Servo servoSensor;

void setup() {
	Serial.begin(9600); // for debug

	servoSensor.attach(servoPin);
}

void loop() {
	
}