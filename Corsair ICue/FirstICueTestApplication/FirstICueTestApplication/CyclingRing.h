#pragma once

#include "tinyxml2.h"

#include "FadingColor.h"
#include "LoopedLinkedList.h"

#define DEFAULT_RING_RPM 80

class CyclingRing
{
public:
	virtual void Update(float deltaTime);
	void UpdateFadingColors(float deltaTime);
	CyclingRing(int ledCount, FadingColor color, int RPM = DEFAULT_RING_RPM);
	CyclingRing(int ledCount, tinyxml2::XMLNode* node);
	CyclingRing();
	CyclingRing(const CyclingRing& rhs);
	void Initialize();
	Color GetRingColor(int index);
	int Size();
	void EnableRainbowPuke();
	int GetCurrentIndex();
	void SetCurrentIndex(int index);
	FadingColor& GetCurrentFadingColor();
	FadingColor& GetNextFadingColor();

	CyclingRing& operator=(const CyclingRing& rhs);
protected:
	//this is less trash
	FadingColor fadingColor;
	int revolutionsPerMinute;
	float timer;
	LoopedLinkedList<FadingColor> ringColors;

	bool rainbowPuke;
private:
	int currentIndex;
};