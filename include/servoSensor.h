/** @brief Turns servo at given direction.
 *
 *	@param direction Relative direction the platform will turn to.
 *  @return Void.
 */
void turnServoSensor(int direction);

/** @brief Finds direction with no obstacles.
 *
 *  Uses ultrasonic mount on the servo to check surroundings and find
 *  clear path.
 *
 *  @return Found direction with no obstacles.
 */
int findUnobstructedDirection();