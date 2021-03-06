#include <iostream>
#include <sstream>
#include <algorithm>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void usage(string name);
uint8_t stringToUInt8(char* s);

#include <RGBColorSensorArray/RGBColorSensorArray.h>

#define WINDOW_NAME "Colors"

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

	device.disable();
	assert(device.isDisabled());
	assert(!device.isEnabled());

	LEDState s = ENABLED;
	device.setLED0State(s);
	device.setLED1State(s);
	device.setLED2State(s);

	device.enable();
	assert(device.isEnabled());

	namedWindow(WINDOW_NAME, 1);

	Mat m[3];
	m[0] = Mat(200, 200, CV_8UC3, Scalar::all(0));
	m[1] = Mat(200, 200, CV_8UC3, Scalar::all(0));
	m[2] = Mat(200, 200, CV_8UC3, Scalar::all(0));
	Mat result(2*m[0].rows, 2*m[0].cols, m[0].type());

	while(true)
	{
		vector<Color> data = device.getData();

		for(size_t i =0; i < data.size(); i++)
		{
			Color c = data[i];
/*
			double alpha = (double)c.getAlpha();
			double red = (double)c.getRed();
			double green = (double)c.getGreen();
			double blue = (double)c.getBlue();

			red /= alpha;
			green /= alpha;
			blue /= alpha;

			cout << red << ", " << green << ", " << blue << endl;

			green *= 1.05;
			blue *= 1.55;

			cout << red << ", " << green << ", " << blue << endl;

			red *= 255.0;
			green *= 255.0;
			blue *= 255.0;

			cout << red << ", " << green << ", " << blue << endl;
*/
			m[i] = Scalar(c.getBlue(), c.getGreen(), c.getRed());

			if(c.getAlpha() > 3000)
			{
				ostringstream t;
				t << "DEFECT";
				putText(m[i], t.str(), Point(20,40), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255, 0), 1, CV_AA);
			}
			
			cout << c << "\t";
		}

		cout << endl;

		m[0].copyTo(result(Rect(0, 0, m[0].cols, m[0].rows)));
		m[1].copyTo(result(Rect(m[0].cols, 0, m[0].cols, m[0].rows)));
		m[2].copyTo(result(Rect(0, m[0].rows, m[0].cols, m[0].rows)));
		imshow(WINDOW_NAME, result);
		
		waitKey(2);
		//usleep(5000);
	}

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
