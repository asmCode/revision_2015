#pragma once

#include "../../CommandBase.h"

class MainCamera;

namespace MainCameraCommands
{
	class MainCameraCommandBase : public CommandBase
	{
	public:
		MainCameraCommandBase(MainCamera* mainCamera) :
			m_subject(mainCamera) {}

		virtual ~MainCameraCommandBase() {}

	protected:
		MainCamera* m_subject;
	};
}
