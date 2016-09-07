/*
 * MotorController.h
 *
 *  Created on: Aug 23, 2016
 *      Author: tanpt
 */

#ifndef MOTORCONTROLLER_H_
#define MOTORCONTROLLER_H_

#include "common.h"

class MotorController {
public:
	enum Direction {
		DIRECTION_FORWARD = 0, DIRECTION_BACKWARD = 1
	};

	enum BoostState {
		BOOST_DISABLE = 0, BOOST_ENBALE = 1
	};

	MotorController();
	~MotorController();

	int8_t setMotorRight(Direction direction, uint16_t speed);

	int8_t setMotorLeft(Direction direction, uint16_t speed);

	int8_t moveForward(uint16_t speed);

	int8_t moveBackward(uint16_t speed);

	int8_t turnRight(uint16_t speed);

	int8_t turnLeft(uint16_t speed);

	int8_t moveBackRight(uint16_t speed);

	int8_t moveBackLeft(uint16_t speed);

	int8_t moveFrontRight(uint16_t speed);

	int8_t moveFrontLeft(uint16_t speed);

	int8_t setBoost(BoostState state);

private:
	static DigitalOut motorLeftDirection_;
	static PwmOut motorLeftSpeed_;
	static DigitalOut motorRightDirection_;
	static PwmOut motorRightSpeed_;

	static DigitalOut motorBoostSpeed_;
};

#endif /* MOTORCONTROLLER_H_ */
