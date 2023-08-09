#include <iostream>

#include "XMLHelper.h"

FanSetting::FanSetting(tinyxml2::XMLNode* parentNode) : fanIndex(-1), innerOffset(0), outerOffset(0), reverseInner(false), reverseOuter(false)
{
	tinyxml2::XMLElement* parentElement = parentNode->ToElement();
	parentElement->QueryIntAttribute("index", &fanIndex);

	tinyxml2::XMLNode* fanChild = parentNode->FirstChild();

	while (fanChild != NULL)
	{
		std::string fanValue = fanChild->Value();

		tinyxml2::XMLElement* fanElement = fanChild->ToElement();
		if (fanValue.compare("Offset") == 0)
		{
			int offsetValue;
			fanElement->QueryIntText(&offsetValue);

			const char* offsetName;
			fanElement->QueryStringAttribute("name", &offsetName);

			if (std::string(offsetName).compare("inner") == 0)
			{
				innerOffset = offsetValue;
			}
			else if (std::string(offsetName).compare("outer") == 0)
			{
				outerOffset = offsetValue;
			}
		}
		else if (fanValue.compare("Reverse") == 0)
		{
			std::string reverseText(fanElement->GetText());

			const char* reverseName;
			fanElement->QueryStringAttribute("name", &reverseName);

			if (std::string(reverseName).compare("inner") == 0)
			{
				if (reverseText.compare("true") == 0)
					reverseInner = true;
			}
			else if (std::string(reverseName).compare("outer") == 0)
			{
				if (reverseText.compare("true") == 0)
					reverseOuter = true;
			}
		}

		fanChild = fanChild->NextSibling();
	}
}
