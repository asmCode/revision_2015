#include "Input.h"
#include <Windows.h>

bool Input::m_pressed[KeyCode::Count];
bool Input::m_justPressed[KeyCode::Count];
bool Input::m_justReleased[KeyCode::Count];
int Input::m_keyMap[KeyCode::Count];

bool Input::m_constructorTrigger = Input::Constructor();

bool Input::Constructor()
{
	Input::m_keyMap[KeyCode_Left] = VK_LEFT;
	Input::m_keyMap[KeyCode_Right] = VK_RIGHT;
	Input::m_keyMap[KeyCode_Up] = VK_UP;
	Input::m_keyMap[KeyCode_Down] = VK_DOWN;

	Input::m_keyMap[KeyCode_A] = 'A';
	Input::m_keyMap[KeyCode_B] = 'B';
	Input::m_keyMap[KeyCode_C] = 'C';
	Input::m_keyMap[KeyCode_D] = 'D';
	Input::m_keyMap[KeyCode_E] = 'E';
	Input::m_keyMap[KeyCode_F] = 'F';
	Input::m_keyMap[KeyCode_G] = 'G';
	Input::m_keyMap[KeyCode_H] = 'H';
	Input::m_keyMap[KeyCode_I] = 'I';
	Input::m_keyMap[KeyCode_J] = 'J';
	Input::m_keyMap[KeyCode_K] = 'K';
	Input::m_keyMap[KeyCode_L] = 'L';
	Input::m_keyMap[KeyCode_M] = 'M';
	Input::m_keyMap[KeyCode_N] = 'N';
	Input::m_keyMap[KeyCode_O] = 'O';
	Input::m_keyMap[KeyCode_P] = 'P';
	Input::m_keyMap[KeyCode_Q] = 'Q';
	Input::m_keyMap[KeyCode_R] = 'R';
	Input::m_keyMap[KeyCode_S] = 'S';
	Input::m_keyMap[KeyCode_T] = 'T';
	Input::m_keyMap[KeyCode_U] = 'U';
	Input::m_keyMap[KeyCode_V] = 'V';
	Input::m_keyMap[KeyCode_W] = 'W';
	Input::m_keyMap[KeyCode_X] = 'X';
	Input::m_keyMap[KeyCode_Y] = 'Y';
	Input::m_keyMap[KeyCode_Z] = 'Z';

	Input::m_keyMap[KeyCode_0] = '0';
	Input::m_keyMap[KeyCode_1] = '1';
	Input::m_keyMap[KeyCode_2] = '2';
	Input::m_keyMap[KeyCode_3] = '3';
	Input::m_keyMap[KeyCode_4] = '4';
	Input::m_keyMap[KeyCode_5] = '5';
	Input::m_keyMap[KeyCode_6] = '6';
	Input::m_keyMap[KeyCode_7] = '7';
	Input::m_keyMap[KeyCode_8] = '8';
	Input::m_keyMap[KeyCode_9] = '9';

	Input::m_keyMap[KeyCode_NumPad0] = VK_NUMPAD0;
	Input::m_keyMap[KeyCode_NumPad1] = VK_NUMPAD1;
	Input::m_keyMap[KeyCode_NumPad2] = VK_NUMPAD2;
	Input::m_keyMap[KeyCode_NumPad3] = VK_NUMPAD3;
	Input::m_keyMap[KeyCode_NumPad4] = VK_NUMPAD4;
	Input::m_keyMap[KeyCode_NumPad5] = VK_NUMPAD5;
	Input::m_keyMap[KeyCode_NumPad6] = VK_NUMPAD6;
	Input::m_keyMap[KeyCode_NumPad7] = VK_NUMPAD7;
	Input::m_keyMap[KeyCode_NumPad8] = VK_NUMPAD8;
	Input::m_keyMap[KeyCode_NumPad9] = VK_NUMPAD9;

	Input::m_keyMap[KeyCode_Space] = VK_SPACE;
	Input::m_keyMap[KeyCode_Escape] = VK_ESCAPE;
	Input::m_keyMap[KeyCode_LShift] = VK_LSHIFT;
	Input::m_keyMap[KeyCode_LCtrl] = VK_LCONTROL;

	Input::m_keyMap[KeyCode_Mouse0] = VK_LBUTTON;
	Input::m_keyMap[KeyCode_Mouse1] = VK_MBUTTON;
	Input::m_keyMap[KeyCode_Mouse2] = VK_RBUTTON;

	return true;
}

void Input::UpdateState()
{
	short keyState;
	short pressedFlag = (short)0x8000;

	for (unsigned char i = 0; i < static_cast<unsigned char>(KeyCode::Count); i++)
	{
		keyState = GetAsyncKeyState(m_keyMap[i]);

		if ((keyState & pressedFlag) != 0) // klawisz jest nacisniety
		{
			m_justPressed[i] = !m_pressed[i];
			
			m_pressed[i] = true;
		}
		else // klawisz nie jest nacisniety
		{			
			m_justReleased[i] = m_pressed[i];

			// fix: jesli w jednym wywolaniu metody nacisnieto przycisk a w kolejnym
			// wywolaniu puszczono, to m_justPressed[i] pozostaloby true
			m_justPressed[i] = false;

			m_pressed[i] = false;
		}
	}
}

bool Input::GetKey(KeyCode keyCode)
{
	return m_pressed[keyCode];
}

bool Input::GetKeyDown(KeyCode keyCode)
{
	return m_justPressed[keyCode];
}

bool Input::GetKeyUp(KeyCode keyCode)
{
	return m_justReleased[keyCode];
}

sm::Point<int> Input::GetMousePosition()
{
	POINT mousePosition;
	GetCursorPos(&mousePosition);

	return sm::Point<int>((int)mousePosition.x, (int)mousePosition.y);
}
