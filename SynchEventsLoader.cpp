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
