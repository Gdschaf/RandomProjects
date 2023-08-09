#pragma once

#include <vector>

#include "tinyxml2.h"

#include "CycleSystem.h"
#include "FadingColor.h"
#include "Fan.h"
#include "CyclingRing.h"

class FigureEightFans : public CycleElement
{
public:
	FigureEightFans(std::vector<Fan*> fans, FadingColor color);
	FigureEightFans(std::vector<Fan*> fans, tinyxml2::XMLNode* node);
	virtual void Update(float deltaTime);
	int GetFanCount();
protected:
	enum direction
	{
		forward,
		backward
	};

	std::vector<Fan*> listOfFans;
	std::vector<CyclingRing> cyclingRings;

	direction currentDirection;
	int currentFan;
};