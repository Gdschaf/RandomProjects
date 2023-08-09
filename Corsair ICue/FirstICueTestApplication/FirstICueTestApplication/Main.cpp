#define CORSAIR_LIGHTING_SDK_DISABLE_DEPRECATION_WARNINGS

#include <CUESDK.h>

#include <iostream>
#include <vector>
#include <unordered_set>
#include <thread>
#include <atomic>
#include <conio.h>
#include <windows.h>
#include <tchar.h>

#include "Fan.h"
#include "CycleSystem.h"
#include "CorsairLedIdStrings.h"
#include "CyclingFan.h"
#include "ReversingFan.h"
#include "FanManager.h"
#include "SnowflakeFan.h"
#include "FigureEightFans.h"
#include "XMLHelper.h"

void TestFanClass()
{
	Fan fan1(CLD_C1_1);
	Fan fan2(CLD_C1_17);

	std::cout << fan1 << std::endl << fan2 << std::endl;

	fan1.OffsetInnerFanList(2);
	fan1.OffsetOuterFanList(-3);

	std::cout << std::endl << "Offset" << std::endl << fan1 << std::endl;

	fan1.ReverseOuterFanList();

	std::cout << std::endl << "Reverse" << std::endl << fan1 << std::endl;
}

void TestGameLoop()
{
	Fan f1(CLD_C1_1);
	Fan f2(CLD_C1_17);
	f2.OffsetOuterFanList(3);
	f2.OffsetInnerFanList(1);

	CycleSystem gameLoop;

	//add cycling elements here
	gameLoop.AddElement(new CyclingFan(&f1, FadingColor(0.5f, Color_White)));
	CyclingFan* addThis = new CyclingFan(&f2, FadingColor(0.3f, Color_Blue));
	//addThis->GetOuterRing().EnableRainbowPuke();
	gameLoop.AddElement(addThis);
	gameLoop.AddElement(new ReversingFan(&f2, 1.5f));

	gameLoop.Initialize();
	gameLoop.StartCycle(); //this will loop until something interrupts it, need to add input for that.
}

void TestFanManager()
{
	FanManager fanManager;
	fanManager.FindConnectedFans();

	std::cout << "Number of connect LL fans: " << fanManager.GetConnectedFanCount() << std::endl;
	
	//easy way for me to visually tell which fan is which in the fan manager
	std::vector<Color> colorForIndex =
	{
		Color_White,
		Color_Red,
		Color_Green,
		Color_Blue
	};

	//this fan needs offsetting for it look better.
	//I think that I have this functionality, but I need a better way to set this up
	fanManager.GetFanByIndex(1)->OffsetOuterFanList(3);
	fanManager.GetFanByIndex(1)->OffsetInnerFanList(1);

	CycleSystem gameLoop;

	for (int i = 0; i < fanManager.GetConnectedFanCount(); ++i)
	{
		//gameLoop.AddElement(new CyclingFan(fanManager.GetFanByIndex(i), FadingColor(0.5, colorForIndex[i])));
		gameLoop.AddElement(new SnowflakeFan(fanManager.GetFanByIndex(i)));
	}

	gameLoop.Initialize();
	gameLoop.StartCycle();
}

void TestFigureEight()
{
	FanManager fanManager;
	fanManager.FindConnectedFans();

	fanManager.GetFanByIndex(1)->ReverseOuterFanList();
	fanManager.GetFanByIndex(1)->OffsetOuterFanList(5);

	fanManager.GetFanByIndex(0)->OffsetOuterFanList(3);

	CycleSystem gameLoop;

	std::vector<Fan*> allConnectedFans;
	for (int i = 0; i < fanManager.GetConnectedFanCount(); ++i)
	{
		allConnectedFans.push_back(fanManager.GetFanByIndex(i));
	}

	gameLoop.AddElement(new FigureEightFans(allConnectedFans, FadingColor(0.5f, Color_Blue)));

	gameLoop.Initialize();
	gameLoop.StartCycle();
}

void SerializeFanSettings(tinyxml2::XMLNode* node, FanManager & fanManager)
{
	tinyxml2::XMLNode* fanChild = node->FirstChild();
	while (fanChild != NULL)
	{
		FanSetting settings(fanChild);

		Fan* f = fanManager.GetFanByIndex(settings.fanIndex);
		if (settings.reverseInner)
			f->ReverseInnerFanList();
		if (settings.reverseOuter)
			f->ReverseOuterFanList();
		if (settings.innerOffset != 0)
			f->OffsetInnerFanList(settings.innerOffset);
		if (settings.outerOffset != 0)
			f->OffsetOuterFanList(settings.outerOffset);

		fanChild = fanChild->NextSibling();
	}
}

