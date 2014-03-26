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

ostream& operator<<(ostream& os, const RGBColorSensor& rhs)
{
	return os << "[Color: " << rhs.color << ", Defect: " << (rhs.defect ? "true" : "false") << "]";
}
