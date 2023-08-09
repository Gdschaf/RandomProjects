#pragma once

#include "tinyxml2.h"

#include "CycleSystem.h"
#include "Fan.h"

class ReversingFan : public CycleElement 
{
public:
	ReversingFan(Fan* fan, float reverseTime);
	ReversingFan(Fan* fan, tinyxml2::XMLNode* node);
	virtual void Update(float deltaTime);
protected:
	Fan* targetFan;
	float duration;
	float timer;
};