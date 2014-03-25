#include <RGBColorSensorI2C.h>

void i2cStartCondition(RGBColorSensorPins* pins);
void i2cRepeatedStartCondition(RGBColorSensorPins* pins);
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

size_t rgbColorSensorI2CRead(RGBColorSensorPins* pins, uint8_t reg, uint8_t* buffer, size_t n)
{
  uint8_t address = (0x29 << 1) | 0x0;

  i2cStartCondition(pins);

  if(i2cWriteByte(pins, address) != 0x1)
  {
    i2cStopCondition(pins);
    return 0xFD;
  }

  if(i2cWriteByte(pins, 0x80 | reg) != 0x1)
  {
    i2cStopCondition(pins);
    return 0xFE;
  }
  
  i2cRepeatedStartCondition(pins);

  uint8_t address_v = (0x29 << 1) | 0x1;

  if(i2cWriteByte(pins, address_v) != 0x1)
  {
    i2cStopCondition(pins);
    return 0xFC;
  }

  uint8_t i;
  for(i = 0; i < n; i++)
  {
    uint8_t v = i2cReadByte(pins, (i < (n-1)));
    buffer[i] = v;
  }

  i2cStopCondition(pins);

  return n;
}

size_t rgbColorSensorI2CWrite(RGBColorSensorPins* pins, uint8_t reg, uint8_t* buffer, size_t n)
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

void i2cRepeatedStartCondition(RGBColorSensorPins* pins)
{
  pins->writeCallback(PIN_DATA, STATE_HIGH_Z);
  _delay_ms(1);
  pins->writeCallback(PIN_CLK, STATE_HIGH_Z);
  _delay_ms(1);
  i2cStartCondition(pins);
}

void i2cStopCondition(RGBColorSensorPins* pins)
{
  pins->writeCallback(PIN_DATA, STATE_LOW);
  _delay_ms(1);
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

  _delay_ms(1);
  pins->writeCallback(PIN_CLK, STATE_HIGH_Z);
  _delay_ms(1);
  pins->writeCallback(PIN_CLK, STATE_LOW);
  _delay_ms(1);

  if(v) 
  {
    pins->writeCallback(PIN_DATA, STATE_HIGH_Z);
  }
  
  _delay_ms(1);
}

bool i2cReadBit(RGBColorSensorPins* pins)
{
  pins->writeCallback(PIN_DATA, STATE_HIGH_Z);
  _delay_ms(1);
  pins->writeCallback(PIN_CLK, STATE_HIGH_Z);

  _delay_ms(1);

  bool v = pins->readDataCallback();
  _delay_ms(1);
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
    i2cWriteBit(pins, (v & 0x80) != 0);
    v <<= 1;
  }

  return !i2cReadBit(pins);
}

