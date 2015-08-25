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
		if (m_currentCommand == nullptr && m_commandQueue.size() > 0)
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

		std::vector<CommandBase*> commands;
		commands.insert(commands.begin(), m_commandParaller.begin(), m_commandParaller.end());
		m_commandParaller.clear();
		for (size_t i = 0; i < commands.size(); i++)
		{
			CommandBase* command = commands[i];
			if (!command->Update())
				m_commandParaller.push_back(command);
			else
				command->Leave();
		}
	}

	void QueueCommand(CommandBase* command)
	{
		m_commandQueue.push(command);
	}

	void SetCommandParaller(CommandBase* command)
	{
		m_commandParaller.push_back(command);
		command->Enter();
	}

private:
	std::queue<CommandBase*> m_commandQueue;
	std::vector<CommandBase*> m_commandParaller;
	CommandBase* m_currentCommand;
};
