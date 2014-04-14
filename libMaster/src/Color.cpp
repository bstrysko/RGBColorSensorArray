#include <Color.h>

Color Color::RED = Color(255, 0, 0);
Color Color::GREEN = Color(0, 255, 0);
Color Color::BLUE = Color(0, 0, 255);

Color::Color() : Color(0, 0, 0, 0)
{
}

Color::Color(uint32_t red, uint32_t green, uint32_t blue) : Color(0, red, green, blue)
{
}

Color::Color(uint32_t alpha, uint32_t red, uint32_t green, uint32_t blue)
{
	this->alpha = alpha;
	this->red = red;
	this->green = green;
	this->blue = blue;
}

uint32_t Color::getAlpha()
{
	return alpha;
}

uint32_t Color::getRed()
{
	return red;
}

uint32_t Color::getGreen()
{
	return green;
}

uint32_t Color::getBlue()
{
	return blue;
}

ostream& operator<<(ostream& os, const Color& color)
{
	return os << "(" << (int)color.alpha << ", " << (int)color.red << ", " <<
		(int)color.green << ", " << (int)color.blue << ")";
}
