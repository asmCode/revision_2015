#pragma once

#include <vector>

class SynchEvent;

class SynchManagerObserver
{
public:
	virtual void SynchEventFired(SynchEvent* synchEvent) = 0;
};
