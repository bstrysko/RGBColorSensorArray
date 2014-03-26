#ifndef _RGB_COLOR_SENSOR_ARRAY_RGB_COLOR_SENSOR_I2C_H_
#define _RGB_COLOR_SENSOR_ARRAY_RGB_COLOR_SENSOR_I2C_H_

#include "SI2CMaster.h"

#include <util/delay.h>

void rgbColorSensorI2CInit(GPins* pins);

uint8_t rgbColorSensorI2CReadID(GPins* pins);
void rgbColorSensorI2CReadColor(GPins* pins, uint16_t* a, uint16_t* r, uint16_t* g, uint16_t* b);

#endif
