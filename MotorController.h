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
        FORWARD = 0,
        BACKWARD = 1
    };

    MotorController();
    ~MotorController();

    int8_t setMotorRight(Direction direction, uint16_t speed);

    int8_t setMotorLeft(Direction direction, uint16_t speed);

    int8_t moveForward(uint16_t speed);

    int8_t moveBackward(uint16_t speed);

    int8_t turnRight(uint16_t speed);

    int8_t turnLeft(uint16_t speed);

private:
    static DigitalOut  motorLeftDirection_;
    static PwmOut      motorLeftSpeed_;
    static DigitalOut  motorRightDirection_;
    static PwmOut      motorRightSpeed_;
};

#endif /* MOTORCONTROLLER_H_ */
