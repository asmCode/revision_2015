#pragma once

template <typename T>
class CommandBase
{
public:
	CommandBase();
	virtual ~CommandBase();

	virtual void SetSubject(T* subject)
	{
		m_subject = subject;
	}

	virtual void Enter() {};
	virtual bool Update() {};
	virtual void Leave() {};

protected:
	T* m_subject;
};
