#pragma once

#include <vector>
#include <string>

inline std::vector<std::string> splitString(std::string input, char splitCharacter)
{
  std::vector<std::string> returnList = std::vector<std::string>();
  int startIndex = 0;
  for (int i = 0; i < input.length(); ++i)
  {
    if (input[i] == splitCharacter)
    {
      if (i - startIndex == 0)
      {
        ++startIndex;
        continue;
      }
      returnList.push_back(input.substr(startIndex, i - startIndex));
      startIndex = i + 1;
    }
  }
  returnList.push_back(input.substr(startIndex));
  return returnList;
}