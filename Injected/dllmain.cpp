#pragma once
#ifndef WIN32
#define WIN32
#endif
#include <WinSock2.h>
#include <string>
#include <cstdio>

#include "WindowsConsole.hpp"
#include "Helpers.hpp"
#include "Storage.h"

#include "Game.h"

HINSTANCE instanceDLL = nullptr;
auto g_ObjectManager = 0x141DF3D30;

DWORD MainThread(LPVOID lpParm)
{
	CreateConsole();

	auto pldata = ((PlayerData*(__cdecl*)())0x0000000140472F10)();

	auto storage = (Storage*)*(int*)(g_ObjectManager + 0x7e8);

	while (!GetAsyncKeyState(VK_NUMPAD7)) {

		//printf("Local Player Address = %X\n", pldata);
		//printf("Local Player Life Percent = %f\n", (pldata->LifePercentage) * 100);
		//printf("Local Player Name = %s\n", pldata->HeroName);
		//printf("Local Player Level = %i\n", pldata->Level);

		Sleep(1000);
	}

	CloseConsole();
	FreeLibraryAndExitThread((HMODULE)instanceDLL, 0);
	return 0;

	//-----------------------------------  loop here before exit ----------------------------------
	//wait for the numpad 7 to be pressed...
	
}

// entry point of the DLL
bool APIENTRY DllMain(HINSTANCE instDLL, DWORD reason, LPVOID /* reserved */)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		instanceDLL = instDLL;
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&MainThread, 0, 0, 0);
	}	
	return true;
}