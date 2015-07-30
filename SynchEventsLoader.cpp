#include "SynchEventsLoader.h"
#include <XML/XMLLoader.h>
#include <XML/XMLNode.h>

#include "SynchManager.h"
#include "SynchEvent.h"

bool SynchEventsLoader::LoadFromFile(const std::string& path, SynchManager* synchManager)
{
	XMLNode* root = XMLLoader::LoadFromFile(path);
	if (root == NULL)
		return false;

	XMLNode* eventNode = NULL;
	SynchEvent* synchEvent = NULL;
	std::string id;
	float time;

	for (uint32_t i = 0; i < root->GetChildrenCount(); i++)
	{
		eventNode = root->GetChild(i);

		id = eventNode->GetAttribAsString("name");
		time = eventNode->GetAttribAsFloat("time");

		synchEvent = new SynchEvent(id, time);

		synchManager->Addevent(synchEvent);
	}

	return true;
}

bool SynchEventsLoader::Generate(SynchManager* synchManager)
{
	//static const float FirstBlinkBeat = 
	static const float RollBeatFirst = 33.0f;
	static const float RollBeatLast = 53.55f;
	static const float RollBeatCount = 15.0f; // w kazdym z nich sa 4 beaty

	static const float RollBeatLength = RollBeatLast - RollBeatFirst;
	static const float RollBeatSingle = RollBeatLength / (RollBeatCount - 0.0f);

	float time = RollBeatFirst;
	for (uint32_t i = 0; i < (uint32_t)RollBeatCount; i++)
	{
		synchManager->Addevent(new SynchEvent("beat1", time));
		time += RollBeatSingle;
	}

	return true;
}
