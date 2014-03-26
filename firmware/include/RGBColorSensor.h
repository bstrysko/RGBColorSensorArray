#ifndef _RGB_COLOR_SENSOR_ARRAY_RGB_COLOR_SENSOR_H_
#define _RGB_COLOR_SENSOR_ARRAY_RGB_COLOR_SENSOR_H_

#include <inttypes.h>
#include <stdbool.h>

#include "GPins.h"
#include "RGBColorSensorI2C.h"

#define LED_STATE_OFF 0
#define LED_STATE_ON 1
#define LED_STATE_TOGGLE 2

typedef struct RGBColorSensor_t RGBColorSensor;

typedef void (*RGBColorSensorProcessCallback)(RGBColorSensor* s);

struct RGBColorSensor_t
{
  GPins pins;
  RGBColorSensorProcessCallback processCallback;
  bool ledToggle;
  bool ledOn; 
  bool defect;
  uint8_t red;
  uint8_t green;
  uint8_t blue;
};

void rgbColorSensorInit
(
  RGBColorSensor* s,
  GPinsReadDataCallback readDataCallback,
  GPinsWriteCallback writeCallback,
  RGBColorSensorProcessCallback processCallback
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
