#include <AVRI2CBootloader/avr/application.h>

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <util/delay.h>

#include <RGBColorSensor.h>

#include "../libMaster/include/RGBColorSensorArrayRegisters.h"

#define SENSOR0_CLK 4
#define SENSOR0_DATA 0
#define SENSOR0_LED 0

#define SENSOR1_CLK 5
#define SENSOR1_DATA 1
#define SENSOR1_LED 1

#define SENSOR2_CLK 6
#define SENSOR2_DATA 2
#define SENSOR2_LED 2

void process(RGBColorSensor* s);

/*
 * BeagleBone Black callbacks
 */
size_t onI2CRead(uint8_t reg, uint8_t* buffer);
void onI2CWrite(uint8_t reg, uint8_t* buffer, size_t bufferSize);

bool sensorReadDataCallback(uint8_t m);
void sensorWriteCallback(uint8_t pin, uint8_t state, uint8_t m);
bool sensor0ReadDataCallback();
void sensor0WriteCallback(uint8_t pin, uint8_t state);
bool sensor1ReadDataCallback();
void sensor1WriteCallback(uint8_t pin, uint8_t state);
bool sensor2ReadDataCallback();
void sensor2WriteCallback(uint8_t pin, uint8_t state);

void delay1Second();

volatile bool enabled;

#define s0 (*(RGBColorSensor*)0x144)
#define s1 (*(RGBColorSensor*)0x164)
#define s2 (*(RGBColorSensor*)0x184)

int main()
{
  I2CCallbacks.onReadFunction = onI2CRead;
  I2CCallbacks.onWriteFunction = onI2CWrite;

  rgbColorSensorInit(&s0, sensor0ReadDataCallback, sensor0WriteCallback, process);
  rgbColorSensorInit(&s1, sensor1ReadDataCallback, sensor1WriteCallback, process);
  rgbColorSensorInit(&s2, sensor2ReadDataCallback, sensor2WriteCallback, process);

  enabled = false;

  sei();

  while(1)
  {
    if(!enabled)
    {
      delay1Second();
      rgbColorSensorToggleLEDState(&s0);
      rgbColorSensorToggleLEDState(&s1);
      rgbColorSensorToggleLEDState(&s2);
      delay1Second();
      rgbColorSensorToggleLEDState(&s0);
      rgbColorSensorToggleLEDState(&s1);
      rgbColorSensorToggleLEDState(&s2); 
    }
    else
    {
      rgbColorSensorUpdate(&s0);
      rgbColorSensorUpdate(&s1);
      rgbColorSensorUpdate(&s2);
    }
  }

  return 0;
}

void process(RGBColorSensor* s)
{
  uint16_t a, r, g, b;
  rgbColorSensorI2CReadColor(&(s->pins), &a, &r, &g, &b);

  r >>= 2;
  g >>= 2;;
  b >>= 2;

//  r = (r >= 256) ? 255 : r;
//  g = (g >= 256) ? 255 : g;
//  b = (b >= 256) ? 255 : b;

  s->red = (uint8_t)r;
  s->green = (uint8_t)g;
  s->blue = (uint8_t)b;
}

size_t onI2CRead(uint8_t reg, uint8_t* buffer)
{
  switch(reg)
  {
    case RGB_COLOR_SENSOR_ARRAY_REGISTER_STATUS:
    {
      buffer[0] = enabled ? 0x1 : 0x0;
      return 1;
    }
    case RGB_COLOR_SENSOR_ARRAY_REGISTER_DATA:
    {
      buffer[0] = rgbColorSensorGetRed(&s0);
      buffer[1] = rgbColorSensorGetGreen(&s0);
      buffer[2] = rgbColorSensorGetBlue(&s0);
      buffer[3] = rgbColorSensorGetRed(&s1);
      buffer[4] = rgbColorSensorGetGreen(&s1);
      buffer[5] = rgbColorSensorGetBlue(&s1);
      buffer[6] = rgbColorSensorGetRed(&s2);
      buffer[7] = rgbColorSensorGetGreen(&s2);
      buffer[8] = rgbColorSensorGetBlue(&s2);

      uint8_t d0 = rgbColorSensorGetDefect(&s0);
      uint8_t d1 = rgbColorSensorGetDefect(&s1);
      uint8_t d2 = rgbColorSensorGetDefect(&s2);

      buffer[9] = (d2 << 2) | (d1 << 1) | (d0);

      return 10;
    }
    case RGB_COLOR_SENSOR_ARRAY_REGISTER_LEDS:
    {
      uint8_t l0 = rgbColorSensorGetLEDState(&s0);
      uint8_t l1 = rgbColorSensorGetLEDState(&s1);
      uint8_t l2 = rgbColorSensorGetLEDState(&s2);

      buffer[0] = (l2 << 4) | (l1 << 2) | (l0);

      return 1;
    }
  }

  return 0;
}

