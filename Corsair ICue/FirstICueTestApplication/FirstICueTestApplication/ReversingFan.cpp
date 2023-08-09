#pragma once

#include "ReversingFan.h"

ReversingFan::ReversingFan(Fan* fan, float reverseTime) : targetFan(fan), duration(reverseTime), timer(0.0f)
{

}

ReversingFan::ReversingFan(Fan* fan, tinyxml2::XMLNode* node) : targetFan(fan), timer(0.0f)
{
	duration = 0.0f;

	tinyxml2::XMLNode* child = node->FirstChild();
	while (child != NULL)
	{
		std::string childName = child->Value();
		if (childName.compare("Duration") == 0)
		{
			child->ToElement()->QueryFloatText(&duration);
		}

		child = child->NextSibling();
	}
}

void ReversingFan::Update(float deltaTime)
{
	if (targetFan != NULL && timer >= duration)
	{
		targetFan->ReverseInnerFanList();
		targetFan->ReverseOuterFanList();
		timer -= duration;
	}

	timer += deltaTime;
}
