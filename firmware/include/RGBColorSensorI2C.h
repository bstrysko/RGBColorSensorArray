#ifndef _RGB_COLOR_SENSOR_ARRAY_RGB_COLOR_SENSOR_I2C_H_
#define _RGB_COLOR_SENSOR_ARRAY_RGB_COLOR_SENSOR_I2C_H_

#include "RGBColorSensorPins.h"

#include <stddef.h>
#include <util/delay.h>

void rgbColorSensorI2CInit(RGBColorSensorPins* pins);
size_t rgbColorSensorI2CRead(RGBColorSensorPins* pins, uint8_t* buffer, size_t n);
size_t rgbColorSensorI2CWrite(RGBColorSensorPins* pins, uint8_t* buffer, size_t n);

#endif
