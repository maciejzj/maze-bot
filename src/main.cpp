#include <Arduino.h>
#include <Servo.h>
#include "defines.h"
#include "servoSensor.h"
#include "platformMotors.h"

int motLeftForward = 2;
int motLeftBack = 3;
int motLeftVelo = 9;

int motRightForward = 4;
int motRightBack = 5;
int motRightVelo = 10;

int servoPin = 6;
Servo servoSensor;

void setup() {
	Serial.begin(9600); // for debug

	pinMode(motLeftForward, OUTPUT);
	pinMode(motLeftBack, OUTPUT);
	pinMode(motLeftVelo, OUTPUT);

	pinMode(motRightForward, OUTPUT);
	pinMode(motRightBack, OUTPUT);
	pinMode(motRightVelo, OUTPUT);

	servoSensor.attach(servoPin);
}

void loop() {
	
}