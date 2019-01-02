/* Macros for directions */
#define BACK -1
#define RIGHT 0
#define LEFT 1
#define FRONT 2

/* Delay macros */
#define INITIAL_DELAY 3000      ///< Delay between power up and start of run routine.
#define MOTOR_STOP_DELAY 500    ///< Delay after motors stop, ensures stability of platform.

#define SAFE_DIST 15            ///< Distance that triggers obstacle detection by ultrasonic.

/* State machine macros */
#define IDLE 0
#define START 1
#define RUNNING 2
#define STOP 3

/* Mechanical parameters */
#define SLOT_NUM 20.0           ///< Number of slots inside of the encoders disks.
#define WHEEL_DIAM 65.0         ///< Diameter of the wheels.
#define WHEELBASE 149.0         ///< Distance between centers of both wheels.

/* Macro function calculating number of slots needed to rotate the platform by given angle */
#define SLOT_NUM_FOR_DEG_ROTATION(DEGREE) (round(DEGREE / 360.0 * 2.0 * SLOT_NUM * WHEELBASE / WHEEL_DIAM))