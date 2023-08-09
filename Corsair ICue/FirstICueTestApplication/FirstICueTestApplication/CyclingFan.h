#pragma once

#include <iostream>

#include "tinyxml2.h"

#include "Fan.h"
#include "CycleSystem.h"
#include "LoopedLinkedList.h"
#include "CyclingRing.h"

class CyclingFan : public CycleElement
{
public:
	CyclingFan(Fan* fan, FadingColor color);
	CyclingFan(Fan* fan, FadingColor innerColor, FadingColor outerColor);
	CyclingFan(Fan* fan, tinyxml2::XMLNode* node);
	virtual void Update(float deltaTime);
	virtual void Initialize();
	CyclingRing& GetOuterRing();
	CyclingRing& GetInnerRing();
protected:
	Fan * targetFan;

	CyclingRing outerRing;
	CyclingRing innerRing;
};