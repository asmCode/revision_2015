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
	static BehavioursManager* GetInstance();

	void RegisterBehaviour(const std::string& name, IBehaviourFactory* factory);
	Behaviour* CreateBehaviour(const std::string& name, GameObject *gameObject);
	void UpdateBehaviours();
	void AwakeBehaviours();

private:
	typedef std::map<std::string, IBehaviourFactory*> BehavioursFactoriesMap;
	typedef std::vector<Behaviour*> BehavioursVector;

	static BehavioursManager* m_instance;

	BehavioursFactoriesMap m_behavioursFactories;
	BehavioursVector m_behaviours;

	BehavioursManager();
	~BehavioursManager();
};
