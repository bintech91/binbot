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

enum BotState {

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
	uint8_t maxDistance = 30;

	BotState state;

	while (true) {
		distanceRight = sensors.distanceSensorRight();
		distanceLeft = sensors.distanceSensorLeft();
		distanceFront = sensors.distanceSensorFront();

		frontRight = sensors.frontRightSensor();
		frontLeft = sensors.frontLeftSensor();
		back = sensors.backSensor();

		if ((frontRight == SensorController::SENSOR_OFF)
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

		} else if ((frontRight == SensorController::SENSOR_OFF)
				&& (back == SensorController::SENSOR_OFF)) {
			motorController.moveFrontLeft(speed);
		} else if ((frontLeft == SensorController::SENSOR_OFF)
				&& (back == SensorController::SENSOR_OFF)) {
			motorController.moveFrontRight(speed);
		} else if ((frontRight == SensorController::SENSOR_OFF)) {
			if ((distanceFront > minDistance)
					&& (distanceFront < maxDistance)) {
				motorController.moveBackLeft(speed);
			} else if ((distanceRight > minDistance)
					&& (distanceRight < maxDistance)) {
				motorController.moveBackward(speed);
			} else if ((distanceLeft > minDistance)
					&& (distanceLeft < maxDistance)) {
				motorController.moveBackward(speed);
			} else {
				motorController.moveBackLeft(speed);
			}

		} else if ((frontLeft == SensorController::SENSOR_OFF)) {
			if ((distanceFront > minDistance)
					&& (distanceFront < maxDistance)) {
				motorController.moveBackRight(speed);
			} else if ((distanceRight > minDistance)
					&& (distanceRight < maxDistance)) {
				motorController.moveBackward(speed);
			} else if ((distanceLeft > minDistance)
					&& (distanceLeft < maxDistance)) {
				motorController.moveBackward(speed);
			} else {
				motorController.moveBackRight(speed);
			}
		} else if ((back == SensorController::SENSOR_OFF)) {
			motorController.moveForward(speed);
		} else {
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
				motorController.moveForward(speed);
			}
		}
	}
}
