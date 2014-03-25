#include <iostream>
#include <sstream>
#include <algorithm>
#include <stdint.h>
#include <assert.h>

using namespace std;

void usage(string name);
uint8_t stringToUInt8(char* s);

#include <RGBColorSensorArray/RGBColorSensorArray.h>

int main(int argc, char* argv[])
{
	if(argc < 3)
	{
		usage(argv[0]);
		return 1;
	}

	uint8_t i2cBusNumber = stringToUInt8(argv[1]);
	uint8_t i2cDeviceAddress = stringToUInt8(argv[2]);

	I2CBus bus(i2cBusNumber);
	RGBColorSensorArray device(&bus, i2cDeviceAddress);

	if(!device.inApplicationMode())
	{
		cout << "Device NOT in application mode" << endl;
		cout << "Switching to application mode..." << endl;
		device.enterApplicationMode();
	}
	else
	{
		cout << "Device in application mode..." << endl;
	}

/*
	device.disable();
	assert(device.isDisabled());
	assert(!device.isEnabled());

	device.setLED0State(ENABLED);
	assert(device.getLED0State() == ENABLED);

	device.setLED1State(DISABLED);
	assert(device.getLED1State() == DISABLED);

	device.setLED2State(ENABLED);
	assert(device.getLED2State() == ENABLED);

	device.setLED0State(ENABLED);
	assert(device.getLED0State() == ENABLED);

	device.setLED0State(DISABLED);
	assert(device.getLED0State() == DISABLED);
	device.setLED1State(DISABLED);
	assert(device.getLED1State() == DISABLED);
	device.setLED2State(DISABLED);
	assert(device.getLED2State() == DISABLED);
	
	device.setLED1State(BLINK);
	assert(device.getLED1State() == BLINK);

	device.setLED2State(ENABLED);
	assert(device.getLED2State() == ENABLED);
*/
	device.setLED0State(DISABLED);
	device.setLED1State(DISABLED);
	device.setLED2State(DISABLED);

	size_t r = device.getReg();
	uint8_t a = r & 0xFF;
	uint8_t b = (r >> 8) & 0xFF;

	cout << (size_t)a << " | " << (size_t)b << endl;

	return 0;
}

void usage(string name)
{
	cout << "usage: " << name << " [ I2C Bus Number ] [I2C Device Address]" << endl;
}

uint8_t stringToUInt8(char* s)
{
	uint8_t result;
	
	result = atoi(s);
	
	if(result == 0 && s[0] != '0')
	{
		stringstream o;
		o << s << " is not a number";		
		throw ios_base::failure(o.str());
	}

	return result;
}
