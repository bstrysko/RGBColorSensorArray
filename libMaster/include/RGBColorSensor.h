#ifndef _RGB_COLOR_SENSOR_ARRAY_RGB_COLOR_SENSOR_H_
#define _RGB_COLOR_SENSOR_ARRAY_RGB_COLOR_SENSOR_H_

#include "Color.h"

class RGBColorSensor
{
  private:
    Color color;
    bool defect;
  public:
    RGBColorSensor(Color color, bool defect);

    Color getColor();
    bool isDefect();
};

#endif
