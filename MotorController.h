/*
 * MotorController.h
 *
 *  Created on: Aug 23, 2016
 *      Author: tanpt
 */

#ifndef MOTORCONTROLLER_H_
#define MOTORCONTROLLER_H_

#include "common.h"

#include "IRController.h"

class MotorController {
public:

	MotorController();
	~MotorController();

	int8_t moveForward(uint8_t speed, uint8_t distance);

	int8_t moveBackward(uint8_t speed, uint8_t distance);

	int8_t turnRight(uint8_t radius);

	int8_t turnLeft(uint8_t radius);

private:

};

#endif /* MOTORCONTROLLER_H_ */
