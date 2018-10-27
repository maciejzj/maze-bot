#include <Arduino.h>
#include "platformMotors.h"
#include "defines.h"

extern int motLeftForward;
extern int motLeftBack;
extern int motLeftVelo;

extern int motRightForward;
extern int motRightBack;
extern int motRightVelo;

void motorStop() {
	digitalWrite(motLeftForward, LOW);
	digitalWrite(motLeftBack, LOW);

	digitalWrite(motLeftForward, LOW);
	digitalWrite(motLeftBack, LOW);

	analogWrite(motLeftVelo, 0);
}

void motorTurn(int direction, int velocity) {
	switch (direction) {
		case RIGHT:
			motorTurnRight(velocity);
			break;

		case LEFT:
			motorTurnLeft(velocity);
			break;
	}
}

void motorTurnLeft(int velocity) {
	analogWrite(motLeftVelo, velocity);
	
	digitalWrite(motLeftForward, HIGH);
	digitalWrite(motLeftBack, LOW);

	digitalWrite(motLeftForward, LOW);
	digitalWrite(motLeftBack, HIGH);

	delay(TURNING_TIME);
	motorStop();
}

void motorTurnRight(int velocity) {
	analogWrite(motLeftVelo, velocity);

	digitalWrite(motLeftForward, LOW);
	digitalWrite(motLeftBack, HIGH);

	digitalWrite(motLeftForward, HIGH);
	digitalWrite(motLeftBack, LOW);

	delay(TURNING_TIME);
	motorStop();
}

void motorForward(int velocity) {
	analogWrite(motLeftVelo, velocity);

	digitalWrite(motLeftForward, HIGH);
	digitalWrite(motLeftForward, HIGH);

	delay(TURNING_TIME);
	motorStop();
}