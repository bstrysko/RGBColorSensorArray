#ifndef _RGB_COLOR_SENSOR_ARRAY_RGB_COLOR_SENSOR_PINS_H_
#define _RGB_COLOR_SENSOR_ARRAY_RGB_COLOR_SENSOR_PINS_H_

#include <inttypes.h>
#include <stdbool.h>

#define STATE_HIGH_Z 0
#define STATE_LOW 1
#define STATE_HIGH 2

#define PIN_CLK 0
#define PIN_DATA 1
#define PIN_LED 2

typedef bool (*RGBColorSensorReadDataCallback)();
typedef void (*RGBColorSensorWriteCallback)(uint8_t, uint8_t);

typedef struct {
  RGBColorSensorReadDataCallback readDataCallback;
  RGBColorSensorWriteCallback writeCallback;
} RGBColorSensorPins;

#endif
