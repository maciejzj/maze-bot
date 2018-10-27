#include <Arduino.h>
#include <Servo.h>
#include "defines.h"
#include "servoSensor.h"
#include "platformMotors.h"
#include "HC_SR04.h"

int motLeftForward = 6;
int motLeftBack = 7;
int motLeftVelo = 9;

int motRightForward = 4;
int motRightBack = 5;
int motRightVelo = 10;

int servoPin = 6;
Servo servoSensor;

int ultrasonicTrig = 2;
int ultrasonicEcho = 3;
int ultrasonicInt = 0;
HC_SR04 sensor(ultrasonicTrig, ultrasonicEcho, ultrasonicInt);

void setup() {
	Serial.begin(9600); // for debug

	pinMode(motLeftForward, OUTPUT);
	pinMode(motLeftBack, OUTPUT);
	pinMode(motLeftVelo, OUTPUT);

	pinMode(motRightForward, OUTPUT);
	pinMode(motRightBack, OUTPUT);
	pinMode(motRightVelo, OUTPUT);

	servoSensor.attach(servoPin);

	sensor.begin();
	sensor.start();

	randomSeed(analogRead(0));
}

void loop() {
	int direction;

	if(sensor.isFinished()) {
		if(sensor.getRange() < SAFE_DIST) {
			motorStop();
			sensor.start();

			direction = random(LEFT, RIGHT - 1);
			turnServoSensor(direction);

			if(sensor.probeRange() < SAFE_DIST) {
				direction = !direction;
				turnServoSensor(direction);

				if(sensor.probeRange() < SAFE_DIST) {
					direction = BACK;
				}
			}

			turnServoSensor(FRONT);
			motorTurn(direction);
			sensor.start();
			motorForward();	
		}
		
		sensor.start();
	}
}