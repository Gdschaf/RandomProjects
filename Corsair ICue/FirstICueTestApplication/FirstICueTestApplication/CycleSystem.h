#pragma once

#include <list>

class CycleElement
{
public:
	virtual void Update(float deltaTime) = 0;
	virtual void Initialize() { }
	virtual ~CycleElement() { }
};

class CycleSystem
{
public:
	void AddElement(CycleElement * element);
	void Initialize();
	void StartCycle();
	void InterruptCycle();
	~CycleSystem();
protected:
	std::list<CycleElement *> cycleElements;
private:
	double targetMilisecondsPerFrame();
	double currentTimeInMilliseconds();

	const unsigned int targetFPS = 60;
	bool cycling = false;
};