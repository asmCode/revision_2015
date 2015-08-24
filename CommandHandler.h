#pragma once

#include "CommandBase.h"
#include <string>
#include <queue>
#include <vector>

template <typename T>
class CommandHandler
{
public:
	CommandHandler() :
		m_currentCommand(nullptr)
	{ }

	virtual ~CommandHandler() {}

	void ProcessCommands()
	{
		if (m_commandQueue == nullptr && m_commandQueue.size() > 0)
		{
			m_currentCommand = m_commandQueue.front();
			m_currentCommand->Enter();
			m_commandQueue.pop();
		}

		if (m_currentCommand != nullptr)
		{
			if (m_currentCommand->Update())
			{
				m_currentCommand->Leave();
				m_currentCommand = nullptr;
			}
		}

		std::vector<CommandBase<T>*> commands;
		commands.insert(commands.begin(), m_commandParaller.begin(), m_commandParaller.end());
		m_commandParaller.clear();
		for (size_t i = 0; i < commands.size(); i++)
		{
			CommandBase<T>* command = commands[i];
			if (!command->Update())
				m_commandsParaller.push_back(command);
			else
				command->Leave();
		}
	}

	void QueueCommand(CommandBase<T>* command)
	{
		m_commandQueue.push(command);
		command->SetSubject(this);
	}

	void SetCommandParaller(CommandBase<T>* command)
	{
		m_commandParaller.push_back(command);
		command->SetSubject(this);
		command->Enter();
	}

private:
	std::queue<CommandBase*> m_commandQueue;
	std::vector<CommandBase*> m_commandParaller;
	CommandBase* m_currentCommand;
};
