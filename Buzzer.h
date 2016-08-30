/*
 * Buzzer.h
 *
 *  Created on: Aug 23, 2016
 *      Author: tanpt
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include "common.h"

class Buzzer {

public:
    Buzzer();
    ~Buzzer();

    void turnOn();

    void turnOff();

private:
    static DigitalOut  buzzer_;
};


#endif /* BUZZER_H_ */
