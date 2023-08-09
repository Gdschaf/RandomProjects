#include <vector>
#include "CyclingFan.h"

//fan needs to be adjusted properly before being passed in.
CyclingFan::CyclingFan(Fan * fan, FadingColor color) : targetFan(fan)
{
	outerRing = CyclingRing(fan->OuterRingLEDCount(), color);
	innerRing = CyclingRing(fan->InnerRingLEDCount(), color);
}

CyclingFan::CyclingFan(Fan * fan, FadingColor innerColor, FadingColor outerColor) : targetFan(fan)
{
	outerRing = CyclingRing(fan->OuterRingLEDCount(), outerColor);
	innerRing = CyclingRing(fan->InnerRingLEDCount(), innerColor);
}

CyclingFan::CyclingFan(Fan* fan, tinyxml2::XMLNode* node) : targetFan(fan)
{
	tinyxml2::XMLNode* child = node->FirstChild();
	while (child != NULL)
	{
		std::string childName = child->Value();
		if (childName.compare("CyclingRing") == 0)
		{
			tinyxml2::XMLElement* childElement = child->ToElement();
			const char* elementName;
			childElement->QueryStringAttribute("name", &elementName);
			if (std::string(elementName).compare("inner") == 0)
			{
				innerRing = CyclingRing(fan->InnerRingLEDCount(), child);
			}
			else if (std::string(elementName).compare("outer") == 0)
			{
				outerRing = CyclingRing(fan->OuterRingLEDCount(), child);
			}
		}

		child = child->NextSibling();
	}
}

void CyclingFan::Update(float deltaTime)
{
	outerRing.Update(deltaTime);
	innerRing.Update(deltaTime);

	//now that the ring colors are updated, actually update the fan LEDs here
	std::vector<CorsairLedColor> outerColors;
	std::vector<CorsairLedColor> innerColors;

	for (int i = 0; i < outerRing.Size(); ++i)
	{
		outerColors.push_back(outerRing.GetRingColor(i));
	}
	for (int i = 0; i < innerRing.Size(); ++i)
	{
		innerColors.push_back(innerRing.GetRingColor(i));
	}

	targetFan->UpdateInnerRingLEDColors(innerColors);
	targetFan->UpdateOuterRingLEDColors(outerColors);
}

void CyclingFan::Initialize()
{
	outerRing.Initialize();
	innerRing.Initialize();
}

CyclingRing& CyclingFan::GetOuterRing()
{
	return outerRing;
}

CyclingRing& CyclingFan::GetInnerRing()
{
	return innerRing;
}
