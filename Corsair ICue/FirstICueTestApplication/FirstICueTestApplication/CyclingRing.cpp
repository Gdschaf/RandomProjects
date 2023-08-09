#include "CyclingRing.h"
#include "Color.h"

#include <iostream>

std::ostream& operator<<(std::ostream& os, const Color& rhs)
{
	os << "Red: " << rhs.r << "  Green: " << rhs.g << "  Blue: " << rhs.b << "  Alpha: " << rhs.a;
	return os;
}

void CyclingRing::Update(float deltaTime)
{
	UpdateFadingColors(deltaTime);

	float secondsPerLED = (1.0f / ((float)revolutionsPerMinute / 60.0f)) / (float)ringColors.size();

	if (timer >= secondsPerLED)
	{
		//light up the next LED
		++currentIndex;
		if (currentIndex >= ringColors.size())
			currentIndex = 0;

		ringColors[currentIndex].SetToStartingColor();
		ringColors[currentIndex].ResetTimer();
		ringColors[currentIndex].StartFading();

		timer -= secondsPerLED;

		if (rainbowPuke)
		{
			ringColors[currentIndex + 1].ManuallySetStartingColor(Color::RandomColor());
		}
	}

	//fade in the leading LED here?
	float fadePercentage = timer / secondsPerLED;
	if (fadePercentage > 1.0f)
		fadePercentage = 1.0f;

	//this should always be safe because of the looping linked list
	ringColors[currentIndex + 1].ManuallySetCurrentColor(ringColors[currentIndex + 1].CalculateFadeInColor(fadePercentage));

	timer += deltaTime;
}

void CyclingRing::UpdateFadingColors(float deltaTime)
{
	for (int i = 0; i < ringColors.size(); ++i)
	{
		ringColors[i].Update(deltaTime);
	}
}

CyclingRing::CyclingRing(int ledCount, FadingColor color, int RPM) : timer(0.0f), revolutionsPerMinute(DEFAULT_RING_RPM), fadingColor(color), currentIndex(0), rainbowPuke(false)
{
	for (int i = 0; i < ledCount; ++i)
	{
		ringColors.push_back(fadingColor);
	}
}

CyclingRing::CyclingRing() : timer(0.0f), revolutionsPerMinute(DEFAULT_RING_RPM), fadingColor(FadingColor()), currentIndex(0), rainbowPuke(false)
{

}

CyclingRing::CyclingRing(const CyclingRing& rhs) : timer(0.0f), currentIndex(0)
{
	fadingColor = rhs.fadingColor;
	revolutionsPerMinute = rhs.revolutionsPerMinute;
	ringColors = rhs.ringColors;
	rainbowPuke = rhs.rainbowPuke;
}

CyclingRing::CyclingRing(int ledCount, tinyxml2::XMLNode* node) : timer(0.0f), currentIndex(0)
{
	fadingColor = FadingColor();
	rainbowPuke = false;
	revolutionsPerMinute = DEFAULT_RING_RPM;

	tinyxml2::XMLNode* child = node->FirstChild();
	while (child != NULL)
	{
		std::string childName = child->Value();
		if (childName.compare("FadingColor") == 0)
		{
			fadingColor = FadingColor(child);
		}
		else if (childName.compare("RevolutionsPerMinute") == 0)
		{
			tinyxml2::XMLElement* childElement = child->ToElement();
			childElement->QueryIntText(&revolutionsPerMinute);
		}
		else if (childName.compare("RainbowPuke") == 0)
		{
			tinyxml2::XMLElement* childElement = child->ToElement();
			std::string elementText = childElement->GetText();
			if (elementText.compare("true") == 0)
				rainbowPuke = true;
		}

		child = child->NextSibling();
	}

	for (int i = 0; i < ledCount; ++i)
	{
		ringColors.push_back(fadingColor);
	}
}

void CyclingRing::Initialize()
{
	ringColors[0].SetToStartingColor();
	ringColors[0].StartFading();
}

Color CyclingRing::GetRingColor(int index)
{
	return ringColors[index].GetCurrentColor();
}

int CyclingRing::Size()
{
	return ringColors.size();
}

void CyclingRing::EnableRainbowPuke()
{
	rainbowPuke = true;
}

int CyclingRing::GetCurrentIndex()
{
	return currentIndex;
}

void CyclingRing::SetCurrentIndex(int index)
{
	currentIndex = index;
}

FadingColor& CyclingRing::GetCurrentFadingColor()
{
	return ringColors[currentIndex];
}

FadingColor& CyclingRing::GetNextFadingColor()
{
	return ringColors[currentIndex + 1];
}

CyclingRing& CyclingRing::operator=(const CyclingRing& rhs)
{
    fadingColor = rhs.fadingColor;
	revolutionsPerMinute = rhs.revolutionsPerMinute;
	ringColors = rhs.ringColors;

	return *this;
}
