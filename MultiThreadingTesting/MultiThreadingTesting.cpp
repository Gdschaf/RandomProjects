#include "AsyncPrimeNumber.h"
#include "JthreadPrimeNumber.h"

#include <iostream>
#include <conio.h>

// instead of using async, use a packaged_task and hand it to a thread pool

// try with mutex, semaphores, latch/barrier, promise/future, atomics, etc. just to try them all

int main()
{
  cout << "Starting Prime Test" << endl;
  PrimeNumber primeTest;
  auto primes = primeTest.findPrimesInRange(0, 1'000'000);

  cout << endl;
  cout << "Starting Async Test" << endl;
  AsyncPrimeNumber asyncTest(2);
  auto asyncPrimes = asyncTest.findPrimesInRange(0, 1'000'000);

  cout << endl;
  cout << "Starting jthread Test" << endl;
  JthreadPrimeNumber jthreadTest(2);
  auto jthreadPrimes = jthreadTest.findPrimesInRange(0, 1'000'000);

  cout << endl << endl;

  cout << "Number of primes found in each:" << endl;
  cout << "Control: " << primes.size() << endl;
  cout << "Async: " << asyncPrimes.size() << endl;
  cout << "jthread: " << jthreadPrimes.size() << endl;

  cout << endl << endl;

  cout << "The time it took to find those primes in each:" << endl;
  cout << "Control: " << primeTest.GetLatestDuration() << endl;
  cout << "Async: " << asyncTest.GetLatestDuration() << endl;
  cout << "jthread: " << jthreadTest.GetLatestDuration() << endl;
}