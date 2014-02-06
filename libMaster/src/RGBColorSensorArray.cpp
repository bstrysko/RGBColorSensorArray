#include <RGBColorSensorArray.h>

RGBColorSensorArray::RGBColorSensorArray(I2CBus* bus, uint8_t address) : I2CDeviceBootable(bus, address)
{
}

LEDState RGBColorSensorArray::getLEDState(uint8_t i)
{
	uint8_t v = i2cRead8(RGB_COLOR_SENSOR_ARRAY_REGISTER_LEDS);
	v = (v >> (2*i)) & 0x3;

	LEDState state = static_cast<LEDState>(v);
	return state;
}

void RGBColorSensorArray::setLEDState(uint8_t i, LEDState state)
{
	uint8_t v;

	switch(state)
	{
		case DISABLED:
		{
			v = 0;
			break;
		}
		case ENABLED:
		{
			v = 1;
			break;
		}
		case BLINK:
		{
			v = 2;
			break;
		}
		default:
		{
			v = 3;
			break;
		}
	}
	
	uint8_t r = (0x3F ^ (0x3 << (2*i)));
	v = (v << (2*i));
	r |= v;
	i2cWrite8(RGB_COLOR_SENSOR_ARRAY_REGISTER_LEDS,
		r
	);
}
 
bool RGBColorSensorArray::isEnabled()
{
	return (
		i2cRead8(RGB_COLOR_SENSOR_ARRAY_REGISTER_STATUS) & 0x1
	);
}

bool RGBColorSensorArray::isDisabled()
{
	return !(
		i2cRead8(RGB_COLOR_SENSOR_ARRAY_REGISTER_STATUS) & 0x1
	);
}


vector<RGBColorSensor> RGBColorSensorArray::getData()
{
	uint8_t buffer[10];
	i2cRead(RGB_COLOR_SENSOR_ARRAY_REGISTER_DATA, buffer, 10);

	vector<RGBColorSensor> data;

	Color c0 = Color(buffer[0], buffer[1], buffer[2]);
	bool d0 = (buffer[9] & 0x1) ? true : false;
	data.push_back(RGBColorSensor(c0, d0));

	Color c1 = Color(buffer[3], buffer[4], buffer[5]);
	bool d1 = (buffer[9] & 0x2) ? true : false;
	data.push_back(RGBColorSensor(c1, d1));

	Color c2 = Color(buffer[6], buffer[7], buffer[8]);
	bool d2 = (buffer[9] & 0x4) ? true : false;
	data.push_back(RGBColorSensor(c2, d2));

	return data;
}

LEDState RGBColorSensorArray::getLED0State()
{
	return getLEDState(0);
}

LEDState RGBColorSensorArray::getLED1State()
{
	return getLEDState(1);
}

LEDState RGBColorSensorArray::getLED2State()
{
	return getLEDState(2);
}

void RGBColorSensorArray::enable()
{
	i2cWrite8(RGB_COLOR_SENSOR_ARRAY_REGISTER_STATUS, 0x1);
}

void RGBColorSensorArray::disable()
{
	i2cWrite8(RGB_COLOR_SENSOR_ARRAY_REGISTER_STATUS, 0x0);
}

void RGBColorSensorArray::setLED0State(LEDState state)
{
	setLEDState(0, state);
}

void RGBColorSensorArray::setLED1State(LEDState state)
{
	setLEDState(1, state);
}

void RGBColorSensorArray::setLED2State(LEDState state)
{
	setLEDState(2, state);	
}
