/*
 * main.cpp
 *
 *  Created on: Aug 23, 2016
 *      Author: tanpt
 */

#include "common.h"
#include "MotorController.h"
#include "SensorController.h"

//#include "ble/BLE.h"
//#include "ble/services/iBeacon.h"
//#include "ble/services/UARTService.h"

MotorController motorController;
SensorController sensors;

//// Sensor
#define NOISE 5
//#define DEBUG

#ifdef DEBUG
Serial pc(p10, p11);
#endif
Ticker ticker;

#define VREF    3300.0  //mV

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////
void periodicCallback(void) {

}

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

typedef enum BotState {
	BOT_FORWARD = 0,
	BOT_BACKWARD,
	BOT_BACKWARD_RIGHT,
	BOT_BACKWARD_LEFT,
	BOT_RIGHT,
	BOT_LEFT
} BotState;

int main(void) {
//Init Hardware
	sensors.init();

	wait(0.1);

	uint8_t distanceRight;
	uint8_t distanceLeft;
	uint8_t distanceFront;

	uint8_t frontRight;
	uint8_t frontLeft;
	uint8_t back;

	uint16_t speed = 1000;
	uint8_t minDistance = 0;
	uint8_t maxDistance = 24;

	BotState state = BOT_FORWARD;

	while (true) {
		distanceRight = sensors.distanceSensorRight();
		distanceLeft = sensors.distanceSensorLeft();
		distanceFront = sensors.distanceSensorFront();

		frontRight = sensors.frontRightSensor();
		frontLeft = sensors.frontLeftSensor();
		back = sensors.backSensor();
		if ((frontRight == SensorController::SENSOR_ON)
				&& (frontLeft == SensorController::SENSOR_ON)
				&& (back == SensorController::SENSOR_ON)) {
			goto CHECK_ENEMY;
		} else if ((frontRight == SensorController::SENSOR_OFF)
				&& (frontLeft == SensorController::SENSOR_OFF)) {
			if ((distanceFront > minDistance)
					&& (distanceFront < maxDistance)) {
				motorController.moveBackward(speed);
			} else if ((distanceRight > minDistance)
					&& (distanceRight < maxDistance)) {
				motorController.moveBackLeft(speed);
			} else if ((distanceLeft > minDistance)
					&& (distanceLeft < maxDistance)) {
				motorController.moveBackRight(speed);
			} else {
				motorController.moveBackward(speed);
			}
			state = BOT_BACKWARD;
		} else if ((frontRight == SensorController::SENSOR_OFF)
				&& (back == SensorController::SENSOR_OFF)) {
			motorController.turnLeft(speed);
			state = BOT_BACKWARD_LEFT;
		} else if ((frontLeft == SensorController::SENSOR_OFF)
				&& (back == SensorController::SENSOR_OFF)) {
			motorController.turnRight(speed);
			state = BOT_BACKWARD_RIGHT;
		} else if ((frontRight == SensorController::SENSOR_OFF)) {
			if (state != BOT_BACKWARD_RIGHT) {
				motorController.turnLeft(speed);
				state = BOT_BACKWARD_LEFT;
			}
		} else if ((frontLeft == SensorController::SENSOR_OFF)) {
			if (state != BOT_BACKWARD_LEFT) {
				motorController.turnRight(speed);
				state = BOT_BACKWARD_RIGHT;
			}
		} else if ((back == SensorController::SENSOR_OFF)) {
			motorController.moveForward(speed);
			state = BOT_FORWARD;
		} else {
			CHECK_ENEMY: {
				if ((distanceFront > minDistance)
						&& (distanceFront < maxDistance)) {
					motorController.moveForward(speed);
					wait_ms(50);
				} else if ((distanceRight > minDistance)
						&& (distanceRight < maxDistance)) {
					motorController.turnRight(speed);
					distanceFront = sensors.distanceSensorFront();
					if ((distanceFront > minDistance)
							&& (distanceFront < maxDistance)) {
						motorController.moveForward(speed);
						wait_ms(50);
					}
				} else if ((distanceLeft > minDistance)
						&& (distanceLeft < maxDistance)) {
					motorController.turnLeft(speed);
					distanceFront = sensors.distanceSensorFront();
					if ((distanceFront > minDistance)
							&& (distanceFront < maxDistance)) {
						motorController.moveForward(speed);
						wait_ms(50);
					}
				} else {
					switch (state) {
					case BOT_FORWARD:
						motorController.moveForward(speed);
						break;
					case BOT_BACKWARD:
						motorController.moveBackward(speed);
						wait(0.45);
						state = BOT_RIGHT;
						break;
					case BOT_BACKWARD_RIGHT:
						motorController.moveBackward(speed);
						wait(0.45);
						state = BOT_RIGHT;
						break;
					case BOT_BACKWARD_LEFT:
						motorController.moveBackward(speed);
						wait(0.45);
						state = BOT_LEFT;
						break;
					case BOT_RIGHT:
						motorController.turnRight(speed);
						wait(0.6);
						state = BOT_FORWARD;
						break;
					case BOT_LEFT:
						motorController.turnLeft(speed);
						wait(0.6);
						state = BOT_FORWARD;
						break;
					default:
						motorController.moveForward(speed);
						break;
					}
				}
			}
		}
	}
}
