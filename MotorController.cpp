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

MotorController::MotorController() {
    motorRightDirection_ = FORWARD;
    motorRightSpeed_.period_ms(1000);
    motorLeftDirection_ = FORWARD;
    motorLeftSpeed_.period_ms(1000);
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
    motorRightDirection_ = FORWARD;
    motorRightSpeed_.pulsewidth_ms(speed);
    motorLeftDirection_ = FORWARD;
    motorLeftSpeed_.pulsewidth_ms(speed);
    return 0;
}

int8_t MotorController::moveBackward(uint16_t speed) {
    motorRightDirection_ = BACKWARD;
    motorRightSpeed_.pulsewidth_ms(speed);
    motorLeftDirection_ = BACKWARD;
    motorLeftSpeed_.pulsewidth_ms(speed);
    return 0;
}

int8_t MotorController::turnRight(uint16_t speed) {
    motorRightDirection_ = BACKWARD;
    motorRightSpeed_.pulsewidth_ms(speed);
    motorLeftDirection_ = FORWARD;
    motorLeftSpeed_.pulsewidth_ms(speed);
    return 0;
}

int8_t MotorController::turnLeft(uint16_t speed) {
    motorRightDirection_ = FORWARD;
    motorRightSpeed_.pulsewidth_ms(speed);
    motorLeftDirection_ = BACKWARD;
    motorLeftSpeed_.pulsewidth_ms(speed);
    return 0;
}
