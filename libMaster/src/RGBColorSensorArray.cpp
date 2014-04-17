#include <RGBColorSensorArray.h>

RGBColorSensorArray::RGBColorSensorArray(I2CBus* bus, uint8_t address) : I2CDeviceBootable(bus, address)
{
	enterApplicationMode();
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
	
	uint8_t r = (0x3F ^ (0x03 << (2*i)));
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

void RGBColorSensorArray::processData(uint16_t* a, uint16_t* r, uint16_t* g, uint16_t* b)
{
	double alpha = (double)(*a);
	double red = (double)(*r);
	double green = (double)(*g);
	double blue = (double)(*b);

	red /= alpha;
	green /= alpha;
	blue /= alpha;

	green *= 1.05;
	blue *= 1.55;

	red *= 255.0;
	green *= 255.0;
	blue *= 255.0;

	(*a) = alpha;
	(*r) = red;
	(*g) = green;
	(*b) = blue;
}

vector<Color> RGBColorSensorArray::getData()
{
	uint16_t buffer[12];
	i2cRead(RGB_COLOR_SENSOR_ARRAY_REGISTER_DATA, (uint8_t*)buffer, 24);

	processData(&buffer[0], &buffer[1], &buffer[2], &buffer[3]);
	processData(&buffer[4], &buffer[5], &buffer[6], &buffer[7]);
	processData(&buffer[8], &buffer[9], &buffer[10], &buffer[11]);

	vector<Color> data;

	data.push_back(Color(buffer[0], buffer[1], buffer[2], buffer[3]));
	data.push_back(Color(buffer[4], buffer[5], buffer[6], buffer[7]));
	data.push_back(Color(buffer[8], buffer[9], buffer[10], buffer[11]));

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
