#pragma once

class SynchEvent;

class SequenceBase
{
public:
	SequenceBase() {}
	virtual ~SequenceBase() {}

	virtual void Initialize() {}
	virtual void Prepare() {}
	virtual void Clean() {}
	virtual void Update() {}
	virtual void NotifySynchEvent(SynchEvent* synchEvent) {}
};
