#ifndef _RGB_COLOR_SENSOR_ARRAY_COLOR_H_
#define _RGB_COLOR_SENSOR_ARRAY_COLOR_H_

#include <stdint.h>

#include <iostream>

using namespace std;

class Color
{
  private:
    uint8_t red, green, blue;
  public:
    Color();
    Color(uint8_t red, uint8_t green, uint8_t blue);

    uint8_t getRed();
    uint8_t getGreen();
    uint8_t getBlue();

    static Color RED;
    static Color GREEN;
    static Color BLUE;

    friend ostream& operator<<(ostream& os, const Color& color);
};

#endif
