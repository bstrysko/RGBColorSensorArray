#include <RGBColorSensor.h>

RGBColorSensor::RGBColorSensor(Color color, bool defect)
{
	this->color = color;
	this->defect = defect;
}
    
Color RGBColorSensor::getColor()
{
	return color;
}

bool RGBColorSensor::isDefect()
{
	return defect;
}
