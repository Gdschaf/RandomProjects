#pragma once

#include <unordered_map>
#include <list>
#include <chrono>

#include <iostream>

using namespace std;
using namespace chrono;

#define TIMER_ID_TYPE unsigned short
#define TIMER_ID_MAX USHRT_MAX

template <typename T, typename U>
class PerformanceTimer
{
public:

  class InvalidIdException : public exception
  {
  public:
    InvalidIdException(string message, TIMER_ID_TYPE id) : errorMessage(message), invalidId(id) { }
    string errorMessage;
    TIMER_ID_TYPE invalidId;
  };

  ~PerformanceTimer()
  {
    if (TimersRunning())
    {
      // idk do something else that isn't iostream related.
      // cout << "Not all timers finished running." << endl;
    }
  }

  U GetDuration(TIMER_ID_TYPE timerId = 0)
  {
    if (completedTimerDurations.size() == 0)
      throw InvalidIdException("No duration found with timerId", timerId);

    if (timerId == 0)
      timerId = getLatestDurationId();

    return getDuration(timerId);
  }

  U GetLatestDuration()
  {
    return GetDuration(0);
  }

  list<U> GetAllDurations()
  {
    list<U> returnDurations = list<U>();
    auto itEnd = completedTimerDurations.end();
    for (auto it = completedTimerDurations.begin(); it != itEnd; ++it)
    {
      returnDurations.push_back(it->second);
    }
    return returnDurations;
  }

  bool TimersRunning()
  {
    return !runningTimers.empty();
  }

protected:

  TIMER_ID_TYPE startTimer()
  {
    cout << "Performance Timer - startTimer()" << endl;
    runningTimers[++timerId] = T::now();
    return timerId;
  }

  void stopTimer(TIMER_ID_TYPE timerId = 0)
  {
    cout << "Performance Timer - endTimer()" << endl;
    if (timerId == 0)
      timerId = getEarliestTimerId();

    time_point<T> timePoint = getTimer(timerId);
    runningTimers.erase(timerId);

    completedTimerDurations[timerId] = duration_cast<U>(T::now() - timePoint);
  }

private:
  unordered_map<TIMER_ID_TYPE, time_point<T>> runningTimers = unordered_map<TIMER_ID_TYPE, time_point<T>>();
  unordered_map<TIMER_ID_TYPE, U> completedTimerDurations = unordered_map<TIMER_ID_TYPE, U>();
  TIMER_ID_TYPE timerId = 0;

  TIMER_ID_TYPE getEarliestTimerId()
  {
    TIMER_ID_TYPE smallestId = TIMER_ID_MAX;
    auto itEnd = runningTimers.end();
    for (auto it = runningTimers.begin(); it != itEnd; ++it)
    {
      smallestId = min(smallestId, it->first);
    }
    return smallestId;
  }

  TIMER_ID_TYPE getLatestDurationId()
  {
    TIMER_ID_TYPE latestId = 0;
    auto itEnd = completedTimerDurations.end();
    for (auto it = completedTimerDurations.begin(); it != itEnd; ++it)
    {
      latestId = max(latestId, it->first);
    }
    return latestId;
  }

  time_point<T> getTimer(TIMER_ID_TYPE id)
  {
    if (!runningTimers.contains(id))
      throw InvalidIdException("No running timer with ID found.", id);
    
    return runningTimers[id];
  }

  U getDuration(TIMER_ID_TYPE id)
  {
    if (!completedTimerDurations.contains(id))
      throw InvalidIdException("No duration with ID found.", id);

    return completedTimerDurations[id];
  }
};