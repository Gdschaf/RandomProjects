#include "AsyncPrimeNumber.h"

#include <future>
#include <functional>

#include <iostream>

AsyncPrimeNumber::AsyncPrimeNumber(unsigned int numberOfThreads) : threadCount(numberOfThreads) { }

std::vector<int> AsyncPrimeNumber::findPrimesInRange(int from, int to)
{
  cout << "Async - start timer" << endl;
  startTimer();
  
  cout << "Async - creating futures" << endl;
  vector<future<vector<int>>> futureList = vector<future<vector<int>>>();
  int startValue = from;
  int span = (to - from) / threadCount;
  for (int i = 0; i < threadCount; ++i)
  {
    futureList.push_back(async(bind(&PrimeNumber::findPrimes, this, startValue, min(startValue + span, to))));
    startValue += (span + 1);
  }

  cout << "Async - getting results and creating list of results" << endl;
  vector<vector<int>> listOfResults = vector<vector<int>>();
  for (int i = 0; i < threadCount; ++i)
  {
    listOfResults.push_back(futureList[i].get());
  }

  cout << "Async - stop timer" << endl;
  stopTimer();

  cout << "Async - merging results into list of primes" << endl;
  vector<int> returnPrimes = listOfResults[0];
  for (int i = 1; i < threadCount; ++i)
  {
    returnPrimes.insert(returnPrimes.end(), listOfResults[i].begin(), listOfResults[i].end());
  }

  return returnPrimes;
}
