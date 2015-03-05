#pragma once

#include <map>
#include <vector>
#include <string>

class GameObject;
class Behaviour;
class IBehaviourFactory;

class BehavioursManager
{
public:
	BehavioursManager();
	~BehavioursManager();

	void RegisterBehaviour(const std::string& name, IBehaviourFactory* factory);
	Behaviour* CreateBehaviour(const std::string& name, GameObject *gameObject);
	void UpdateBehaviours();

private:
	typedef std::map<std::string, IBehaviourFactory*> BehavioursFactoriesMap;
	typedef std::vector<Behaviour*> BehavioursVector;

	BehavioursFactoriesMap m_behavioursFactories;
	BehavioursVector m_behaviours;
};
