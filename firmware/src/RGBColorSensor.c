#include <RGBColorSensor.h>

void LED_OFF(RGBColorSensor* s);
void LED_ON(RGBColorSensor* s);

void rgbColorSensorInit
(
  RGBColorSensor* s,
  GPinsReadDataCallback readDataCallback,
  GPinsWriteCallback writeCallback,
  RGBColorSensorProcessCallback processCallback
)
{
  s->pins.readDataCallback = readDataCallback;
  s->pins.writeCallback = writeCallback;
  s->processCallback = processCallback;
  rgbColorSensorI2CInit(&(s->pins));
  rgbColorSensorSetLEDState(s, LED_STATE_OFF);
  s->defect = false;
  s->red = 0;
  s->green = 0;
  s->blue = 0;
}

uint8_t rgbColorSensorGetRed(RGBColorSensor* s)
{
  return s->red;
}

uint8_t rgbColorSensorGetGreen(RGBColorSensor* s)
{
  return s->green;
}

uint8_t rgbColorSensorGetBlue(RGBColorSensor* s)
{
  return s->blue;
}

bool rgbColorSensorGetDefect(RGBColorSensor* s)
{
  return s->defect;
}

uint8_t rgbColorSensorGetLEDState(RGBColorSensor* s)
{
  if(s->ledToggle)
  {
    return LED_STATE_TOGGLE;
  }
  else
  {
    return (s->ledOn ? LED_STATE_ON : LED_STATE_OFF); 
  }
}

void rgbColorSensorSetLEDState(RGBColorSensor* s, uint8_t state)
{
  if(state < 3)
  {
    s->ledOn = ((state == LED_STATE_ON) ? true : false);
    s->ledToggle = ((state == LED_STATE_TOGGLE) ? true : false);

    if(s->ledOn)
    {
      LED_ON(s);      
    }
    else
    {
      LED_OFF(s);
    }
  }
}

void rgbColorSensorToggleLEDState(RGBColorSensor* s)
{
  if(s->ledToggle)
  {
    if(s->ledOn)
    {
      LED_OFF(s);
    }
    else
    {
      LED_ON(s);
    }
  }
}

void rgbColorSensorUpdate(RGBColorSensor* s)
{
  s->processCallback(s);
}

void LED_OFF(RGBColorSensor* s)
{
  s->ledOn = false;
  s->pins.writeCallback(PIN_LED, STATE_LOW);
}

void LED_ON(RGBColorSensor* s)
{
  s->ledOn = true;
  s->pins.writeCallback(PIN_LED, STATE_HIGH_Z);
}
