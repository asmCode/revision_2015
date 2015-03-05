#pragma once

class BehavioursManager;

class FuturisEngine
{
public:
	FuturisEngine();
	~FuturisEngine();

	bool Initialize();

	BehavioursManager* GetBehavioursManager() const;

private:
	BehavioursManager* m_behavioursManager;
};
