/*
 * Buzzer.cpp
 *
 *  Created on: Aug 23, 2016
 *      Author: tanpt
 */

#include "Buzzer.h"

static DigitalOut  Buzzer::buzzer_(LED1, 1);

Buzzer::Buzzer(){
}

Buzzer::~Buzzer(){
}

void Buzzer::turnOn(){
	buzzer_ = 1;
}

void Buzzer::turnOff(){
	buzzer_ = 0;
}
