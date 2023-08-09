#pragma once

#include "tinyxml2.h"

#include "Color.h"

class FadingColor
{
public:
	FadingColor(float duration, Color start, Color end = Color_Black);
	FadingColor(tinyxml2::XMLNode* node);
	FadingColor();
	void Update(float deltaTime);
	void ResetTimer();
	void StartFading();
	void PauseFading();
	void StopFading();
	void SetToStartingColor();
	void SetToEndingColor();
	Color GetCurrentColor();
	void ManuallySetCurrentColor(Color c);
	void ManuallySetStartingColor(Color c);
	Color CalculateFadeInColor(float percentage);
	Color CalculateFadeOutColor(float percentage);
	void SetFadingDuration(float duration);

	FadingColor& operator=(const FadingColor& rhs);
protected:
	short SnipValue(float v);

	Color startingColor;
	Color endingColor;
	Color currentColor;
	float fadeDuration;
	float timer;
	bool fading;
};