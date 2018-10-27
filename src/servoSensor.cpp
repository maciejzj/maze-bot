#include <Servo.h>
#include "servoSensor.h"
#include "defines.h"

extern Servo servoSensor;

void turnServoSensor(int direction) {
    switch(direction) {
        case RIGHT:
			servoSensor.write(0);
			break;
		
		case FRONT:
			servoSensor.write(90);
			break;

		case LEFT:
			servoSensor.write(180);
			break;
    }
}