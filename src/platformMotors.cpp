#include <Arduino.h>
#include "platformMotors.h"
#include "defines.h"

/* Global variables from main file */
extern int motLeftForward;
extern int motLeftBack;
extern int motLeftVelo;

extern int motRightForward;
extern int motRightBack;
extern int motRightVelo;

extern int motLeftCounter;
extern int motRightCounter;

extern unsigned long motLeftDeltaTime;
extern unsigned long motRightDeltaTime;

unsigned long lastTimeLeft;		///< Time from last interrupt on left endcoder
unsigned long lastTimeRight;	///< Time from last interrupt on right endcoder

inline void motorStop() {
	motorLeftStop();
	motorRightStop();
	delay(MOTOR_STOP_DELAY);
}

inline void motorLeftStop() {
	digitalWrite(motLeftForward, LOW);
	digitalWrite(motLeftBack, LOW);
	analogWrite(motLeftVelo, 0);
}

inline void motorRightStop() {
	digitalWrite(motRightForward, LOW);
	digitalWrite(motRightBack, LOW);
	analogWrite(motRightVelo, 0);
}

void motorTurn(int direction) {
	switch (direction) {
		case RIGHT:
			motorTurnRight();
			break;

		case LEFT:
			motorTurnLeft();
			break;

		case BACK:
			motorTurnBack();
			break;
	}
}

void motorTurnLeft() {
	int velocity = 255;

	analogWrite(motLeftVelo, velocity);
	analogWrite(motRightVelo, velocity);
	
	digitalWrite(motLeftForward, HIGH);
	digitalWrite(motLeftBack, LOW);

	digitalWrite(motRightForward, LOW);
	digitalWrite(motRightBack, HIGH);

	delay(TURNING_TIME);
	motorStop();
}

void motorRotateLeft(int velocity) {
	if(velocity >= 0) {
		digitalWrite(motLeftForward, HIGH);
		digitalWrite(motLeftBack, LOW);
		analogWrite(motLeftVelo, velocity);
	} else {
		digitalWrite(motLeftForward, LOW);
		digitalWrite(motLeftBack, HIGH);
		analogWrite(motLeftVelo, -velocity);
	}
}

void motorRotateRight(int velocity) {
	if(velocity >= 0) {
		digitalWrite(motRightForward, HIGH);
		digitalWrite(motRightBack, LOW);
		analogWrite(motRightVelo, velocity);
	} else {
		digitalWrite(motRightForward, LOW);
		digitalWrite(motRightBack, HIGH);
		analogWrite(motRightVelo, -velocity);
	}
}

void motorTurnRight() {
	int velocity = 255;

	analogWrite(motLeftVelo, velocity);
	analogWrite(motRightVelo, velocity);

	digitalWrite(motLeftForward, LOW);
	digitalWrite(motLeftBack, HIGH);

	digitalWrite(motRightForward, HIGH);
	digitalWrite(motRightBack, LOW);

	delay(TURNING_TIME);
	motorStop();
}

void motorTurnBack() {
	int velocity = 255;
	
	analogWrite(motLeftVelo, velocity);
	analogWrite(motRightVelo, velocity);

	digitalWrite(motLeftForward, LOW);
	digitalWrite(motLeftBack, HIGH);

	digitalWrite(motRightForward, HIGH);
	digitalWrite(motRightBack, LOW);

	delay(2 * TURNING_TIME);
	motorStop();
}

void motorForward(int velocity) {
	analogWrite(motLeftVelo, velocity);
	analogWrite(motRightVelo, velocity);

	digitalWrite(motRightForward, HIGH);
	digitalWrite(motRightBack, LOW);

	digitalWrite(motLeftForward, HIGH);
	digitalWrite(motLeftBack, LOW);	
}

void headingVeloFix() {
	static int actuation = 100;
	float P = 10;
	float I = 20;

	int veloDelta = 1/motLeftDeltaTime - 1/motRightDeltaTime;
	int slotDelta = motLeftCounter - motRightCounter + 5;

	actuation = round(P * veloDelta + I * slotDelta);
	motorRotateRight(actuation);
}

void motorMoveOffset() {
	int velocity = 255;	

	analogWrite(motLeftVelo, velocity);
	analogWrite(motRightVelo, velocity);

	digitalWrite(motLeftForward, HIGH);
	digitalWrite(motRightBack, LOW);	

	digitalWrite(motRightForward, HIGH);
	digitalWrite(motRightBack, LOW);

	delay(SELF_LENGTH_OFFSET);
	motorStop();
}


void motorLeftCounterInt() {
	static unsigned long lastTime;
	unsigned long timeNow = millis();
	if(timeNow - lastTime < 1) return;

	motLeftCounter++;
	motLeftDeltaTime = timeNow - lastTime;
	lastTime = timeNow;
}

void motorRightCounterInt() {
	static unsigned long lastTime;
	unsigned long timeNow = millis();
	if(timeNow - lastTime < 1) return;

	motRightCounter++;
	motRightDeltaTime = timeNow - lastTime;
	lastTime = timeNow;
}