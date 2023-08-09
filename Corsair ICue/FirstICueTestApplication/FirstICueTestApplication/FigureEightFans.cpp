#include "FigureEightFans.h"

FigureEightFans::FigureEightFans(std::vector<Fan*> fans, FadingColor color) : currentDirection(forward), currentFan(0)
{
	for (int i = 0; i < fans.size(); ++i)
	{
		cyclingRings.push_back(CyclingRing(fans[i]->OuterRingLEDCount(), color));
	}
	listOfFans = fans;
}

FigureEightFans::FigureEightFans(std::vector<Fan*> fans, tinyxml2::XMLNode* node) : currentDirection(forward), currentFan(0)
{
	FadingColor color;

	tinyxml2::XMLNode* child = node->FirstChild();
	while (child != NULL)
	{
		std::string childName = child->Value();
		if (childName.compare("FadingColor") == 0)
		{
			color = FadingColor(child);
		}
		child = child->NextSibling();
	}

	for (int i = 0; i < fans.size(); ++i)
	{
		cyclingRings.push_back(CyclingRing(fans[i]->OuterRingLEDCount(), color));
	}
	listOfFans = fans;
}

void FigureEightFans::Update(float deltaTime)
{
	for (int i = 0; i < cyclingRings.size(); ++i)
	{
		if (i == currentFan)
			cyclingRings[i].Update(deltaTime);
		else
			cyclingRings[i].UpdateFadingColors(deltaTime);
	}

	if (currentDirection == forward && cyclingRings[currentFan].GetCurrentIndex() == 6)
	{
		cyclingRings[currentFan].GetNextFadingColor().SetToEndingColor();
		++currentFan;
		if (currentFan >= cyclingRings.size())
		{
			currentFan = cyclingRings.size() - 1;
			currentDirection = backward;
		}
	}
	else if (currentDirection == backward && cyclingRings[currentFan].GetCurrentIndex() == 0)
	{
		cyclingRings[currentFan].GetNextFadingColor().SetToEndingColor();
		--currentFan;
		if (currentFan < 0)
		{
			currentFan = 0;
			currentDirection = forward;
		}
	}

	for (int i = 0; i < listOfFans.size(); ++i)
	{
		std::vector<CorsairLedColor> fanColors;
		for (int j = 0; j < cyclingRings[i].Size(); ++j)
		{
			fanColors.push_back(cyclingRings[i].GetRingColor(j));
		}
		listOfFans[i]->UpdateOuterRingLEDColors(fanColors);
	}
}

int FigureEightFans::GetFanCount()
{
	return listOfFans.size();
}
