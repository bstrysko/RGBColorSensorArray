#ifndef _RGB_COLOR_SENSOR_ARRAY_S_I2C_MASTER_H_
#define _RGB_COLOR_SENSOR_ARRAY_S_I2C_MASTER_H_

#include "GPins.h"

#include <stddef.h>
#include <util/delay.h>

void sI2CMasterInit(GPins* pins);

void sI2CMasterRead(GPins* pins, uint8_t address, uint8_t reg, uint8_t* buffer, size_t n);
void sI2CMasterWrite(GPins* pins, uint8_t address, uint8_t reg, uint8_t* buffer, size_t n);

uint8_t sI2CMasterRead8(GPins* pins, uint8_t address, uint8_t reg);
uint16_t sI2CMasterRead16(GPins* pins, uint8_t address, uint8_t reg);
void sI2CMasterWrite8(GPins* pins, uint8_t address, uint8_t reg, uint8_t v);

#endif
