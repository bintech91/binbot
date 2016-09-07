/*
 * MotorController.cpp
 *
 *  Created on: Aug 23, 2016
 *      Author: tanpt
 */

#include "MotorController.h"

DigitalOut MotorController::motorLeftDirection_(p25);
PwmOut MotorController::motorLeftSpeed_(p23);
DigitalOut MotorController::motorRightDirection_(p28);
PwmOut MotorController::motorRightSpeed_(p24);

DigitalOut MotorController::motorBoostSpeed_(p20);

MotorController::MotorController() {
	motorRightDirection_ = DIRECTION_FORWARD;
	motorRightSpeed_.period_ms(200);
	motorLeftDirection_ = DIRECTION_FORWARD;
	motorLeftSpeed_.period_ms(200);
}

MotorController::~MotorController() {

}

int8_t MotorController::setMotorRight(Direction direction, uint16_t speed) {
	motorRightDirection_ = direction;
	motorRightSpeed_.pulsewidth_ms(speed);
	return 0;
}

int8_t MotorController::setMotorLeft(Direction direction, uint16_t speed) {
	motorLeftDirection_ = direction;
	motorLeftSpeed_.pulsewidth_ms(speed);
	return 0;
}

int8_t MotorController::moveForward(uint16_t speed) {
	motorRightDirection_ = DIRECTION_FORWARD;
	motorRightSpeed_.pulsewidth_ms(speed);
	motorLeftDirection_ = DIRECTION_FORWARD;
	motorLeftSpeed_.pulsewidth_ms(speed);

	return 0;
}

int8_t MotorController::moveBackward(uint16_t speed) {
	motorRightDirection_ = DIRECTION_BACKWARD;
	motorRightSpeed_.pulsewidth_ms(speed);
	motorLeftDirection_ = DIRECTION_BACKWARD;
	motorLeftSpeed_.pulsewidth_ms(speed);

	return 0;
}

int8_t MotorController::turnRight(uint16_t speed) {
	motorRightDirection_ = DIRECTION_BACKWARD;
	motorRightSpeed_.pulsewidth_ms(speed);
	motorLeftDirection_ = DIRECTION_FORWARD;
	motorLeftSpeed_.pulsewidth_ms(speed);

	return 0;
}

int8_t MotorController::turnLeft(uint16_t speed) {
	motorRightDirection_ = DIRECTION_FORWARD;
	motorRightSpeed_.pulsewidth_ms(speed);
	motorLeftDirection_ = DIRECTION_BACKWARD;
	motorLeftSpeed_.pulsewidth_ms(speed);

	return 0;
}

int8_t MotorController::moveBackRight(uint16_t speed) {
	motorRightDirection_ = DIRECTION_BACKWARD;
	motorRightSpeed_.pulsewidth_ms(speed);
	motorLeftDirection_ = DIRECTION_BACKWARD;
	motorLeftSpeed_.pulsewidth_ms(speed / 3);

	return 0;
}

int8_t MotorController::moveBackLeft(uint16_t speed) {
	motorRightDirection_ = DIRECTION_BACKWARD;
	motorRightSpeed_.pulsewidth_ms(speed / 3);
	motorLeftDirection_ = DIRECTION_BACKWARD;
	motorLeftSpeed_.pulsewidth_ms(speed);

	return 0;
}

int8_t MotorController::moveFrontRight(uint16_t speed) {
	motorLeftDirection_ = DIRECTION_FORWARD;
	motorLeftSpeed_.pulsewidth_ms(speed);
	motorRightDirection_ = DIRECTION_FORWARD;
	motorRightSpeed_.pulsewidth_ms(speed / 50);

	return 0;
}

int8_t MotorController::moveFrontLeft(uint16_t speed) {
	motorRightDirection_ = DIRECTION_FORWARD;
	motorRightSpeed_.pulsewidth_ms(speed);
	motorLeftDirection_ = DIRECTION_FORWARD;
	motorLeftSpeed_.pulsewidth_ms(speed / 50);

	return 0;
}
int8_t MotorController::setBoost(BoostState state) {
	motorBoostSpeed_ = state;
}

