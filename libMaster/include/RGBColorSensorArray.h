#ifndef _RGB_COLOR_SENSOR_ARRAY_RGB_COLOR_SENSOR_ARRAY_H_
#define _RGB_COLOR_SENSOR_ARRAY_RGB_COLOR_SENSOR_ARRAY_H_

#include <AVRI2CBootloader/I2CDeviceBootable.h>

#include "Color.h"
#include "RGBColorSensorArrayRegisters.h"

#include <vector>

using namespace std;

enum LEDState
{
  ENABLED = 1,
  DISABLED = 0,
  BLINK = 2,
  UNDEFINED = 3
};

class RGBColorSensorArray : public I2CDeviceBootable
{
  private:
    LEDState getLEDState(uint8_t i);
    void setLEDState(uint8_t i, LEDState state);
    void processData(uint16_t* a, uint16_t* r, uint16_t* g, uint16_t* b);
  public:
    RGBColorSensorArray(I2CBus* bus, uint8_t address);

    bool isEnabled();
    bool isDisabled();
    vector<Color> getData();
    LEDState getLED0State();
    LEDState getLED1State();
    LEDState getLED2State();

    void enable();
    void disable();
    void setLED0State(LEDState state);
    void setLED1State(LEDState state);
    void setLED2State(LEDState state);
};

#endif
