#pragma once

#include "PrimeNumber.h"

// jthread is C++20
class JthreadPrimeNumber : public PrimeNumber
{
public:
  JthreadPrimeNumber(unsigned int numberOfThreads);
  vector<int> findPrimesInRange(int from, int to) override;
private:
  unsigned int threadCount;
};
