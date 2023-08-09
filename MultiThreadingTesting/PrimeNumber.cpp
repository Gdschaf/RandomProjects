#include "PrimeNumber.h"

#include <iostream>

bool PrimeNumber::isPrime(int number)
{
  bool isNumberPrime = true;

  if (number == 0 || number == 1)
    isNumberPrime = false;
  else
  {
    for (int i = 2; i < number; ++i)
    {
      if (number % i == 0)
      {
        isNumberPrime = false;
        break;
      }
    }
  }

  return isNumberPrime;
}

std::vector<int> PrimeNumber::findPrimesInRange(int from, int to)
{
  startTimer();
  auto returnPrimes = findPrimes(from, to);
  stopTimer();
  return returnPrimes;
}

vector<int> PrimeNumber::findPrimes(int from, int to)
{
  // obviously not thread safe
  // cout << "Prime Number - finding primes from: " << from << " to: " << to << endl;
  vector<int> returnPrimes;

  for (int i = from; i <= to; ++i)
  {
    if (isPrime(i))
      returnPrimes.push_back(i);
  }

  return returnPrimes;
}