/*
 * SensorController.h
 *
 *  Created on: Aug 26, 2016
 *      Author: tanpt
 */

#ifndef SENSORCONTROLLER_H_
#define SENSORCONTROLLER_H_

#include "common.h"

//// Sensor
#define SENSOR_NOISE 5

class SensorController {
public:
	SensorController();
	~SensorController();

	enum SensorState {
		SENSOR_ON = 0, SENSOR_OFF = 1
	};

	void init();

	uint16_t distanceSensor();

	uint8_t frontRightSensor();
	uint8_t frontLeftSensor();
	uint8_t backSensor();

private:

	static AnalogIn analogIR_;
	static DigitalIn sensorFrontRight_;
	static DigitalIn sensorFrontLeft_;
	static DigitalIn sensorBack_;
	static DigitalIn sensorIR_;
};

#endif /* SENSORCONTROLLER_H_ */
