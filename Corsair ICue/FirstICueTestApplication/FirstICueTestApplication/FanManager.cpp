#include <CUESDK.h>

#include "FanManager.h"

const std::vector<CorsairLedId> DIYDeviceStartingIDs =
{
	CLD_C1_1,
	CLD_C2_1
};

FanManager::~FanManager()
{
	//make sure to delete all fans
	for (int i = 0; i < ListOfFans.size(); ++i)
	{
		delete ListOfFans[i];
	}
}

void FanManager::FindConnectedFans()
{
	//this is assuming that the corsair handshake was successfully done before this
	int numberOfConnectedDevices = CorsairGetDeviceCount();

	CorsairError lastError = CorsairGetLastError();
	if (lastError == CE_ServerNotFound)
	{
		std::cout << "Could not get device count, the server was not found." << std::endl;
		return;
	}
	else if (lastError == CE_ProtocolHandshakeMissing)
	{
		std::cout << "Could not get device count, protocol handshake is missing." << std::endl;
		return;
	}

	if (numberOfConnectedDevices != -1)
	{
		//there's actually connect devices!
		//I'm really not sure if this will be 0 if there's only 1 connected device? 
		//I wouldn't think so but idk
		for (int i = 0; i < numberOfConnectedDevices; ++i)
		{
			CorsairDeviceInfo * deviceInfo = CorsairGetDeviceInfo(i);
			lastError = CorsairGetLastError();
			if (lastError == CE_InvalidArguments)
			{
				std::cout << "The device index \"" << i << "\" was not valid while trying to get device info." << std::endl;
			}

			//this shouldn't be null unless there's an error which is handled above.
			if (deviceInfo != NULL)
			{
				//I'm not sure which will have the LL fans, but we know it's not a mouse or keyboard or headset soo....
				if (deviceInfo->type == CDT_CommanderPro || deviceInfo->type == CDT_LightingNodePro)
				{
					//loop through the channels on this device
					for (int j = 0; j < deviceInfo->channels.channelsCount; ++j)
					{
						CorsairChannelInfo channelInfo = deviceInfo->channels.channels[j];
						//this is where we do the CLD_C1 or CLD_C2 depending on the DIY channel I believe?
						int currentLEDCount = 0;
						for (int k = 0; k < channelInfo.devicesCount; ++k)
						{
							if (channelInfo.devices[k].type == CCDT_LL_Fan)
							{
								//this is where we want to make the Fan and add it
								ListOfFans.push_back(new Fan((CorsairLedId)(DIYDeviceStartingIDs[j] + currentLEDCount), i));
							}
							currentLEDCount += channelInfo.devices[k].deviceLedCount;
						}
					}
				}
			}
		}
	}
}

int FanManager::GetConnectedFanCount()
{
	return (int)ListOfFans.size();
}

Fan* FanManager::GetFanByIndex(int fanIndex)
{
	if (fanIndex < ListOfFans.size() && fanIndex >= 0)
		return ListOfFans[fanIndex];
	return NULL;
}
