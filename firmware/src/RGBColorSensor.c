#include <RGBColorSensor.h>

void LED_OFF(RGBColorSensor* s);
void LED_ON(RGBColorSensor* s);

void rgbColorSensorInit
(
  RGBColorSensor* s,
  RGBColorSensorReadDataCallback readDataCallback,
  RGBColorSensorWriteCallback writeCallback
)
{
  s->readDataCallback = readDataCallback;
  s->writeCallback = writeCallback;
  rgbColorSensorSetLEDState(s, LED_STATE_OFF);
}

uint8_t rgbColorSensorGetRed(RGBColorSensor* s)
{
  //TODO: implement
  return 0;
}

uint8_t rgbColorSensorGetGreen(RGBColorSensor* s)
{
  //TODO: implement
  return 0;
}

uint8_t rgbColorSensorGetBlue(RGBColorSensor* s)
{
  //TODO: implement
  return 0;
}

bool rgbColorSensorGetDefect(RGBColorSensor* s)
{
  //TODO: implement
  return false;
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
  //TODO: implement
}

void LED_OFF(RGBColorSensor* s)
{
  s->ledOn = false;
  s->writeCallback(PIN_LED, STATE_LOW);
}

void LED_ON(RGBColorSensor* s)
{
  s->ledOn = true;
  s->writeCallback(PIN_LED, STATE_HIGH_Z);
}
