#include <Arduino.h>
#include <Servo.h>
#include <TimerOne.h>
#include <IRremote.h>
#include "defines.h"
#include "servoSensor.h"
#include "platformMotors.h"
#include "HC_SR04.h"

int motLeftForward = 10;			///< Left motor forward pin.
int motLeftBack = 12;				///< Left motor back pin.
int motLeftVelo = 11;				///< Left motor velocity PWM pin.

int motRightForward = 8;			///< Right motor forward pin.
int motRightBack = 9;				///< Right motor back pin.
int motRightVelo = 5;				///< Right motor velocity PWM pin.

int motLeftSlotSensor = 2;			///< Left motor slot sensor (encoder) interrupt pin.
int motRightSlotSensor = 1;			///< Right motor slot sensor (encoder) interrupt pin.
volatile int motLeftCounter = 0;	///< Counter of left motor's slots detected in current movement.
volatile int motRightCounter = 0;	///< Counter of right motor's slots detected in current movement.
unsigned long motLeftDeltaTime;		///< Time betweeen last left enoder's ISRs, indicates velocity.
unsigned long motRightDeltaTime;	///< Time betweeen last right enoder's ISRs, indicates velocity.

int servoPin = 13;					///< Servo control PWM pin.
Servo servoSensor;					///< Servo library global instance.

int ultrasonicTrig = 4;				///< Ultrasonic sensor trigger pin.
int ultrasonicEcho = 3;				///< Ultrasonic sensor echo pin.
int ultrasonicInt = 0;				///< Ultrasonic sensor interrupt pin.
HC_SR04 sensor(ultrasonicTrig, ultrasonicEcho, ultrasonicInt); ///< Ultrasonic sensor library instance.

int IRrecvPin = 7;					///< IR receiver interrupt and data pin.
IRrecv irrecv(IRrecvPin);			///< IR library global instance.
decode_results results;				///< IR received codes holding structure.

unsigned long forwardStartTim = 0;  ///< IR library global instance.
unsigned long forwardStopTim = 0;

volatile int state = START;			///< State machine state variable.
int backtrackCounter = 0;
   
void changeRunningState();
void corridorEscaper();

void setup() {
	Serial.begin(9600); // for debug
	Serial.print("Initialised serial");

	pinMode(motLeftForward, OUTPUT);
	pinMode(motLeftBack, OUTPUT);
	pinMode(motLeftVelo, OUTPUT);

	pinMode(motRightForward, OUTPUT);
	pinMode(motRightBack, OUTPUT);
	pinMode(motRightVelo, OUTPUT);

	attachInterrupt(digitalPinToInterrupt(motLeftSlotSensor), motorLeftCounterInt, CHANGE);
	attachInterrupt(digitalPinToInterrupt(motRightSlotSensor), motorRightCounterInt, CHANGE);

	servoSensor.attach(servoPin);
	turnServoSensor(FRONT);

	sensor.begin();
	sensor.start();

	irrecv.enableIRIn();
	attachInterrupt(digitalPinToInterrupt(IRrecvPin), changeRunningState, RISING);

	randomSeed(analogRead(0));

}

void loop() {
	switch(state) {
		case START:
			motorForward();
			sensor.start();
			state = RUNNING;
			break;

		case RUNNING:
			headingVeloFix();
			if(sensor.isFinished()) {
				if(sensor.getRange() < SAFE_DIST) {
					state = START;

					motorStop();
					forwardStopTim = millis();

					int direction = findUnobstructedDirection();
					motorTurn(direction);

					if (direction == BACK) backtrackCounter++;
					else backtrackCounter = 0;

					if(backtrackCounter == 2) {
						/* 	Disabled corridorEscaper() due to it being broken by 
							conflict of timers */
					}
				}
				sensor.start();
			}
			break;

		case STOP:
			motorStop();
			state = IDLE;
			break;
	}
}

void corridorEscaper() {
	unsigned long forwardDeltaTim = forwardStopTim - forwardStartTim;

	int direction = random(LEFT, RIGHT - 1);
	turnServoSensor(direction);
	sensor.start();

	Timer1.initialize(forwardDeltaTim * 1000); 
	Timer1.attachInterrupt(motorTurnBack);
	motorForward();

	while (true) {
		if(sensor.isFinished()) {
			if(sensor.getRange() > SAFE_DIST) {
				Timer1.detachInterrupt();

				motorStop();
				turnServoSensor(FRONT);

				motorMoveOffset();
				motorTurn(direction);

				break;
			}
		}
	}
}

void changeRunningState() {
	if (irrecv.decode(&results)) {
		unsigned long IRvalue = results.value;
		switch (IRvalue) {
			case 0x100CBCA:
				state = STOP;
				break;
			case 0x1009C9D:
				state = START;
				break;
		}
		irrecv.resume();
	}
}