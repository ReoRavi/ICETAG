// Engine.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Engine.h"
#include "System.h"
#include "DataManager.h"

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
#if _DEBUG
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
#endif
	CSystem system;

	// 초기화에 실패하면?
	if (!(system.Init()))
		system.Release();
	
	// 루프
	if (DataManager->bIsGameRun)
		system.MessageLoop();

	// 초기화
	system.Release();
}