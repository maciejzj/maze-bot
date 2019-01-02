/** @brief Stops the motors.
 *
 *  Stops both motors and delays next action to ensure mechanical stability.
 *
 *  @return Void.
 */
void motorStop();

/** @brief Stops left motor.
 *
 *  Drives the motor low and zeros the velocity.
 *
 *  @return Void.
 */
void motorLeftStop();

/** @brief Stops right motor.
 *
 *  Drives the motor low and zeros the velocity.
 *
 *  @return Void.
 */
void motorRightStop();
void motorTurn(int direction);
void motorTurnLeft();
void motorRotateLeft(int velocity);
void motorTurnRight();
void motorRotateRight(int velocity);
void motorTurnBack();
void motorForward(int velocity = 100);
void headingVeloFix();
void motorMoveOffset();
void motorLeftCounterInt();
void motorRightCounterInt();