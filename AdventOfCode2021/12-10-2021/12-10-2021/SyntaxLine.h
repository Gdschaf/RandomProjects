#pragma once

#include <string>
#include <vector>

class SyntaxLine
{
public:
  SyntaxLine(std::string input);
  int getPointValue();
  unsigned long long getCompletionScore();
  bool hasCompletionString() { return !completionString.empty(); }
  bool isCorrupt() { return firstIncorrectIndex != line.size(); }

  std::string line;
  int firstIncorrectIndex;
private:
  void findFirstIncorrectIndex();
  char getComplimentaryChar(char c);
  void calculateCompletionString();

  std::vector<char> completionString = std::vector<char>();
};