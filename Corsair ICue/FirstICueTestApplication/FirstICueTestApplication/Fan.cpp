#define CORSAIR_LIGHTING_SDK_DISABLE_DEPRECATION_WARNINGS

#include "Fan.h"
#include "CorsairLedIdStrings.h"

std::ostream & operator<<(std::ostream & os, LoopedLinkedList<CorsairLedId> & rhs)
{
	int listSize = rhs.size();
	for (int i = 0; i < listSize; ++i)
	{
		os << LedIdToString.find(rhs[i])->second.c_str();
		if (i != listSize - 1)
			os << " -> ";
	}
	return os;
}

Fan::Fan(CorsairLedId startingId, int deviceIndex) : fanStartingId(startingId), connectedDeviceIndex(deviceIndex)
{
	for (int i = 0; i < ledCount; ++i)
	{
		if (i < innerRingCount)
			innerFanList.push_back((CorsairLedId)(((int)fanStartingId) + i));
		else
			outerFanList.push_back((CorsairLedId)(((int)fanStartingId) + i));
	}
}

Fan::Fan(Fan &rhs) : fanStartingId(rhs.fanStartingId), connectedDeviceIndex(rhs.connectedDeviceIndex)
{
	innerFanList = rhs.innerFanList;
	outerFanList = rhs.outerFanList;
}

void Fan::OffsetInnerFanList(int offset)
{
	if(offset != 0)
		innerFanList.rotate(offset);
}

void Fan::OffsetOuterFanList(int offset)
{
	if(offset != 0)
		outerFanList.rotate(offset);
}

int Fan::OuterRingLEDCount()
{
	return outerRingCount;
}

int Fan::InnerRingLEDCount()
{
	return innerRingCount;
}

int Fan::TotalLEDCount()
{
	return ledCount;
}

void Fan::UpdateOuterRingLEDColors(std::vector<CorsairLedColor> ledColors)
{
	for (int i = 0; i < ledColors.size(); ++i)
	{
		ledColors[i].ledId = outerFanList[i];
	}

	if (connectedDeviceIndex == -1)
		CorsairSetLedsColors(static_cast<int>(ledColors.size()), ledColors.data());
	else
		CorsairSetLedsColorsBufferByDeviceIndex(connectedDeviceIndex, (int)ledColors.size(), ledColors.data());
}

void Fan::UpdateInnerRingLEDColors(std::vector<CorsairLedColor> ledColors)
{
	for (int i = 0; i < ledColors.size(); ++i)
	{
		ledColors[i].ledId = innerFanList[i];
	}

	if (connectedDeviceIndex == -1)
		CorsairSetLedsColors(static_cast<int>(ledColors.size()), ledColors.data());
	else
		CorsairSetLedsColorsBufferByDeviceIndex(connectedDeviceIndex, (int)ledColors.size(), ledColors.data());
}

std::ostream & operator<<(std::ostream & os, Fan & rhs)
{
	os << "Inner fan IDs: " << rhs.innerFanList << std::endl << "Outer fan IDs: " << rhs.outerFanList;
	return os;
}