#include <Arduino.h>
#include <Servo.h>
#include "servoSensor.h"
#include "defines.h"
#include "HC_SR04.h"

/* Global variables from main file */
extern Servo servoSensor;
extern HC_SR04 sensor;

void turnServoSensor(int direction) {
	switch(direction) {
		case RIGHT:
			servoSensor.write(180);
			break;
		
		case FRONT:
			servoSensor.write(90);
			break;

		case LEFT:
			servoSensor.write(0);
			break;
	}
	delay(MOTOR_STOP_DELAY);
}

int findUnobstructedDirection() {
	int direction = random(RIGHT, LEFT + 1);
	turnServoSensor(direction);

	if(sensor.probeRange() < SAFE_DIST) {
		direction = !direction;
		turnServoSensor(direction);

		if(sensor.probeRange() < SAFE_DIST) {
			direction = BACK;
		}
	}

	turnServoSensor(FRONT);
	return direction;
}