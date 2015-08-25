#pragma once

class CommandBase
{
public:
	CommandBase() {};
	virtual ~CommandBase() {};

	virtual void Enter() {};
	virtual bool Update() { return true; };
	virtual void Leave() {};
};
