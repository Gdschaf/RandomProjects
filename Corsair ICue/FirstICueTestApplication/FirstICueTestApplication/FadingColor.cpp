#include "FadingColor.h"

#include <algorithm>
#include <iostream>

FadingColor::FadingColor(float duration, Color start, Color end /*= Color_Black*/) : fadeDuration(duration), startingColor(start), endingColor(end)
{
	//used just to initialize variables?
	StopFading();
	currentColor = end;
}

FadingColor::FadingColor(): fadeDuration(1.0f), startingColor(Color_White), endingColor(Color_Black)
{
	StopFading();
	currentColor = endingColor;
}

FadingColor::FadingColor(tinyxml2::XMLNode* node)
{
	startingColor = Color_White;
	endingColor = Color_Black;
	fadeDuration = 1.0f;

	tinyxml2::XMLNode* child = node->FirstChild();

	while (child != NULL)
	{
		std::string childName = child->Value();
		tinyxml2::XMLElement* childElement = child->ToElement();
		if (childName.compare("Color") == 0)
		{
			const char* colorName;
			childElement->QueryStringAttribute("name", &colorName);
			if (std::string(colorName).compare("starting") == 0)
			{
				startingColor = Color(child);
			}
			else if (std::string(colorName).compare("ending") == 0)
			{
				endingColor = Color(child);
			}
		}
		else if (childName.compare("FadeDuration") == 0)
		{
			childElement->QueryFloatText(&fadeDuration);
		}

		child = child->NextSibling();
	}

	StopFading();
	currentColor = endingColor;
}

FadingColor& FadingColor::operator=(const FadingColor& rhs)
{
	startingColor = rhs.startingColor;
	endingColor = rhs.endingColor;
	fadeDuration = rhs.fadeDuration;
	StopFading();

	return *this;
}

void FadingColor::Update(float deltaTime)
{
	if (fading && timer < fadeDuration)
	{
		timer += deltaTime;

		float percentage = timer / fadeDuration;
		percentage = std::min(1.0f, percentage);

		//interpolate between the start and end color
		//set current color after clamping to make sure it's between 0 and 255
		currentColor = CalculateFadeOutColor(percentage);
	}
	else if (fading)
	{
		SetToEndingColor();
		StopFading();
	}
}

Color FadingColor::CalculateFadeInColor(float percentage)
{
	Color fadeInColor = endingColor - (endingColor - startingColor) * percentage;
	fadeInColor.r = SnipValue(fadeInColor.r);
	fadeInColor.g = SnipValue(fadeInColor.g);
	fadeInColor.b = SnipValue(fadeInColor.b);
	fadeInColor.a = SnipValue(fadeInColor.a);
	return fadeInColor;
}

Color FadingColor::CalculateFadeOutColor(float percentage)
{
	Color fadeOutColor = startingColor - (startingColor - endingColor) * percentage;
	fadeOutColor.r = SnipValue(fadeOutColor.r);
	fadeOutColor.g = SnipValue(fadeOutColor.g);
	fadeOutColor.b = SnipValue(fadeOutColor.b);
	fadeOutColor.a = SnipValue(fadeOutColor.a);
	return fadeOutColor;
}

void FadingColor::SetFadingDuration(float duration)
{
	fadeDuration = duration;
}

short FadingColor::SnipValue(float v)
{
	return (short)(std::max(0.0f, std::min(v, 255.0f)));
}

void FadingColor::ResetTimer()
{
	timer = 0.0f;
}

void FadingColor::StartFading()
{
	fading = true;
}

void FadingColor::PauseFading()
{
	fading = false;
}

void FadingColor::StopFading()
{
	PauseFading();
	ResetTimer();
}

void FadingColor::SetToStartingColor()
{
	currentColor = startingColor;
}

void FadingColor::SetToEndingColor()
{
	currentColor = endingColor;
}

Color FadingColor::GetCurrentColor()
{
	return currentColor;
}

void FadingColor::ManuallySetCurrentColor(Color c)
{
	currentColor = c;
}

void FadingColor::ManuallySetStartingColor(Color c)
{
	startingColor = c;
}
