#pragma once

#include "tinyxml2.h"

#include "CycleSystem.h"
#include "Fan.h"
#include "FadingColor.h"

class SnowflakeFan : public CycleElement
{
public:
	SnowflakeFan(Fan* fan);
	SnowflakeFan(Fan* fan, tinyxml2::XMLNode* node);
	virtual void Update(float deltaTime);
protected:
	Fan* targetFan;

	//I don't know how I'm going to make these settable yet
	float minimumRandomSpawnTime;
	float maximumRandomSpawnTime;

	float minimumRandomFadeTime;
	float maximumRadnomFadeTime;

	float timer;
	float currentDuration;

	std::vector<FadingColor> randomLEDs;

	//utility for helping get random floats
	float getRandomTime(float min, float max);

	void updateCorsairLEDs();
};