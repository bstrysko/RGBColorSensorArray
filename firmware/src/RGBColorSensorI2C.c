#include <RGBColorSensorI2C.h>

void i2cStartCondition(RGBColorSensorPins* pins);
void i2cStopCondition(RGBColorSensorPins* pins);
void i2cWriteBit(RGBColorSensorPins* pins, uint8_t v);
bool i2cReadBit(RGBColorSensorPins* pins);
uint8_t i2cReadByte(RGBColorSensorPins* pins, uint8_t ack);
uint8_t i2cWriteByte(RGBColorSensorPins* pins, uint8_t v);

void rgbColorSensorI2CInit(RGBColorSensorPins* pins)
{
  pins->writeCallback(PIN_CLK, STATE_HIGH_Z);
  pins->writeCallback(PIN_DATA, STATE_HIGH_Z);
  _delay_ms(1);
}

size_t rgbColorSensorI2CRead(RGBColorSensorPins* pins, uint8_t* buffer, size_t n)
{
  //TODO: implement
  return 0;
}

size_t rgbColorSensorI2CWrite(RGBColorSensorPins* pins, uint8_t* buffer, size_t n)
{
  //TODO: implement
  return 0;
}

void i2cStartCondition(RGBColorSensorPins* pins)
{
  pins->writeCallback(PIN_CLK, STATE_HIGH_Z);
  pins->writeCallback(PIN_DATA, STATE_HIGH_Z);
  _delay_ms(1);
  pins->writeCallback(PIN_DATA, STATE_LOW);
  _delay_ms(1);
  pins->writeCallback(PIN_CLK, STATE_LOW);
  _delay_ms(1);
}

void i2cStopCondition(RGBColorSensorPins* pins)
{
  pins->writeCallback(PIN_CLK, STATE_HIGH_Z);
  _delay_ms(1);
  pins->writeCallback(PIN_DATA, STATE_HIGH_Z);
  _delay_ms(1);
}

void i2cWriteBit(RGBColorSensorPins* pins, uint8_t v)
{
  if(v)
  {
    pins->writeCallback(PIN_DATA, STATE_HIGH_Z);
  }
  else
  {
    pins->writeCallback(PIN_DATA, STATE_LOW);
  }

  pins->writeCallback(PIN_CLK, STATE_HIGH_Z);
  _delay_ms(1);
  pins->writeCallback(PIN_CLK, STATE_LOW);
  _delay_ms(1);

  if(v) 
  {
    pins->writeCallback(PIN_DATA, STATE_LOW);
  }
  
  _delay_ms(1);
}

bool i2cReadBit(RGBColorSensorPins* pins)
{
  pins->writeCallback(PIN_DATA, STATE_HIGH_Z);
  pins->writeCallback(PIN_CLK, STATE_HIGH_Z);

  _delay_ms(1);

  bool v = pins->readDataCallback();
  pins->writeCallback(PIN_CLK, STATE_LOW);

  _delay_ms(1);

  return v;
}

uint8_t i2cReadByte(RGBColorSensorPins* pins, uint8_t ack)
{ 
  uint8_t v = 0;
  uint8_t i;

  for(i = 0; i < 8; i++)
  {
    v <<= 1;
    v |= i2cReadBit(pins);
  }

  i2cWriteBit(pins, !ack);
 
  _delay_ms(1);
  return v;
}

uint8_t i2cWriteByte(RGBColorSensorPins* pins, uint8_t v)
{
  uint8_t i;

  for(i = 0; i < 8; i++)
  {
    i2cWriteBit(pins, (v & 0x80));
    v <<= 1;
  }

  //TODO: read ack bit?  
  return 0;
}

