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

struct RGBColorSensor_t
{
  GPins pins;
  bool ledToggle;
  bool ledOn; 
};

void rgbColorSensorInit
(
  RGBColorSensor* s,
  GPinsReadDataCallback readDataCallback,
  GPinsWriteCallback writeCallback
);

void rgbColorSensorReadColor(RGBColorSensor* s, uint16_t* a, uint16_t* r, uint16_t* g, uint16_t* b);
uint8_t rgbColorSensorGetLEDState(RGBColorSensor* s);
void rgbColorSensorSetLEDState(RGBColorSensor* s, uint8_t state);
void rgbColorSensorToggleLEDState(RGBColorSensor* s);

#endif
