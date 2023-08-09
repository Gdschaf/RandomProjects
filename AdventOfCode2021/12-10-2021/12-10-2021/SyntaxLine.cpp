#include <stack>
#include <iostream>

#include "SyntaxLine.h"

SyntaxLine::SyntaxLine(std::string input)
{
  line = input;
  findFirstIncorrectIndex();
  calculateCompletionString();
}

int SyntaxLine::getPointValue()
{
  if (firstIncorrectIndex == line.size())
    return 0;
  switch (line[firstIncorrectIndex])
  {
  case ')':
    return 3;
  case '}':
    return 1197;
  case ']':
    return 57;
  case '>':
    return 25137;
  }
  return 0;
}

//): 1 point.
//]: 2 points.
//}: 3 points.
//> : 4 points.
unsigned long long SyntaxLine::getCompletionScore()
{
  unsigned long long score = 0;
  std::string s;
  for (int i = 0; i < completionString.size(); ++i)
  {
    s += completionString[i];
    score *= 5;
    switch (completionString[i])
    {
    case ')':
      score += 1;
      break;
    case ']':
      score += 2;
      break;
    case '}':
      score += 3;
      break;
    case '>':
      score += 4;
      break;
    }
  }
  std::cout << line << " has a completion string of " << s << " and a score of " << score << std::endl;
  return score;
}

void SyntaxLine::findFirstIncorrectIndex()
{
  std::stack<char> syntaxStack = std::stack<char>();
  for (int i = 0; i < line.size(); ++i)
  {
    switch (line[i])
    {
    case '(':
    case '{':
    case '[':
    case '<':
      syntaxStack.push(line[i]);
      break;
    case ')':
    case '}':
    case ']':
    case '>':
      if (syntaxStack.top() == getComplimentaryChar(line[i]))
        syntaxStack.pop();
      else
      {
        firstIncorrectIndex = i;
        std::cout << line << "\t Looking for " << getComplimentaryChar(syntaxStack.top()) << " but found " << line[i] << std::endl;
        return;
      }
      break;
    }
  }
  firstIncorrectIndex = line.size();
}

char SyntaxLine::getComplimentaryChar(char c)
{
  switch (c)
  {
  case '(':
    return ')';
  case ')':
    return '(';
  case '{':
    return '}';
  case '}':
    return '{';
  case '[':
    return ']';
  case ']':
    return '[';
  case '<':
    return '>';
  case '>':
    return '<';
  }
  return 0;
}

void SyntaxLine::calculateCompletionString()
{
  std::stack<char> syntaxStack = std::stack<char>();
  for (int i = 0; i < line.size(); ++i)
  {
    switch (line[i])
    {
    case '(':
    case '{':
    case '[':
    case '<':
      syntaxStack.push(line[i]);
      break;
    case ')':
    case '}':
    case ']':
    case '>':
      syntaxStack.pop();
    }
  }
  while (!syntaxStack.empty())
  {
    completionString.push_back(getComplimentaryChar(syntaxStack.top()));
    syntaxStack.pop();
  }
}
