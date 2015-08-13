#include "SystemUtils.h"
#include <Windows.h>

void SystemUtils::CopyToClipboard(const std::string& text)
{
	HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, text.size() + 1);
	memcpy(GlobalLock(hMem), text.c_str(), text.size() + 1);
	GlobalUnlock(hMem);
	OpenClipboard(0);
	EmptyClipboard();
	SetClipboardData(CF_TEXT, hMem);
	CloseClipboard();
}
