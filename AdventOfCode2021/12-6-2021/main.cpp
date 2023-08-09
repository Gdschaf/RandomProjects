#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#define DAYS 256

unsigned long long getCount(std::unordered_map<int, unsigned long long> map)
{
  unsigned long long total = 0;
  std::unordered_map<int, unsigned long long>::iterator itEnd = map.end();
  for (std::unordered_map<int, unsigned long long>::iterator it = map.begin(); it != itEnd; ++it)
  {
    total += it->second;
  }
  return total;
}

int main(void)
{
  std::fstream file;
  file.open("input.txt");
  if (file.is_open())
  {
    std::string line;
    std::unordered_map<int, unsigned long long> fishesMap = std::unordered_map<int, unsigned long long>();
    while (std::getline(file, line))
    {
      for (int i = 0; i < line.size(); i += 2)
      {
        ++fishesMap[line[i] - '0'];
      }
    }
    file.close();

    for (int i = 0; i < DAYS; ++i)
    {
      std::unordered_map<int, unsigned long long> tempMap = std::unordered_map<int, unsigned long long>();
      std::unordered_map<int, unsigned long long>::iterator itEnd = fishesMap.end();
      for (std::unordered_map<int, unsigned long long>::iterator it = fishesMap.begin(); it != itEnd; ++it)
      {
        if (it->first == 0)
        {
          tempMap[8] += it->second;
          tempMap[6] += it->second;
        }
        else
        {
          tempMap[it->first - 1] += it->second;
        }
      }
      fishesMap = tempMap;
    }

    unsigned long long total = getCount(fishesMap);


    std::cout << "The total number of fishes is " << total << std::endl;
  }
}