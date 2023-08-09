#pragma once

#include "tinyxml2.h"

class FanSetting
{
public:
	FanSetting(tinyxml2::XMLNode* parentNode);

	int fanIndex;
	int innerOffset;
	int outerOffset;
	bool reverseInner;
	bool reverseOuter;
private:
	FanSetting();
	FanSetting(FanSetting& rhs);
};