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
void platformTurn(int direction);

/** @brief Turns the platform by given angle.
 *
 *  Rotates the platform till it reaches set point of turn angle.
 *  Counts slots and compares them with target calculated from
 *  given angle. Uses cascade regulation for precision and proper
 *  driving of the motors.
 *
 *  @param degree Targeted degree of rotation, if positive
 *         turns right, negative turns left. Not recommended
 *         and pointless to use values greater than 180 degrees,
 *         waht results in longer rotation and precision loss.
 * 
 *  @return Void.
 */
void platformTurnAngle(int degree);

/** @brief Rotates the left motor with given valocity (actuation).
 *
 *  Steers the motor's pins and PWM actuate the left motor.
 *
 *  @param velocity Actuation that will drive the PWM steering the
 *         motor's velocity (precisely force momentum). Ranges from
 *         0 to 255.
 * 
 *  @return Void.
 */
void motorRotateLeft(int velocity);

/** @brief Rotates the right motor with given valocity (actuation).
 *
 *  Steers the motor's pins and PWM actuate the right motor.
 *
 *  @param velocity Actuation that will drive the PWM steering the
 *         motor's velocity (precisely force momentum). Ranges from
 *         0 to 255.
 * 
 *  @return Void.
 */
void motorRotateRight(int velocity);

/** @brief Resets encoders values when heading new direction after stop.
 * 
 *  @return Void.
 */
inline void resetEncoders();

/** @brief Actuates motors to run foward while keeping the straight direction.
 *
 *  Implements velcity regualtion for both motors. One has a fixed set point
 *  and acts as master, while the second one, slave has floating set point to
 *  synchronise with master. This ensures keeping the heading direction.
 *
 *  @return Void.
 */
void headingVeloFix();

/** @brief ISR for left slot sensor interrupt.
 *
 *  Increments the counter and calculates delta time for velocity estimation.
 *  Provides simple debouncing.
 *
 *  @return Void.
 */
void motorLeftCounterInt();

/** @brief ISR for right slot sensor interrupt.
 *
 *  Increments the counter and calculates delta time for velocity estimation.
 *  Provides simple debouncing.
 *
 *  @return Void.
 */
void motorRightCounterInt();