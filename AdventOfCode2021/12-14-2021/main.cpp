#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

#include "DoubleLinkedList.h"

#define NUM_STEPS 40

struct Insertion
{
  std::vector<std::string> pairs = std::vector<std::string>();
  char character;
};

void printInsertionRules(std::unordered_map<std::string, Insertion>& map)
{
  std::unordered_map<std::string, Insertion>::iterator itEnd = map.end();
  for (std::unordered_map<std::string, Insertion>::iterator it = map.begin(); it != itEnd; ++it)
  {
    std::cout << it->first << " -> " << it->second.character << std::endl;
  }
}

unsigned long long getMostCommon(std::unordered_map<char, unsigned long long>& charCount)
{
  unsigned long long highestCount = 0;
  std::unordered_map<char, unsigned long long>::iterator itEnd = charCount.end();
  for (std::unordered_map<char, unsigned long long>::iterator it = charCount.begin(); it != itEnd; ++it)
  {
    if (it->second > highestCount)
      highestCount = it->second;
  }

  return highestCount;
}

unsigned long long getLeastCommon(std::unordered_map<char, unsigned long long>& charCount)
{
  unsigned long long lowestCount = ULLONG_MAX;
  std::unordered_map<char, unsigned long long>::iterator itEnd = charCount.end();
  for (std::unordered_map<char, unsigned long long>::iterator it = charCount.begin(); it != itEnd; ++it)
  {
    if (it->second < lowestCount)
      lowestCount = it->second;
  }

  return lowestCount;
}

int main(void)
{
  std::fstream file;
  file.open("input.txt");
  //file.open("example.txt");
  if (file.is_open())
  {
    std::string line;
    int lineCount = 1;
    std::unordered_map<std::string, Insertion> insertionRules = std::unordered_map<std::string, Insertion>();
    std::unordered_map<char, unsigned long long> characterCount = std::unordered_map<char, unsigned long long>();
    std::string polymerTemplate;
    while (std::getline(file, line))
    {
      if (lineCount == 1)
      {
        polymerTemplate = line;
        for (int i = 0; i < line.size(); ++i)
        {
          ++characterCount[line[i]];
        }
      }
      else if (lineCount >= 3)
      {
        std::string key = line.substr(0, 2);
        char value = line[6];
        Insertion i = Insertion();
        i.character = value;
        std::string pair1 = std::string(1, key[0]);
        pair1 += value;
        std::string pair2 = std::string(1, value);
        pair2 += key[1];
        i.pairs.push_back(pair1);
        i.pairs.push_back(pair2);
        insertionRules[key] = i;
      }

      ++lineCount;
    }
    file.close();

    std::cout << polymerTemplate << std::endl;
    std::cout << "Polymer Template length is " << polymerTemplate.size() << std::endl;
    std::cout << std::endl;
    printInsertionRules(insertionRules);

    std::unordered_map<std::string, unsigned long long> pairCounts = std::unordered_map<std::string, unsigned long long>();
    for (int i = 1; i < polymerTemplate.size(); ++i)
    {
      std::string pair = std::string(1, polymerTemplate[i - 1]);
      pair += polymerTemplate[i];
      if (insertionRules.find(pair) != insertionRules.end())
      {
        ++pairCounts[pair];
      }
    }

    for (int i = 0; i < NUM_STEPS; ++i)
    {
      std::unordered_map<std::string, unsigned long long> tempPairCounts = std::unordered_map<std::string, unsigned long long>();
      std::unordered_map<std::string, unsigned long long>::iterator itEnd = pairCounts.end();
      for (std::unordered_map<std::string, unsigned long long>::iterator it = pairCounts.begin(); it != itEnd; ++it)
      {
        Insertion i = insertionRules[it->first];
        characterCount[i.character] += it->second;
        for (int x = 0; x < i.pairs.size(); ++x)
        {
          if (insertionRules.find(i.pairs[x]) != insertionRules.end())
          {
            tempPairCounts[i.pairs[x]] += it->second;
          }
        }
      }
      pairCounts = tempPairCounts;
    }

    unsigned long long max = getMostCommon(characterCount);
    unsigned long long min = getLeastCommon(characterCount);

    std::cout << max << " - " << min << " = " << (max - min) << std::endl;
  }
}