void SerializeCycleElements(tinyxml2::XMLNode* node, CycleSystem& gameLoop, FanManager& fanManager)
{
	tinyxml2::XMLNode* elementsChild = node->FirstChild();
	while (elementsChild != NULL)
	{
		std::string elementName = elementsChild->Value();
		if (elementName.compare("CyclingFan") == 0)
		{
			tinyxml2::XMLElement* element = elementsChild->ToElement();
			int fanIndex;
			element->QueryIntAttribute("index", &fanIndex);
			if (fanIndex < fanManager.GetConnectedFanCount())
				gameLoop.AddElement(new CyclingFan(fanManager.GetFanByIndex(fanIndex), elementsChild));
		}
		else if (elementName.compare("SnowflakeFan") == 0)
		{
			tinyxml2::XMLElement* element = elementsChild->ToElement();
			int fanIndex;
			element->QueryIntAttribute("index", &fanIndex);
			if (fanIndex < fanManager.GetConnectedFanCount())
				gameLoop.AddElement(new SnowflakeFan(fanManager.GetFanByIndex(fanIndex), elementsChild));
		}
		else if (elementName.compare("ReversingFan") == 0)
		{
			tinyxml2::XMLElement* element = elementsChild->ToElement();
			int fanIndex;
			element->QueryIntAttribute("index", &fanIndex);
			if (fanIndex < fanManager.GetConnectedFanCount())
				gameLoop.AddElement(new ReversingFan(fanManager.GetFanByIndex(fanIndex), elementsChild));
		}
		else if (elementName.compare("FigureEightFan") == 0)
		{
			std::vector<Fan*> listOfFans;
			tinyxml2::XMLNode* figureEightChild = elementsChild->FirstChild();
			while (figureEightChild != NULL)
			{
				std::string figureEightChildName = figureEightChild->Value();
				if (figureEightChildName.compare("ListOfFans") == 0)
				{
					tinyxml2::XMLNode* listOfFansChild = figureEightChild->FirstChild();
					while (listOfFansChild != NULL)
					{
						std::string listOfFansChildName = listOfFansChild->Value();
						if (listOfFansChildName.compare("FanIndex") == 0)
						{
							tinyxml2::XMLElement* fanIndexElement = listOfFansChild->ToElement();
							int newFanIndex;
							fanIndexElement->QueryIntText(&newFanIndex);
							if (newFanIndex < fanManager.GetConnectedFanCount())
								listOfFans.push_back(fanManager.GetFanByIndex(newFanIndex));
						}

						listOfFansChild = listOfFansChild->NextSibling();
					}
				}

				figureEightChild = figureEightChild->NextSibling();
			}

			gameLoop.AddElement(new FigureEightFans(listOfFans, elementsChild));
		}

		elementsChild = elementsChild->NextSibling();
	}
}

void TestXMLSerialization()
{
	FanManager fanManager;
	fanManager.FindConnectedFans();

	CycleSystem gameLoop;

	tinyxml2::XMLDocument doc;
	doc.LoadFile("Settings.xml");
	if (!doc.Error())
	{
		tinyxml2::XMLNode* child = doc.FirstChild();
		child = child->FirstChild(); //this is because we added that <CorsairSettings> tag because "there can't be more then one root element in an xml file" or something... it was still working but the "error" was bugging me
		while (child != NULL)
		{
			std::string value = child->Value();
			if (value.compare("FanSettings") == 0)
			{
				SerializeFanSettings(child, fanManager);
			}
			else if (value.compare("CyclingElements") == 0)
			{
				SerializeCycleElements(child, gameLoop, fanManager);
			}
			child = child->NextSibling();
		}
	}
	else
	{
		std::cout << "XML document had an error while trying to load: " << doc.ErrorIDToName(doc.ErrorID()) << std::endl;
	}

	gameLoop.Initialize();
	gameLoop.StartCycle();
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//seed the random number generator at the start
	srand((unsigned)time(NULL));

	CorsairPerformProtocolHandshake();
	CorsairError lastError = CorsairGetLastError();
	if (lastError == CE_ServerNotFound)
	{
		std::cout << "Server not found when trying to perform protocol handshake." << std::endl;
		return -1;
	}
	CorsairRequestControl(CAM_ExclusiveLightingControl);

	//TestFanClass();

	//TestGameLoop();

	//TestFanManager();

	//TestFigureEight();

	TestXMLSerialization();

	_getch();
}