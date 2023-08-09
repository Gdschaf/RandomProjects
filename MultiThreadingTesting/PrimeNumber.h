#pragma once

#include "PerformanceTimer.h"

class PrimeNumber : public PerformanceTimer<high_resolution_clock, milliseconds>
{
public:
  virtual vector<int> findPrimesInRange(int from, int to);
  vector<int> findPrimes(int from, int to);
protected:
  bool isPrime(int number);
};