#include "stdafx.h"
#include "System.h"
// Managers
#include "WindowManager.h"
#include "SceneManager.h"
#include "TextureManager.h"
#include "InputManager.h"
#include "DataManager.h"
#include "NetWork.h"
#include "MakePacket.h"

#define SERVER_ON_OFF false


CSystem::CSystem(VOID)
{
	// empty...
}

CSystem::~CSystem(VOID)
{
	// empty...
}

BOOL CSystem::Init(VOID)
{
	WinMgr->Init();
	DataManager->Initialize();
	SceneMgr->ChangeScene(SceneInfo_Title); 

	return TRUE;
}

VOID CSystem::MessageLoop(VOID)
{
	MSG msg;

	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT && DataManager->bIsGameRun)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Process();
			Render();
		}
	}
}

VOID CSystem::Process(VOID)
{
	Network->Loop();
	InputMgr->Process();
	SceneMgr->m_pScene->Process();
}

VOID CSystem::Render(VOID)
{
	SceneMgr->m_pScene->PreRender();
	SceneMgr->m_pScene->Render();
	SceneMgr->m_pScene->PostRender();

	//if (DataManager->bIsQuit)
	//{
	//	Release();
	//}
}

VOID CSystem::Release(VOID)
{
	TextureMgr->Release();
	SceneMgr->Release();
	WinMgr->Release();
	Network->Release();
	FreeConsole();
}