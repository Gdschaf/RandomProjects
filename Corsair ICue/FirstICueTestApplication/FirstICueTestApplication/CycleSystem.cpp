#include <CUESDK.h>

#include "CycleSystem.h"

#include <ctime>
#include <iostream>
#include <chrono>

void CycleSystem::AddElement(CycleElement * element) 
{
	cycleElements.push_back(element); 
}

void CycleSystem::Initialize()
{
	std::list<CycleElement *>::iterator it = cycleElements.begin();
	std::list<CycleElement *>::iterator itEnd = cycleElements.end();
	for (it; it != itEnd; ++it)
	{
		(*it)->Initialize();
	}
}

CycleSystem::~CycleSystem()
{
	//as long as whatever derives from CycleElement has a virtual deconstructor, I think this should work
	std::list<CycleElement *>::iterator it = cycleElements.begin();
	std::list<CycleElement *>::iterator itEnd = cycleElements.end();
	for (it; it != itEnd; ++it)
	{
		delete (*it);
	}
}

double CycleSystem::targetMilisecondsPerFrame()
{
	double secondsPerFrame = 1.0 / targetFPS;
	return secondsPerFrame * 1000; //convert to miliseconds;
}

double CycleSystem::currentTimeInMilliseconds()
{
	return (double)(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
}

void CycleSystem::StartCycle()
{
	cycling = true;
	double targetMiliseconds = targetMilisecondsPerFrame();
	double lastTime = currentTimeInMilliseconds();
	double lagTime = 0;
	while (cycling)
	{
		double currentTime = currentTimeInMilliseconds();
		double elapsedTime = currentTime - lastTime;
		lastTime = currentTime;
		lagTime += elapsedTime;

		//game loop goes here
		while (lagTime > targetMiliseconds)
		{
			std::list<CycleElement *>::iterator it = cycleElements.begin();
			std::list<CycleElement *>::iterator itEnd = cycleElements.end();
			for (it; it != itEnd; ++it)
			{
				//send it in as seconds elapsed instead of milliseconds elapsed
				(*it)->Update((float)(targetMiliseconds / 1000.0));
			}

			//after each frame, perform LED buffer flush
			CorsairSetLedsColorsFlushBufferAsync(nullptr, nullptr);

			lagTime -= targetMiliseconds;
		}
	}
}

void CycleSystem::InterruptCycle()
{
	cycling = false;
}