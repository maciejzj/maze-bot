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

/** @brief Turns the platform.
 *
 *  Utility for easily colling rotation to realtive positions of platform.
 *	Calls turning function with specified argument.
 *
 *	@param direction Relative direction the platform will turn to.
 *  @return Void.
 */
void platoformTurn(int direction);

/** @brief Turns the platofrm by given angle.
 *
 *  Rotates the platform till it reaches set point of turn angle.
 *  Counts slots and compares them with target calculated from
 *  given angle. Uses cascade regulation for precision and proper
 *  driving of the motors.
 *
 *  @param degree Tergeted degree of rotation, if positive
 *         turns right, negative turns left. Not recommended
 *         and pointless to use values greater than 180 degrees,
 *         waht results in longer rotation and precision loss.
 * 
 *  @return Void.
 */
void platformTurnAngle(int degree);

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