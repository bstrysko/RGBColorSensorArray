#ifndef _RGB_COLOR_SENSOR_ARRAY_COLOR_H_
#define _RGB_COLOR_SENSOR_ARRAY_COLOR_H_

#include <stdint.h>

#include <iostream>

using namespace std;

class Color
{
  private:
    uint32_t alpha, red, green, blue;
  public:
    Color();
    Color(uint32_t red, uint32_t green, uint32_t blue);
    Color(uint32_t alpha, uint32_t red, uint32_t green, uint32_t blue);

    uint32_t getAlpha();
    uint32_t getRed();
    uint32_t getGreen();
    uint32_t getBlue();

    static Color RED;
    static Color GREEN;
    static Color BLUE;

    friend ostream& operator<<(ostream& os, const Color& color);
};

#endif
