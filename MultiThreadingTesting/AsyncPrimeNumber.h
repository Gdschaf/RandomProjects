#pragma once

#include "PrimeNumber.h"

// async is C++11
class AsyncPrimeNumber : public PrimeNumber
{
public:
  AsyncPrimeNumber(unsigned int numberOfThreads);
  vector<int> findPrimesInRange(int from, int to) override;
private:
  unsigned int threadCount;
};