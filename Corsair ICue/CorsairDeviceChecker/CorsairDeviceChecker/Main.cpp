#define CORSAIR_LIGHTING_SDK_DISABLE_DEPRECATION_WARNINGS

#include <fstream>
#include <vector>
#include <string>
#include "conio.h"

#include "StreamRedirect.h"
#include "CorsairEnumStrings.h"

#define OUTPUT_FILE_NAME "DevicesOutput.txt"

class EventPrinter
{
public:
	void print(const CorsairEvent* e)
	{
		std::cout << "Event #" << std::to_string(++m_eventCounter) << std::endl;
		if (e->id == CEI_DeviceConnectionStatusChangedEvent) {
			printConnectionEvent(e->deviceConnectionStatusChangedEvent);
		}
	}
private:
	void printConnectionEvent(const CorsairDeviceConnectionStatusChangedEvent* e) const
	{
		std::cout << "Device id: " << e->deviceId
			<< "   Status: " << (e->isConnected ? "connected" : "disconnected") << std::endl;

	}

	int m_eventCounter = 0;
};

const std::vector<CorsairLedId> DIYDeviceStartingIDs =
{
	CLD_C1_1,
	CLD_C2_1
};

std::vector<CorsairLedId> GetAvailableLEDsForDevice(int deviceIndex)
{
	std::vector<CorsairLedId> availableLEDs;

	CorsairLedPositions* ledPositions = CorsairGetLedPositionsByDeviceIndex(deviceIndex);
	if (ledPositions != NULL)
	{
		for (int i = 0; i < ledPositions->numberOfLed; i++)
		{
			const CorsairLedId ledId = ledPositions->pLedPosition[i].ledId;
			availableLEDs.push_back(ledId);
		}
	}

	return availableLEDs;
}

std::vector<CorsairLedId> PrintOutCorsairConnectedDevices()
{
	std::vector<CorsairLedId> firstLEDs;

	int numberOfConnectedDevices = CorsairGetDeviceCount();
	CorsairError lastError = CorsairGetLastError();
	if (lastError == CE_ServerNotFound)
	{
		std::cout << "Could not get device count, the server was not found." << std::endl;
		return firstLEDs;
	}
	else if (lastError == CE_ProtocolHandshakeMissing)
	{
		std::cout << "Could not get device count, protocol handshake is missing." << std::endl;
		return firstLEDs;
	}

	if (numberOfConnectedDevices != -1)
	{
		std::cout << "There are " << numberOfConnectedDevices << " connected Corsair devices." << std::endl;
		std::cout << std::endl;

		for (int connectedDevice = 0; connectedDevice < numberOfConnectedDevices; ++connectedDevice)
		{
			CorsairDeviceInfo* deviceInfo = CorsairGetDeviceInfo(connectedDevice);
			lastError = CorsairGetLastError();
			if (lastError == CE_InvalidArguments)
			{
				std::cout << "The device index \"" << connectedDevice << "\" was not valid while trying to get device info." << std::endl;
			}

			//this shouldn't be null unless there's an error which is handled above.
			if (deviceInfo != NULL)
			{
				std::cout << "Device " << connectedDevice << ":" << std::endl;
				std::cout << "\tType: " << CorsairDeviceTypeStrings.find(deviceInfo->type)->second.c_str() << std::endl;
				std::cout << "\tModel: " << deviceInfo->model << std::endl;
				std::cout << "\tDevice ID: " << deviceInfo->deviceId << std::endl;
				std::cout << "\tLED Count: " << deviceInfo->ledsCount << std::endl;
				std::cout << "\tChannel Count: " << deviceInfo->channels.channelsCount << std::endl;

				std::vector<CorsairLedId> deviceAvailableLEDs = GetAvailableLEDsForDevice(connectedDevice);
				if (deviceAvailableLEDs.size() > 0)
				{
					std::cout << "\tAvailable LEDs:" << std::endl;
					for (int led = 0; led < (int)deviceAvailableLEDs.size(); ++led)
					{
						std::cout << "\t\t" << CorsairLedIdStrings.find(deviceAvailableLEDs[led])->second.c_str() << std::endl;
					}
				}

				std::cout << std::endl;

				for (int channel = 0; channel < deviceInfo->channels.channelsCount; ++channel)
				{
					std::cout << "\tChannel " << channel << ":" << std::endl;

					CorsairChannelInfo channelInfo = deviceInfo->channels.channels[channel];
					std::cout << "\t\tLED Count: " << channelInfo.totalLedsCount << std::endl;
					std::cout << "\t\tChannel Devices: " << channelInfo.devicesCount << std::endl;
					std::cout << std::endl;

					int currentLEDCount = 0;
					for (int channelDevice = 0; channelDevice < channelInfo.devicesCount; ++channelDevice)
					{
						std::cout << "\t\tChannel Device " << channelDevice << ":" << std::endl;
						std::cout << "\t\t\tType: " << CorsairChannelDeviceTypeStrings.find(channelInfo.devices[channelDevice].type)->second.c_str() << std::endl;
						std::cout << "\t\t\tLED Count: " << channelInfo.devices[channelDevice].deviceLedCount << std::endl;
						std::cout << std::endl;

						if (deviceInfo->type == CDT_LightingNodePro || deviceInfo->type == CDT_CommanderPro)
						{
							firstLEDs.push_back((CorsairLedId)(DIYDeviceStartingIDs[channel] + currentLEDCount));
							if (channelInfo.devices[channelDevice].type == CCDT_LL_Fan)
							{
								firstLEDs.push_back((CorsairLedId)(DIYDeviceStartingIDs[channel] + currentLEDCount + 4)); //4 is the inside LED count so we can light up the first LED on the outside
							}
						}
						currentLEDCount += channelInfo.devices[channelDevice].deviceLedCount;
					}
				}
			}
		}
	}

	return firstLEDs;
}

