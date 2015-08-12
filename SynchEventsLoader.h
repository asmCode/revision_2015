#pragma once

#include <string>

class SynchManager;

class SynchEventsLoader
{
public:
	static bool LoadFromFile(const std::string& path, SynchManager* synchManager);
	static bool Generate(SynchManager* synchManager);

	static void SetBunchEvents(
		SynchManager* synchManager,
		const std::string& eventName,
		float timeStart,
		float timeEnd,
		int count);
};
