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

void platformTurn(int direction) {
	switch (direction) {
		case RIGHT:
			platformTurnAngle(-90);
			break;

		case LEFT:
			platformTurnAngle(90);
			break;

		case BACK:
			platformTurnAngle(180);
			break;
	}
}

void platformTurnAngle(int degree) {
	int actuationLeft;				///< Actuation of the left motor, steers the motor's PWM.
	int actuationRight;				///< Actuation of the right motor, steers the motor's PWM.
	float Pv = 1.2;					///< Proportional coefficient of (subordinate) velocity regulator.
	float Iv = 1.2;					///< Integral coefficient of (subordinate) velocity regulator.
	float Pp = 0.35;				///< Proportional coefficient of (precedent) position regulator.
	float setPointVeloRight;		///< Velocity set point for subordinate regulator of right motor.
	float setPointVeloLeft;			///< Velocity set point for subordinate regulator of left motor.
	bool leftIsStopped = false;		///< Indicator of left motor being stopped after it reaches posiotion set point.
	bool rightIsStopped = false;	///< Indicator of right motor being stopped after it reaches posiotion set point.
	float veloErrL = 0;             ///< Velocity (subordinate) regulator error for left motor
	float veloErr = 0; 				///< Velocity (subordinate) regulator error for right motor

	/* Clear initial values for encoder readouts */
	motLeftDeltaTime = 1;
	motRightDeltaTime = 1;

	motRightCounter = 0;
	motLeftCounter = 0;

	/* Calculate position target (set point) number of slots from given angle */
	float target = abs(SLOT_NUM_FOR_DEG_ROTATION(degree)); 

	/* Calculate direction sign, determines whether platform turns left or right */
	int direction = degree > 0 ? 1 : -1;

	/* Set the last time ISRs as the begging of the work of the regulator */
	lastTimeLeft = millis();
	lastTimeRight = millis();

	while(1) {
		int slotDeltaRight = target - motRightCounter;  ///< Error of precedent position regulator for right motor.
		int slotDeltaLeft = target - motLeftCounter;    ///< Error of precedent position regulator for left motor.

		setPointVeloRight = Pp * slotDeltaRight;
		setPointVeloLeft = Pp * slotDeltaLeft;
	
		/* Avoid too high velocity set points to elude wheel slips during long turns */
		if(setPointVeloRight > 16) setPointVeloRight = 16;
		if(setPointVeloLeft > 16) setPointVeloLeft = 16;

		/* Calulate velocity errors */
		float veloDelta = setPointVeloRight - (1.0/((float) motRightDeltaTime));  
		float veloDeltaL = setPointVeloLeft - (1.0/((float) motLeftDeltaTime));
		/* Get current time to compare it with last time of ISR and estimate integral */
		unsigned long compareTime = millis();
	
		/* PI regulator formula, calculates motors actuations */
		actuationRight = round(Pv * veloDelta + Iv * veloDelta * (compareTime - lastTimeRight));
		actuationLeft = round(Pv * veloDeltaL + Iv * veloDeltaL * (compareTime - lastTimeLeft));

		/* Prevent oversaturation of PWM */
		if (actuationRight > 255) actuationRight = 255;
		if (actuationLeft > 255) actuationLeft = 255;

		/* If target is reached stop the motor, otherwise actuate it */
		if (motLeftCounter>=target) {
			motorLeftStop(); leftIsStopped = true;
		} else
			motorRotateLeft(direction * actuationLeft);

		if (motRightCounter>=target) {
			motorRightStop();
			rightIsStopped = true;
		} else
			motorRotateRight(-direction * actuationRight);

		/* If both motors are stopped exit function */
		if(leftIsStopped && rightIsStopped) return;
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