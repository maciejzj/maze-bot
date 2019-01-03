/**
* \file defines.h
* \author Maciej Ziaja, Bartosz Staszulonek
* \brief Macros and defines for various MazeBot functions.
*
* \see https://github.com/MaciejZj/MazeBot
*/
 
/* Macros for directions */
#define BACK -1                 ///< Back of platform, where the PCB is.
#define RIGHT 0                 ///< Right side of platform.
#define LEFT 1                  ///< Left side of platform.
#define FRONT 2                 ///< Front of the platform, where the battery is.
 
/* Delay macros */
#define INITIAL_DELAY 3000      ///< Delay between power up and start of run routine.
#define MOTOR_STOP_DELAY 500    ///< Delay after motors stop, ensures stability of platform.
 
#define SAFE_DIST 15            ///< Distance that triggers obstacle detection by ultrasonic.
 
/* State machine macros */
#define IDLE 0                  ///< Idle state in which nothing happens
#define START 1                 ///< Restart encoders, drive motors forward
#define RUNNING 2               ///< Is running now, and avoids obstacles
#define STOP 3                  ///< Stop running, turn off engines, then go idle
 
/* Mechanical parameters */
#define SLOT_NUM 20.0           ///< Number of slots inside of the encoders disks.
#define WHEEL_DIAM 65.0         ///< Diameter of the wheels.
#define WHEELBASE 149.0         ///< Distance between centers of both wheels.
 
/* Macro function calculating number of slots needed to rotate the platform by given angle */
#define SLOT_NUM_FOR_DEG_ROTATION(DEGREE) (round(DEGREE / 360.0 * 2.0 * SLOT_NUM * WHEELBASE / WHEEL_DIAM))
 
/* Enable/disable debug */
#define TURN_ANGLE_DBG 1
#define HEADING_VELO_FIX_DBG 0
 
/* Debug macros */
#define PRINT_HEADING_VELO_FIX_DBG {                                              \
        Serial.println("======= headingVeloFix() debugging =======");             \
        Serial.println("********* master motor debugging *********");             \
        Serial.print("motLeftDeltaTime: "); Serial.println(motLeftDeltaTime);     \
        Serial.print("actuationLeft: "); Serial.println(actuationLeft);           \
        Serial.print("********** slave motor debugging *********");               \
        Serial.print("motRightDeltaTime: "); Serial.println(motRightDeltaTime);   \
        Serial.print("slotDelta: "); Serial.println(slotDelta);                   \
        Serial.print("veloDelta: "); Serial.println(veloDelta);                   \
        Serial.print("actuationRight: "); Serial.println(actuationRight);         \
}
 
#define PRINT_TURN_ANGLE_DBG {                                                                          \
        Serial.println("======= turnAngle() debugging =======");                                        \
        Serial.print("Slot target: "); Serial.println(target);                                          \
        Serial.print("SlotDeltaRight: "); Serial.println(slotDeltaRight);                               \
        Serial.print("SlotDeltaLeft: "); Serial.println(slotDeltaLeft);                                 \
        Serial.println("*************************************");                                        \
        Serial.print("setPointVeloRight: "); Serial.println(setPointVeloRight);                         \
        Serial.print("setPointVeloLeft: "); Serial.println(setPointVeloLeft);                           \
        Serial.println("*************************************");                                        \
        Serial.print("motRightDeltaTime: "); Serial.println(motRightDeltaTime);                         \
        Serial.print("motLeftDeltaTime: "); Serial.println(motLeftDeltaTime);                           \
        Serial.println("*************************************");                                        \
        Serial.print("veloDeltaRight: "); Serial.println(veloDeltaRight);                               \
        Serial.print("veloDeltaLeft: "); Serial.println(veloDeltaLeft);                                 \
        Serial.println("*************************************");                                        \
        Serial.print("compareTime - lastTimeRight: "); Serial.println(compareTime - lastTimeRight);     \
        Serial.print("compareTime - lastTimeLeft: "); Serial.println(compareTime - lastTimeLeft);       \
        Serial.println("*************************************");                                        \
        Serial.print("actuationRight: "); Serial.println(actuationRight);                               \
        Serial.print("actuationLeft: "); Serial.println(actuationLeft);                                 \
}
