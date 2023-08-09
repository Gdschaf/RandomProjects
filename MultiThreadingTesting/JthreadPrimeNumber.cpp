#include "JthreadPrimeNumber.h"

#include <future>
#include <functional>

#include <iostream>

JthreadPrimeNumber::JthreadPrimeNumber(unsigned int numberOfThreads) : threadCount(numberOfThreads) { }

std::vector<int> JthreadPrimeNumber::findPrimesInRange(int from, int to)
{

  startTimer();

  cout << "Jthread - creating packaged tasks, creating future list, and moving task to jthread" << endl;
  vector<future<vector<int>>> futureList = vector<future<vector<int>>>();
  int startValue = from;
  int span = (to - from) / threadCount;
  for (int i = 0; i < threadCount; ++i)
  {
    cout << "current thread cout: " << i << endl;
    packaged_task<vector<int>()> packagedTask(packaged_task<vector<int>()>(bind(&PrimeNumber::findPrimes, this, startValue, min(startValue + span, to))));
    futureList.push_back(packagedTask.get_future());
    jthread(move(packagedTask)).detach();
    startValue += (span + 1);
  }

  cout << "Jthread - getting results from future" << endl;
  vector<vector<int>> listOfResults = vector<vector<int>>();
  for (int i = 0; i < threadCount; ++i)
  {
    listOfResults.push_back(futureList[i].get());
  }

  stopTimer();

  cout << "Jthread - merging results into primes list" << endl;
  vector<int> returnPrimes = listOfResults[0];
  for (int i = 1; i < threadCount; ++i)
  {
    returnPrimes.insert(returnPrimes.end(), listOfResults[i].begin(), listOfResults[i].end());
  }

  return returnPrimes;
}
