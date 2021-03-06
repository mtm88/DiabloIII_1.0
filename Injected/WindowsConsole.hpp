#pragma once

inline auto CreateConsole()
{
	AllocConsole();
	SetConsoleTitle("Diablo III");
	FILE* stream;
	freopen_s(&stream, "CONOUT$", "w", stdout);
}

inline auto CloseConsole()
{
	auto conHandle = GetConsoleWindow();
	FreeConsole();
	PostMessage(conHandle, WM_CLOSE, 0, 0);
}