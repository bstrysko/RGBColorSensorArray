#ifndef _RGB_COLOR_SENSOR_ARRAY_RGB_COLOR_SENSOR_H_
#define _RGB_COLOR_SENSOR_ARRAY_RGB_COLOR_SENSOR_H_

#include <inttypes.h>
#include <stdbool.h>

#include "RGBColorSensorPins.h"
#include "RGBColorSensorI2C.h"

#define LED_STATE_OFF 0
#define LED_STATE_ON 1
#define LED_STATE_TOGGLE 2

typedef struct
{
  RGBColorSensorPins pins;
  bool ledToggle;
  bool ledOn;
} RGBColorSensor;

void rgbColorSensorInit
(
  RGBColorSensor* s,
  RGBColorSensorReadDataCallback readDataCallback,
  RGBColorSensorWriteCallback writeCallback
);

uint8_t rgbColorSensorGetRed(RGBColorSensor* s);
uint8_t rgbColorSensorGetGreen(RGBColorSensor* s);
uint8_t rgbColorSensorGetBlue(RGBColorSensor* s);
bool rgbColorSensorGetDefect(RGBColorSensor* s);
uint8_t rgbColorSensorGetLEDState(RGBColorSensor* s);
void rgbColorSensorSetLEDState(RGBColorSensor* s, uint8_t state);
void rgbColorSensorToggleLEDState(RGBColorSensor* s);
void rgbColorSensorUpdate(RGBColorSensor* s);

#endif
