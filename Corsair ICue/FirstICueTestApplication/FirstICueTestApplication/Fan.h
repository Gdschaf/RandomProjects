#pragma once

#include <CUESDK.h>
#include <vector>

#include "LoopedLinkedList.h"

class Fan
{
public:
	Fan(CorsairLedId, int deviceIndex = -1);
	Fan(Fan &rhs);

	void OffsetInnerFanList(int offset);
	void OffsetOuterFanList(int offset);
	void ReverseInnerFanList() { innerFanList.reverse(); }
	void ReverseOuterFanList() { outerFanList.reverse(); }

	int OuterRingLEDCount();
	int InnerRingLEDCount();
	int TotalLEDCount();

	void UpdateOuterRingLEDColors(std::vector<CorsairLedColor> ledColors);
	void UpdateInnerRingLEDColors(std::vector<CorsairLedColor> ledColors);

	friend std::ostream & operator<<(std::ostream & os, Fan & rhs);
protected:
	const int ledCount = 16;
	const int innerRingCount = 4;
	const int outerRingCount = 12;

	const CorsairLedId fanStartingId;

	int connectedDeviceIndex;

	LoopedLinkedList<CorsairLedId> outerFanList;
	LoopedLinkedList<CorsairLedId> innerFanList;
};