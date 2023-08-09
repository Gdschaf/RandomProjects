#pragma once

#include <stdlib.h>

#include <CUESDK.h>
#include "tinyxml2.h"

class Color
{
public:
	//only really should be 0-255
	short r;
	short g;
	short b;
	short a; //a is used to determine the brightness in this case

	Color(short red, short green, short blue, short alpha = 255) : r(red), g(green), b(blue), a(alpha) { }
	Color(const Color& rhs) : r(rhs.r), g(rhs.g), b(rhs.b), a(rhs.a) { }
	Color() : r(0), g(0), b(0), a(255) { }

	Color(tinyxml2::XMLNode* node)
	{
		tinyxml2::XMLElement* element = node->ToElement();
		int red, green, blue, alpha = 0;
		element->QueryIntAttribute("red", &red);
		element->QueryIntAttribute("green", &green);
		element->QueryIntAttribute("blue", &blue);
		element->QueryIntAttribute("alpha", &alpha);
		r = (short)red;
		g = (short)green;
		b = (short)blue;
		a = (short)alpha;
	}

	static Color RandomColor()
	{
		return Color(rand() % 256, rand() % 256, rand() % 256, 255); //I think we just want alpha to be yes.
	}

	Color & operator=(const Color & rhs)
	{
		r = rhs.r;
		g = rhs.g;
		b = rhs.b;
		a = rhs.a;
		return *this;
	}

	Color operator-(const Color& rhs)
	{
		return Color(r - rhs.r, g - rhs.g, b - rhs.b, a - rhs.a);
	}

	Color operator+(const Color& rhs)
	{
		return Color(r + rhs.r, g + rhs.g, b + rhs.b, a + rhs.b);
	}

	Color& operator+=(const Color& rhs)
	{
		r += rhs.r;
		g += rhs.g;
		b += rhs.b;
		a += rhs.a;
		return *this;
	}

	Color& operator-=(const Color& rhs)
	{
		r -= rhs.r;
		g -= rhs.g;
		b -= rhs.b;
		a -= rhs.a;
		return *this;
	}

	Color operator*(const float& rhs)
	{
		return Color((short)(r * rhs), short(g * rhs), short(b * rhs), (short)(a * rhs));
	}

	operator CorsairLedColor() const 
	{
		CorsairLedColor corsairColor;
		float alpha = 255.0f / a;
		corsairColor.r = (int)(r * alpha);
		corsairColor.g = (int)(g * alpha);
		corsairColor.b = (int)(b * alpha);
		return corsairColor;
	}
};

#define Color_Black Color(0, 0, 0, 255)
#define Color_White Color(255, 255, 255, 255)
#define Color_Blue Color(0, 0, 255, 255)
#define Color_Red Color(255, 0, 0, 255)
#define Color_Green Color(0, 255, 0, 255)
#define Color_Purple Color(128, 0, 255, 255);
#define Color_Magenta Color(255, 0, 255, 255);
#define Color_Yellow Color(255, 255, 0, 255);
#define Color_Gold Color(255, 128, 0, 255);
#define Color_Orange Color(255, 64, 0, 255)
#define Color_Teal Color(0, 128, 255, 255);
#define Color_Turqoise Color(0, 255, 128, 255);
