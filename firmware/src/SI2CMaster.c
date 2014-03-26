#include <SI2CMaster.h>

#define WRITE_BIT 0x00
#define READ_BIT 0x01

void i2cStartCondition(GPins* pins);
void i2cRepeatedStartCondition(GPins* pins);
void i2cStopCondition(GPins* pins);
void i2cWriteBit(GPins* pins, uint8_t v);
bool i2cReadBit(GPins* pins);
uint8_t i2cReadByte(GPins* pins, uint8_t ack);
void i2cWriteByte(GPins* pins, uint8_t v);

void sI2CMasterInit(GPins* pins)
{
  pins->writeCallback(PIN_CLK, STATE_HIGH_Z);
  pins->writeCallback(PIN_DATA, STATE_HIGH_Z);
  _delay_ms(1);
}

void sI2CMasterRead(GPins* pins, uint8_t address, uint8_t reg, uint8_t* buffer, size_t n)
{
  i2cStartCondition(pins);
  _delay_ms(1);
  i2cWriteByte(pins, ((address << 1) | WRITE_BIT));
  _delay_ms(1);
  i2cWriteByte(pins, reg);
  _delay_ms(1);
  i2cRepeatedStartCondition(pins);
  _delay_ms(1);
  i2cWriteByte(pins, ((address << 1) | READ_BIT));
  _delay_ms(1);

  uint8_t i;
  for(i = 0; i < n; i++)
  {
    buffer[i] = i2cReadByte(pins, (i < (n-1)));
  }

  i2cStopCondition(pins);
}

void sI2CMasterWrite(GPins* pins, uint8_t address, uint8_t reg, uint8_t* buffer, size_t n)
{
  i2cStartCondition(pins);
  i2cWriteByte(pins, ((address << 1) | WRITE_BIT));
  i2cWriteByte(pins, reg);
  
  uint8_t i;
  for(i = 0; i < n; i++)
  {
    i2cWriteByte(pins, buffer[i]);
  }

  i2cStopCondition(pins);
}

uint8_t sI2CMasterRead8(GPins* pins, uint8_t address, uint8_t reg)
{
  uint8_t v;
  sI2CMasterRead(pins, address, reg, &v, 1);
  return v;
}

uint16_t sI2CMasterRead16(GPins* pins, uint8_t address, uint8_t reg)
{
  uint16_t v;
  sI2CMasterRead(pins, address, reg, (uint8_t*)&v, 2);
  return v;
}

void sI2CMasterWrite8(GPins* pins, uint8_t address, uint8_t reg, uint8_t v)
{
  sI2CMasterWrite(pins, address, reg, &v ,1);
}

void i2cStartCondition(GPins* pins)
{
  pins->writeCallback(PIN_CLK, STATE_HIGH_Z);
  pins->writeCallback(PIN_DATA, STATE_HIGH_Z);
  _delay_ms(1);
  pins->writeCallback(PIN_DATA, STATE_LOW);
  _delay_ms(1);
  pins->writeCallback(PIN_CLK, STATE_LOW);
  _delay_ms(1);
}

void i2cRepeatedStartCondition(GPins* pins)
{
  pins->writeCallback(PIN_DATA, STATE_HIGH_Z);
  _delay_ms(1);
  pins->writeCallback(PIN_CLK, STATE_HIGH_Z);
  _delay_ms(1);
  i2cStartCondition(pins);
}

void i2cStopCondition(GPins* pins)
{
  pins->writeCallback(PIN_DATA, STATE_LOW);
  _delay_ms(1);
  pins->writeCallback(PIN_CLK, STATE_HIGH_Z);
  _delay_ms(1);
  pins->writeCallback(PIN_DATA, STATE_HIGH_Z);
  _delay_ms(1);
}

void i2cWriteBit(GPins* pins, uint8_t v)
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

bool i2cReadBit(GPins* pins)
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

uint8_t i2cReadByte(GPins* pins, uint8_t ack)
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

void i2cWriteByte(GPins* pins, uint8_t v)
{
  uint8_t i;

  for(i = 0; i < 8; i++)
  {
    i2cWriteBit(pins, (v & 0x80) != 0);
    v <<= 1;
  }

  //TODO: in future check ACK bit
  /*!*/
  i2cReadBit(pins);
}
