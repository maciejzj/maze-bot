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

void motorTurnLeft(int direction, int velocity = 255) {
	analogWrite(motLeftVelo, velocity);
	
	digitalWrite(motLeftForward, HIGH);
	digitalWrite(motLeftBack, LOW);

	digitalWrite(motLeftForward, LOW);
	digitalWrite(motLeftBack, HIGH);

	delay(TURNING_TIME);
	motorStop();
}

void motorTurnRight(int direction, int velocity) {
	analogWrite(motLeftVelo, velocity);

	digitalWrite(motLeftForward, LOW);
	digitalWrite(motLeftBack, HIGH);

	digitalWrite(motLeftForward, HIGH);
	digitalWrite(motLeftBack, LOW);

	delay(TURNING_TIME);
	motorStop();
}

void motorForward(int direction, int velocity) {
	analogWrite(motLeftVelo, velocity);

	digitalWrite(motLeftForward, HIGH);
	digitalWrite(motLeftForward, HIGH);

	delay(TURNING_TIME);
	motorStop();
}