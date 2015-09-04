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
	synchManager->Addevent(new SynchEvent("show_group", 3.0f));
	synchManager->Addevent(new SynchEvent("hide_group", 6.5f));
	synchManager->Addevent(new SynchEvent("show_title", 8.5f));
	synchManager->Addevent(new SynchEvent("hide_title", 11.0f));
	SetBunchEvents(synchManager, "blink1", 11.34f, 32.0, 30);

	synchManager->Addevent(new SynchEvent("color_orange", 31.489f));
	synchManager->Addevent(new SynchEvent("spin_fast", 31.489f));
	synchManager->Addevent(new SynchEvent("spin_fast_end", 33.0f));
	synchManager->Addevent(new SynchEvent("flash", 33.0f));

	SetBunchEvents(synchManager, "beat1", 33.0f, 53.55f, 15);
	synchManager->Addevent(new SynchEvent("beat1_end", 53.5f));

	synchManager->Addevent(new SynchEvent("color_green", 54.88f));
	SetBunchEvents(synchManager, "open_mech1", 54.88f, 65.8f, 8);
	float shift = -0.1f;
	SetBunchEvents(synchManager, "pull_put_long", 60 + 5.89f + shift, 60 + 16.85f + shift, 32);
	synchManager->Addevent(new SynchEvent("color_blue", 60 + 16.85f));
	synchManager->Addevent(new SynchEvent("prepare_for_magnet", 60 + 16.85f));
	synchManager->Addevent(new SynchEvent("flash", 60 + 16.85f));

	synchManager->Addevent(new SynchEvent("flash", 60 + 22.34f));
	synchManager->Addevent(new SynchEvent("flash", 60 + 27.8f));
	synchManager->Addevent(new SynchEvent("flash", 60 + 33.3f));
	
	
	synchManager->Addevent(new SynchEvent("color_orange", 60 + 38.79f));
	synchManager->Addevent(new SynchEvent("prepare_for_explosions", 60 + 38.79f));
	synchManager->Addevent(new SynchEvent("flash", 60 + 38.79f));
	SetBunchEvents(synchManager, "explode", 60 + 39.79f, 120 + 1.86f, 16);
	
	synchManager->Addevent(new SynchEvent("break", 120 + 0.97f));
	synchManager->Addevent(new SynchEvent("open_gate", 120 + 3.443f));
	
	synchManager->Addevent(new SynchEvent("endless_flight", 120 + 4.829f));

	synchManager->Addevent(new SynchEvent("flash", 120 + 10.33f));
	synchManager->Addevent(new SynchEvent("color_blue", 120 + 10.33f));
	synchManager->Addevent(new SynchEvent("flash", 120 + 15.82f));
	synchManager->Addevent(new SynchEvent("color_green", 120 + 15.82f));
	synchManager->Addevent(new SynchEvent("flash", 120 + 26.79f));
	synchManager->Addevent(new SynchEvent("color_orange", 120 + 26.79f));

	synchManager->Addevent(new SynchEvent("end_flight", 120 + 36.0f));
	synchManager->Addevent(new SynchEvent("prepare_for_outro", 120 + 39.0f));
	

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
