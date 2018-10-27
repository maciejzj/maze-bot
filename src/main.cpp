#include <Arduino.h>
#include "defines.h"
#include "platformMotors.h"

int motLeftForward = 2;
int motLeftBack = 3;
int motLeftVelo = 9;

int motRightForward = 4;
int motRightBack = 5;
int motRightVelo = 10;

void setup() {
	Serial.begin(9600); // for debug

	pinMode(motLeftForward, OUTPUT);
	pinMode(motLeftBack, OUTPUT);
	pinMode(motLeftVelo, OUTPUT);

	pinMode(motRightForward, OUTPUT);
	pinMode(motRightBack, OUTPUT);
	pinMode(motRightVelo, OUTPUT);
}

void loop() {
	
}