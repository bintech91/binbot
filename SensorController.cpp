/*
 * SensorController.cpp
 *
 *  Created on: Aug 26, 2016
 *      Author: tanpt
 */

#include  "SensorController.h"

AnalogIn SensorController::sensorDistanceFront_(p1);
DigitalIn SensorController::sensorFrontRight_(p2);
DigitalIn SensorController::sensorFrontLeft_(p3);
DigitalIn SensorController::sensorBack_(p4);

AnalogIn SensorController::sensorDistanceRight_(p6);
AnalogIn SensorController::sensorDistanceLeft_(p5);

SensorController::SensorController() {

}

SensorController::~SensorController() {

}

void SensorController::init() {
    sensorFrontLeft_.mode(PullUp);
    sensorFrontRight_.mode(PullUp);
    sensorBack_.mode(PullUp);
}
uint16_t SensorController::distanceSensorRight() {
    uint16_t adc;
    uint16_t cm;
    uint16_t sensor = 0, i;

    for (i = 0; i < SENSOR_NOISE; i++) {
        adc = sensorDistanceRight_.read_u16();
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
        cm = sensor / SENSOR_NOISE;
    }
    return cm;
}

uint16_t SensorController::distanceSensorLeft() {
    uint16_t adc;
    uint16_t cm;
    uint16_t sensor = 0, i;

    for (i = 0; i < SENSOR_NOISE; i++) {
        adc = sensorDistanceLeft_.read_u16();
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
        cm = sensor / SENSOR_NOISE;
    }
    return cm;
}
uint16_t SensorController::distanceSensorFront() {
    uint16_t adc;
    uint16_t cm;
    uint16_t sensor = 0, i;

    for (i = 0; i < SENSOR_NOISE; i++) {
        adc = sensorDistanceFront_.read_u16();
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
        cm = sensor / SENSOR_NOISE;
    }
    return cm;
}

uint8_t SensorController::frontRightSensor() {
    uint16_t i, sensor = 0;

    for (i = 0; i < SENSOR_NOISE; i++) {
        wait(0.001);
        sensor = sensor + sensorFrontRight_;
    }
    if (sensor > SENSOR_NOISE / 2)
        return SENSOR_OFF;
    else
        return SENSOR_ON;
}
uint8_t SensorController::frontLeftSensor() {
    uint16_t i, sensor = 0;

    for (i = 0; i < SENSOR_NOISE; i++) {
        wait(0.001);
        sensor = sensor + sensorFrontLeft_;
    }
    if (sensor > SENSOR_NOISE / 2)
        return SENSOR_OFF;
    else
        return SENSOR_ON;
}
uint8_t SensorController::backSensor() {
    uint16_t i, sensor = 0;

    for (i = 0; i < SENSOR_NOISE; i++) {
        wait(0.001);
        sensor = sensor + sensorBack_;
    }
    if (sensor > SENSOR_NOISE / 2)
        return SENSOR_OFF;
    else
        return SENSOR_ON;
}
