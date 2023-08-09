#include <fstream>
#include <iostream>
#include <algorithm>

#include "SyntaxLine.h"

int main(void)
{
  std::fstream file;
  file.open("input.txt");
  if (file.is_open())
  {
    std::string line;
    int totalScore = 0;
    std::vector<unsigned long long> completionScores = std::vector<unsigned long long>();
    while (std::getline(file, line))
    {
      SyntaxLine s = SyntaxLine(line);
      if (!s.isCorrupt())
        completionScores.push_back(s.getCompletionScore());
      totalScore += s.getPointValue();
    }
    std::cout << "Total syntax score was " << totalScore << std::endl;

    std::sort(completionScores.begin(), completionScores.end());
    unsigned long long middleScore = completionScores[completionScores.size() / 2];
    std::cout << "The middle score is " << middleScore << std::endl;
  }
}