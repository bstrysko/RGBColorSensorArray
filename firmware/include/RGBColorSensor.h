#ifndef _RGB_COLOR_SENSOR_ARRAY_RGB_COLOR_SENSOR_H_
#define _RGB_COLOR_SENSOR_ARRAY_RGB_COLOR_SENSOR_H_

#include <inttypes.h>
#include <stdbool.h>

#define STATE_HIGH_Z 0
#define STATE_LOW 1
#define STATE_HIGH 2

#define PIN_CLK 0
#define PIN_DATA 1
#define PIN_LED 2

#define LED_STATE_OFF 0
#define LED_STATE_ON 1
#define LED_STATE_TOGGLE 2

typedef bool (*RGBColorSensorReadDataCallback)();
typedef void (*RGBColorSensorWriteCallback)(uint8_t, uint8_t);

typedef struct
{
  RGBColorSensorReadDataCallback readDataCallback;
  RGBColorSensorWriteCallback writeCallback;
  bool ledToggle;
  bool ledOn;
} RGBColorSensor;

void rgbColorSensorInit
(
  RGBColorSensor* s,
  RGBColorSensorReadDataCallback readDataCallback,
  RGBColorSensorWriteCallback writeCallback
);

uint8_t rgbColorSensorGetRed(RGBColorSensor* s);
uint8_t rgbColorSensorGetGreen(RGBColorSensor* s);
uint8_t rgbColorSensorGetBlue(RGBColorSensor* s);
bool rgbColorSensorGetDefect(RGBColorSensor* s);
uint8_t rgbColorSensorGetLEDState(RGBColorSensor* s);
void rgbColorSensorSetLEDState(RGBColorSensor* s, uint8_t state);
void rgbColorSensorToggleLEDState(RGBColorSensor* s);
void rgbColorSensorUpdate(RGBColorSensor* s);

/*
// Port for the I2C
#define I2C_DDR DDRD
#define I2C_PIN PIND
#define I2C_PORT PORTD

// Pins to be used in the bit banging
#define I2C_CLK 0
#define I2C_DAT 1

#define I2C_DATA_HI()\
I2C_DDR &= ~ (1 << I2C_DAT);\
I2C_PORT |= (1 << I2C_DAT);
#define I2C_DATA_LO()\
I2C_DDR |= (1 << I2C_DAT);\
I2C_PORT &= ~ (1 << I2C_DAT);

#define I2C_CLOCK_HI()\
I2C_DDR &= ~ (1 << I2C_CLK);\
I2C_PORT |= (1 << I2C_CLK);
#define I2C_CLOCK_LO()\
I2C_DDR |= (1 << I2C_CLK);\
I2C_PORT &= ~ (1 << I2C_CLK);

void I2C_WriteBit(unsigned char c)
{
    if (c > 0)
    {
        I2C_DATA_HI();
    }
    else
    {
        I2C_DATA_LO();
    }

    I2C_CLOCK_HI();
    delay(1);

    I2C_CLOCK_LO();
    delay(1);

    if (c > 0)
    {
        I2C_DATA_LO();
    }

    delay(1);
}

unsigned char I2C_ReadBit()
{
    I2C_DATA_HI();

    I2C_CLOCK_HI();
    delay(1);

    unsigned char c = I2C_PIN;

    I2C_CLOCK_LO();
    delay(1);

    return (c >> I2C_DAT) & 1;
}

// Inits bitbanging port, must be called before using the functions below
//
void I2C_Init()
{
    I2C_PORT &= ~ ((1 << I2C_DAT) | (1 << I2C_CLK));

    I2C_CLOCK_HI();
    I2C_DATA_HI();

    delay(1);
}

// Send a START Condition
//
void I2C_Start()
{
    // set both to high at the same time
    I2C_DDR &= ~ ((1 << I2C_DAT) | (1 << I2C_CLK));
    delay(1);

    I2C_DATA_LO();
    delay(1);

    I2C_CLOCK_LO();
    delay(1);
}

// Send a STOP Condition
//
void I2C_Stop()
{
    I2C_CLOCK_HI();
    delay(1);

    I2C_DATA_HI();
    delay(1);
}

// write a byte to the I2C slave device
//
unsigned char I2C_Write(unsigned char c)
{
    for (char i = 0; i < 8; i++)
    {
        I2C_WriteBit(c & 128);

        c <<= 1;
    }

    //return I2C_ReadBit();
    return 0;
}


// read a byte from the I2C slave device
//
unsigned char I2C_Read(unsigned char ack)
{
    unsigned char res = 0;

    for (char i = 0; i < 8; i++)
    {
        res <<= 1;
        res |= I2C_ReadBit();
    }

    if (ack > 0)
    {
        I2C_WriteBit(0);
    }
    else
    {
        I2C_WriteBit(1);
    }

    delay(1);

    return res;
}
*/

#endif