void onI2CWrite(uint8_t reg, uint8_t* buffer, size_t bufferSize)
{
  switch(reg)
  {
    case RGB_COLOR_SENSOR_ARRAY_REGISTER_STATUS:
    {
      enabled = (buffer[0] & 0x1) ? true : false;
      break;
    }
    case RGB_COLOR_SENSOR_ARRAY_REGISTER_LEDS:
    {
      if(!enabled)
      {
	int v = buffer[0];
	uint8_t l0 = (v & 0x3);
	uint8_t l1 = ((v >> 2) & 0x3);
	uint8_t l2 = ((v >> 4) & 0x3);

	rgbColorSensorSetLEDState(&s0, l0); 
	rgbColorSensorSetLEDState(&s1, l1);
	rgbColorSensorSetLEDState(&s2, l2);
      }

      break;
    }
  }
}

bool sensorReadDataCallback(uint8_t m)
{
  return !(!(PIND & m));
}

void sensorWriteCallback(uint8_t pin, uint8_t state, uint8_t m)
{
  switch(pin)
  {
    case PIN_CLK:
    {
      switch(state)
      {
	case STATE_HIGH_Z:
	{
	  DDRD &= ~m;
	  PORTD &= ~m;
	  break;
	}
	case STATE_LOW:
	{
	  DDRD |= m;
	  PORTD &= ~m;
	  break;
	}
	case STATE_HIGH:
	{
	  DDRD |= m;
	  PORTD |= m;
	  break;
	}
      }

      break;
    }
    case PIN_DATA:
    {
      switch(state)
      {
	case STATE_HIGH_Z:
	{
	  DDRD &= ~m;
	  PORTD &= ~m;
	  break;
	}
	case STATE_LOW:
	{
	  DDRD |= m;
	  PORTD &= ~m;
	  break;
	}
	case STATE_HIGH:
	{
	  DDRD |= m;
	  PORTD |= m;
	  break;
	}
      }

      break;
    }
    case PIN_LED:
    {
      switch(state)
      {
	case STATE_HIGH_Z:
	{
	  DDRC &= ~m;
	  PORTC &= ~m;
	  break;
	}
	case STATE_LOW:
	{
	  DDRC |= m;
	  PORTC &= ~m;
	  break;
	}
	case STATE_HIGH:
	{
	  DDRC |= m;
	  PORTC |= m;
	  break;
	}
      }

      break;
    }
  }
}

bool sensor0ReadDataCallback()
{
  return sensorReadDataCallback(_BV(SENSOR0_DATA));
}

void sensor0WriteCallback(uint8_t pin, uint8_t state)
{
  uint8_t m = 0;

  switch(pin)
  {
    case PIN_CLK:
    {
      m = _BV(SENSOR0_CLK);
      break;
    }
    case PIN_DATA:
    {
      m = _BV(SENSOR0_DATA);
      break;
    }
    case PIN_LED:
    {
      m = _BV(SENSOR0_LED);
      break;
    }
  }

  sensorWriteCallback(pin, state, m);
}

bool sensor1ReadDataCallback()
{
  return sensorReadDataCallback(_BV(SENSOR1_DATA));
}

void sensor1WriteCallback(uint8_t pin, uint8_t state)
{
  uint8_t m = 0;

  switch(pin)
  {
    case PIN_CLK:
    {
      m = _BV(SENSOR1_CLK);
      break;
    }
    case PIN_DATA:
    {
      m = _BV(SENSOR1_DATA);
      break;
    }
    case PIN_LED:
    {
      m = _BV(SENSOR1_LED);
      break;
    }
  }

  sensorWriteCallback(pin, state, m);
}

bool sensor2ReadDataCallback()
{
  return sensorReadDataCallback(_BV(SENSOR2_DATA));
}

void sensor2WriteCallback(uint8_t pin, uint8_t state)
{
  uint8_t m = 0;

  switch(pin)
  {
    case PIN_CLK:
    {
      m = _BV(SENSOR2_CLK);
      break;
    }
    case PIN_DATA:
    {
      m = _BV(SENSOR2_DATA);
      break;
    }
    case PIN_LED:
    {
      m = _BV(SENSOR2_LED);
      break;
    }
  }

  sensorWriteCallback(pin, state, m);
}

void delay1Second()
{
  uint8_t i;

  for(i = 0; i < 40; i++)
  {
    _delay_ms(100);
  }
}
