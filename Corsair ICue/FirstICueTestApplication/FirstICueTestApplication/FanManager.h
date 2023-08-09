#pragma once

#include <vector>

#include "Fan.h"

class FanManager
{
public:
	~FanManager();
	void FindConnectedFans();
	int GetConnectedFanCount();
	Fan* GetFanByIndex(int fanIndex);
protected:
	std::vector<Fan*> ListOfFans;
};