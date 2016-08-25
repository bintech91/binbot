/*
 * main.cpp
 *
 *  Created on: Aug 23, 2016
 *      Author: tanpt
 */

#include "common.h"
#include "MotorController.h"
#include "Buzzer.h"

//#include "ble/BLE.h"
//#include "ble/services/iBeacon.h"
//#include "ble/services/UARTService.h"


MotorController motorController;
Buzzer buzzer;

//// Sensor
#define NOISE 5
//#define DEBUG

#ifdef DEBUG
Serial pc(p10, p11);
#endif

Ticker ticker;
AnalogIn analog_ir(p1);
DigitalIn SEN_UP_R(p2);
DigitalIn SEN_UP_L(p3);
DigitalIn SEN_DOWN(p4);
DigitalIn SEN_IR(p6);

#define ON      0
#define OFF     1
#define VREF    3300.0  //mV

uint16_t g_time_led = 0;

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////
//////////////////////////////////////////////////
/*
 * @param    none.
 * @return   Distance (cm), 1-80 cm.
 */
uint16_t sensor_ir(void) {
	uint16_t adc;
	uint16_t cm;
	uint16_t sensor = 0, i;

	for (i = 0; i < NOISE; i++) {
		adc = analog_ir.read_u16();
		adc = 750 - adc;
		if (adc > 60000)
			cm = 1;
		else if (adc > 600)
			cm = 0;
		else if (adc > 550)
			cm = adc / 8;
		else if (adc > 500)
			cm = adc / 10;
		else if (adc > 450)
			cm = adc / 12;
		else if (adc > 400)
			cm = adc / 14;
		else if (adc > 350)
			cm = adc / 16;
		else if (adc > 300)
			cm = adc / 18;
		else if (adc > 200)
			cm = adc / 16;
		else if (adc > 200)
			cm = adc / 14;
		else if (adc > 150)
			cm = adc / 12;
		else if (adc > 100)
			cm = adc / 10;
		else if (adc > 60)
			cm = adc / 9;
		else if (adc > 30)
			cm = adc / 8;
		else if (adc > 0)
			cm = adc / 7;

		wait(0.001);
		sensor = sensor + cm;
		if (cm == 0)
			break;
		cm = sensor / NOISE;
	}

#ifdef DEBUG
	pc.printf("\r\n %d adc, %d cm", adc, cm);
#endif
	return cm;
}

//////////////////////////////////////////////////
/*
 * @param    none.
 * @return   ON or OFF.
 */
uint8_t sensor_ir2(void) {
	uint16_t i, sensor = 0;

	for (i = 0; i < NOISE; i++) {
		wait(0.001);
		sensor = sensor + SEN_IR;
	}
	if (sensor > NOISE / 2)
		return OFF;
	else
		return ON;
}

//////////////////////////////////////////////////
/*
 * @param    none.
 * @return   ON or OFF.
 */
uint8_t sensor_up_left(void) {
	uint16_t i, sensor = 0;

	for (i = 0; i < NOISE; i++) {
		wait(0.001);
		sensor = sensor + SEN_UP_L;
	}
	if (sensor > NOISE / 2)
		return OFF;
	else
		return ON;
}
//////////////////////////////////////////////////
/*
 * @param    none.
 * @return   ON or OFF.
 */
uint8_t sensor_up_right(void) {
	uint16_t i, sensor = 0;

	for (i = 0; i < NOISE; i++) {
		wait(0.001);
		sensor = sensor + SEN_UP_R;
	}
	if (sensor > NOISE / 2)
		return OFF;
	else
		return ON;
}
//////////////////////////////////////////////////
/*
 * @param    none.
 * @return   ON or OFF.
 */
uint8_t sensor_down(void) {
	uint16_t i, sensor = 0;

	for (i = 0; i < NOISE; i++) {
		wait(0.001);
		sensor = sensor + SEN_DOWN;
	}
	if (sensor > NOISE / 2)
		return OFF;
	else
		return ON;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
void periodicCallback(void) {
	g_time_led++;
	if (g_time_led >= 1000) {
		g_time_led = 0;
		led1 = !led1;
	}   //DIR_L = !DIR_L; DIR_R = !DIR_R;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

int main(void) {
	wait(0.1);
	//Init Hardware
	SEN_UP_L.mode(PullUp);
	SEN_UP_R.mode(PullUp);
	SEN_DOWN.mode(PullUp);
	SEN_IR.mode(PullUp);

	buzzer.turnOn();

	//Init interupt Timer
	ticker.attach(periodicCallback, 0.00015);
	wait(0.5);
	while (true) {
		//rotator_right(20);
		uint8_t sen_in = sensor_ir();
		if ((sen_in > 0) && (sen_in < 50)) {
			motorController.moveForward(1000);
			while ((sensor_up_left() == OFF) && (sensor_up_right() == OFF)) {
				motorController.moveBackward(1000);
			}
		} else {
			motorController.turnRight(1000);
		}
	}
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
 led1 = 1; DIR_L = 0; DIR_R = 0; PWM_L = 0;  PWM_R = 0;

 //Init interupt Timer
 ticker.attach(periodicCallback, 0.00015);
 wait(0.5);
 while (true) {
 //rotator_right(20);
 uint8_t sen_in = sensor_ir();
 if( (sen_in > 0) && (sen_in < 50) )
 {
 move_up(100, 100);
 while( (sensor_up_left() == OFF) && (sensor_up_right() == OFF) ){
 move_down(40,40);
 }
 } else {
 rotator_right(100);
 }
 }
 }
 */

