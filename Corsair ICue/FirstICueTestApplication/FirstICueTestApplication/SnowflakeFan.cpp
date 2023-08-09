#include "SnowflakeFan.h"

SnowflakeFan::SnowflakeFan(Fan* fan) : targetFan(fan), timer(0.0f)
{
	//try these values?
	minimumRandomFadeTime = 1.0f;
	maximumRadnomFadeTime = 2.0f;

	minimumRandomSpawnTime = 0.1f;
	maximumRandomSpawnTime = 0.5f;

	currentDuration = getRandomTime(minimumRandomSpawnTime, maximumRandomSpawnTime);

	for (int i = 0; i < fan->TotalLEDCount(); ++i)
	{
		randomLEDs.push_back(FadingColor());
	}
}

SnowflakeFan::SnowflakeFan(Fan* fan, tinyxml2::XMLNode* node) : targetFan(fan), timer(0.0f)
{
	minimumRandomFadeTime = 0.0f;
	maximumRadnomFadeTime = 0.0f;
	minimumRandomSpawnTime = 0.0f;
	maximumRandomSpawnTime = 0.0f;

	tinyxml2::XMLNode* child = node->FirstChild();
	while (child != NULL)
	{
		std::string childName = child->Value();
		tinyxml2::XMLElement * childElement = child->ToElement();

		if (childName.compare("MinimumSpawnTime") == 0)
		{
			childElement->QueryFloatText(&minimumRandomSpawnTime);
		}
		else if (childName.compare("MaximumSpawnTime") == 0)
		{
			childElement->QueryFloatText(&maximumRandomSpawnTime);
		}
		else if (childName.compare("MinimumFadeTime") == 0)
		{
			childElement->QueryFloatText(&minimumRandomFadeTime);
		}
		else if (childName.compare("MaximumFadeTime") == 0)
		{
			childElement->QueryFloatText(&maximumRadnomFadeTime);
		}

		child = child->NextSibling();
	}

	currentDuration = getRandomTime(minimumRandomSpawnTime, maximumRandomSpawnTime);

	for (int i = 0; i < fan->TotalLEDCount(); ++i)
	{
		randomLEDs.push_back(FadingColor());
	}
}

void SnowflakeFan::Update(float deltaTime)
{
	//update all fading LEDs first
	for (int i = 0; i < randomLEDs.size(); ++i)
	{
		randomLEDs[i].Update(deltaTime);
	}

	//check if we should spawn a new led
	if (timer >= currentDuration)
	{
		int nextLED = rand() % randomLEDs.size();
		randomLEDs[nextLED].StopFading(); //just in case?
		randomLEDs[nextLED].SetToStartingColor();
		randomLEDs[nextLED].SetFadingDuration(getRandomTime(minimumRandomFadeTime, maximumRadnomFadeTime));
		randomLEDs[nextLED].StartFading();

		timer -= currentDuration;
	}

	timer += deltaTime;

	updateCorsairLEDs();
}

float SnowflakeFan::getRandomTime(float min, float max)
{
	return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
}

void SnowflakeFan::updateCorsairLEDs()
{
	std::vector<CorsairLedColor> outerColors;
	std::vector<CorsairLedColor> innerColors;
	for (int i = 0; i < randomLEDs.size(); ++i)
	{
		if (i < targetFan->InnerRingLEDCount())
			innerColors.push_back(randomLEDs[i].GetCurrentColor());
		else
			outerColors.push_back(randomLEDs[i].GetCurrentColor());
	}

	targetFan->UpdateInnerRingLEDColors(innerColors);
	targetFan->UpdateOuterRingLEDColors(outerColors);
}
