#pragma once

#include <string>

class SynchManager;

class SynchEventsLoader
{
public:
	static bool LoadFromFile(const std::string& path, SynchManager* synchManager);
};