int main()
{
	CorsairPerformProtocolHandshake();
	CorsairError lastError = CorsairGetLastError();
	if (lastError == CE_ServerNotFound)
	{
		std::cout << "Server not found when trying to perform protocol handshake." << std::endl;
		return 0;
	}

	std::vector<CorsairLedId> firstLEDOfEachFan;

	std::ofstream outputFile;
	outputFile.open(OUTPUT_FILE_NAME);
	if (outputFile.is_open())
	{
		//comment this out to have it go to the console window, however, I'd like to find a way to output to a file and screen at the same time
		StreamRedirect redirectOutput(std::cout, outputFile);

		firstLEDOfEachFan = PrintOutCorsairConnectedDevices();

		outputFile.close();
	}

	bool worked = CorsairRequestControl(CAM_ExclusiveLightingControl);
	std::cout << "Request Control returned: " << worked << std::endl;


	const auto callback = [](void* context, const CorsairEvent* e) {
		EventPrinter* eventPrinter = static_cast<EventPrinter*>(context);
		eventPrinter->print(e);
	};

	//Context could be any class instance or any pointer. Client must ensure context is valid during callback execution
	EventPrinter context;
	CorsairSubscribeForEvents(callback, &context);

	//light up the first light of each fan
	std::vector<CorsairLedColor> listOfColors;
	for (int i = 0; i < firstLEDOfEachFan.size(); ++i)
	{
		CorsairLedColor newColor;
		newColor.ledId = firstLEDOfEachFan[i];
		newColor.r = 0;
		newColor.g = 0;
		newColor.b = 255;
		listOfColors.push_back(newColor);

		std::cout << "LED " << CorsairLedIdStrings.find(firstLEDOfEachFan[i])->second.c_str() << " should be lighting up." << std::endl;
	}
	CorsairSetLedsColors(static_cast<int>(listOfColors.size()), listOfColors.data());

	std::cout << "Press enter when you're done." << std::endl;
	_getch();

	CorsairUnsubscribeFromEvents();
	CorsairReleaseControl(CAM_ExclusiveLightingControl);
}