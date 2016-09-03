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
int main(void) {
	wait(0.1);
//Init Hardware

	sensors.init();

//Init interupt Timer
	ticker.attach(periodicCallback, 0.00015);
	wait(0.5);

	while (true) {
		//rotator_right(20);
		uint8_t sen_in = sensors.distanceSensor();
		if ((sensors.frontLeftSensor() == SensorController::SENSOR_OFF)
				&& (sensors.frontRightSensor() == SensorController::SENSOR_OFF)) {
			motorController.moveBackward(1000);
			wait(1);
		} else if (sensors.frontLeftSensor() == SensorController::SENSOR_OFF) {
			motorController.moveBackRight(1000);
			wait(1);
		} else if (sensors.frontRightSensor() == SensorController::SENSOR_OFF) {
			motorController.moveBackLeft(1000);
			wait(1);
		} else if (sensors.backSensor() == SensorController::SENSOR_OFF) {
			motorController.moveForward(1000);
			wait(1);
		} else {
			if ((sen_in > 0) && (sen_in <= 70)) {
				motorController.moveForward(1000);
				wait(0.1);
			} else {
				motorController.turnRight(500);
				wait_us(100);
			}
		}
	}

//    while (true) {
//        //rotator_right(20);
//        uint8_t sen_in = sensors.distanceSensor();
//        if ((sen_in > 0) && (sen_in < 30)) {
//            if ((sensors.frontLeftSensor() == SensorController::SENSOR_OFF) && (sensors.frontRightSensor() == SensorController::SENSOR_OFF)) {
//                motorController.moveBackward(1000);
//                wait(2);
//            } else {
//                motorController.moveForward(1000);
//            }
//
//        } else {
//            if ((sensors.frontLeftSensor() == SensorController::SENSOR_OFF) && (sensors.frontRightSensor() == SensorController::SENSOR_OFF)) {
//                motorController.moveBackward(1000);
//                wait(2);
//            } else {
//                motorController.turnRight(1000);
//            }
//        }
//    }
}

/*
 int main(void)
 {
 wait(0.1);
 //Init Hardware
 SEN_UP_L.mode(PullUp);
 SEN_UP_R.mode(PullUp);
 SEN_DOWN.mode(PullUp);
 SEN_IR.mode(PullUp);

 //Init interupt Timer
 ticker.attach(periodicCallback, 0.00015);
 wait(0.5);
 while (true) {
 //rotator_right(20);
 uint8_t sen_in = distanceSensor();
 if( (sen_in > 0) && (sen_in < 50) )
 {
 move_up(100, 100);
 while( (frontLeftSensor() == OFF) && (frontRightSensor() == OFF) ){
 move_down(40,40);
 }
 } else {
 rotator_right(100);
 }
 }
 }
 */

