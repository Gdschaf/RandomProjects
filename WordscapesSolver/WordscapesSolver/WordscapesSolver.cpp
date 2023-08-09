// WordscapesSolver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstring>
#include <string>
#include <conio.h>
#include <vector>
#include <fstream>

bool checkWord(std::string dictionaryWord, std::vector<char> availableCharacters)
{
  if (dictionaryWord.size() > availableCharacters.size() || dictionaryWord.size() < 3)
    return false;
  for (int i = 0; i < dictionaryWord.size(); ++i)
  {
    char t = dictionaryWord[i];
    std::vector<char>::iterator foundIt = std::find(availableCharacters.begin(), availableCharacters.end(), t);
    bool found = foundIt != availableCharacters.end();
    if (!found)
      return false;
    else
    {
      availableCharacters.erase(foundIt);
    }
  }
  return true;
}

int main(int argc, char* argv[])
{
  std::string input = "";
  do
  {
    std::cout << "Please enter available letters seperated by a space." << std::endl;
    getline(std::cin, input);
  } while (input.size() == 0);

  std::vector<char> availableCharacters = std::vector<char>();
  for (int i = 0; i < input.size(); ++i)
  {
    if (input[i] != ' ')
    {
      std::cout << input[i] << std::endl;
      availableCharacters.push_back(input[i]);
    }
  }

  std::ifstream wordsFile("words_alpha.txt");
  if (wordsFile.is_open())
  {
    std::string wordLine;
    while (getline(wordsFile, wordLine))
    {
      if (checkWord(wordLine, availableCharacters))
        std::cout << wordLine << std::endl;
    }
    std::cout << std::endl << std::endl << "Done....." << std::endl;
    wordsFile.close();
  }
  else
  {
    std::cout << "Couldn't find words file..." << std::endl;
  }

  _getch();
}
