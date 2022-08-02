// dllmain.cpp : Определяет точку входа для приложения DLL.
#include <windows.h>
#include "il2cpp.h"
#include <iostream>
HRESULT initil2cpp(HMODULE hModule)
{
	auto PLH = il2cpp::FindClass("PLH");
	if (!PLH) goto out;
	std::cout << "PLH: " << PLH << std::endl;
	std::cout << "PLH->StaticFields(): " << PLH->StaticFields() << std::endl;
	
	out:
	FreeLibraryAndExitThread(hModule, 0);
}
BOOL APIENTRY DllMain(HMODULE hm, DWORD  r, LPVOID lpR)
{
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);
	switch (r)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hm);
		CloseHandle(
			CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(initil2cpp), hm, 0, nullptr)
		);
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
