#include <Arduino.h>
#include <Servo.h>
#include <TimerOne.h>
#include <IRremote.h>
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

int servoPin = 11;
Servo servoSensor;

int ultrasonicTrig = 2;
int ultrasonicEcho = 3;
int ultrasonicInt = 0;
HC_SR04 sensor(ultrasonicTrig, ultrasonicEcho, ultrasonicInt);

int IRrecvPin = 1;
IRrecv irrecv(IRrecvPin);
decode_results results;

unsigned long forwardStartTim = 0;
unsigned long forwardStopTim = 0;

volatile int state = 1;
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

	servoSensor.attach(servoPin);
	turnServoSensor(FRONT);

	sensor.begin();
	sensor.start();

	irrecv.enableIRIn();
	attachInterrupt(digitalPinToInterrupt(IRrecvPin), changeRunningState, RISING);

	randomSeed(analogRead(0));
	motorForward();
	forwardStartTim = millis();
}

void loop() {
	if(sensor.isFinished()) {
		if(sensor.getRange() < SAFE_DIST) {
			motorStop();
			forwardStopTim = millis();

			int direction = findUnobstructedDirection();
			motorTurn(direction);

			if (direction == BACK) backtrackCounter++;
			else backtrackCounter = 0;

			if(backtrackCounter == 2) {
				corridorEscaper();
			}

			motorForward();
			forwardStartTim = millis();
		}
		
		sensor.start();
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
		unsigned long odczyt = results.value;
		switch (odczyt) {
			case 0x100CBCA:
				state = 0;
				break;
			case 0x1009C9D:
				state = 1;
				break;
		}
		irrecv.resume();
	}
}