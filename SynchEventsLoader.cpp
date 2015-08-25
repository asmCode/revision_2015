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
	synchManager->Addevent(new SynchEvent("prepare_for_beginning", 0.0f));
	//SetBunchEvents(synchManager, "blink1", 11.34f, 32.0, 30);

	synchManager->Addevent(new SynchEvent("spin_fast", 31.489f));
	synchManager->Addevent(new SynchEvent("spin_fast_end", 33.0f));

	SetBunchEvents(synchManager, "beat1", 33.0f, 53.55f, 15);
	/*SetBunchEvents(synchManager, "open_mech1", 54.88f, 65.8f, 8);
	float shift = -0.1f;
	SetBunchEvents(synchManager, "pull_put_long", 60 + 5.89f + shift, 60 + 16.85f + shift, 32);
	synchManager->Addevent(new SynchEvent("prepare_for_magnet", 60 + 16.0f));
	synchManager->Addevent(new SynchEvent("prepare_for_explosions", 60 + 39.79f - 1.379f));
	SetBunchEvents(synchManager, "explode", 60 + 39.79f, 120 + 1.86f, 16);
	synchManager->Addevent(new SynchEvent("endless_flight", 120 + 3.2f));*/

	return true;
}

void SynchEventsLoader::SetBunchEvents(
	SynchManager* synchManager,
	const std::string& eventName,
	float timeStart,
	float timeEnd,
	int count)
{
	float length = timeEnd - timeStart;
	float beatLength = length / (float)count;

	float time = timeStart;
	for (int i = 0; i < count; i++)
	{
		synchManager->Addevent(new SynchEvent(eventName, time));
		time += beatLength;
	}
}
