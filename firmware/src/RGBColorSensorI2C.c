#include <RGBColorSensorI2C.h>

#define RGB_COLOR_SENSOR_I2C_ADDRESS 0x29
#define RGB_COLOR_SENSOR_I2C_COMMAND_BIT 0x80

#define REGISTER_ENABLE 0x00
#define REGISTER_ID 0x12
#define REGISTER_CDATAL 0x14
#define REGISTER_RDATAL 0x16
#define REGISTER_GDATAL 0x18
#define REGISTER_BDATAL 0x1A

#define ENABLE_PON 0x01
#define ENABLE_AEN 0x02
#define ENABLE_WEN 0x08
#define ENABLE_AIEN 0x10

uint8_t read8(GPins* pins, uint8_t reg);
uint16_t read16(GPins* pins, uint8_t reg);
void write8(GPins* pins, uint8_t reg, uint8_t v);
void enable(GPins* pins);

void rgbColorSensorI2CInit(GPins* pins)
{
  sI2CMasterInit(pins);
  enable(pins);
}

void enable(GPins* pins)
{
  write8(pins, REGISTER_ENABLE, ENABLE_PON);
  _delay_ms(1);
  write8(pins, REGISTER_ENABLE, (ENABLE_PON | ENABLE_AEN));
}

uint8_t rgbColorSensorI2CReadID(GPins* pins)
{
  return read8(pins, REGISTER_ID);
}

void rgbColorSensorI2CReadColor(GPins* pins, uint16_t* c, uint16_t* r, uint16_t* g, uint16_t* b)
{
  (*c) = read16(pins, REGISTER_CDATAL);
  (*r) = read16(pins, REGISTER_RDATAL);
  (*g) = read16(pins, REGISTER_GDATAL);
  (*b) = read16(pins, REGISTER_BDATAL);
}

uint8_t read8(GPins* pins, uint8_t reg)
{
  return sI2CMasterRead8(pins, RGB_COLOR_SENSOR_I2C_ADDRESS, RGB_COLOR_SENSOR_I2C_COMMAND_BIT | reg);
}

uint16_t read16(GPins* pins, uint8_t reg)
{
  return sI2CMasterRead16(pins, RGB_COLOR_SENSOR_I2C_ADDRESS, RGB_COLOR_SENSOR_I2C_COMMAND_BIT | reg);
}

void write8(GPins* pins, uint8_t reg, uint8_t v)
{
  sI2CMasterWrite8(pins, RGB_COLOR_SENSOR_I2C_ADDRESS, RGB_COLOR_SENSOR_I2C_COMMAND_BIT | reg, v);
}
