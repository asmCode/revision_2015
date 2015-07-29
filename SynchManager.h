#pragma once

#include <vector>

class SynchEvent;
class SynchManagerObserver;

class SynchManager
{
public:
	static SynchManager* GetInstance();

	void Addevent(SynchEvent* synchEvent);
	void Update(float time);

	void RegisterObserver(SynchManagerObserver* observer);
	void SortEventsByTime();

protected:
	std::vector<SynchEvent*> m_events;
	std::vector<SynchManagerObserver*> m_observers;
	float m_time;

private:
	static SynchManager* m_instance;

	SynchManager();
	virtual ~SynchManager();

	SynchEvent* GetAndRemoveEvent();
	void NotifySynchEventFired(SynchEvent* synchEvent);
};
