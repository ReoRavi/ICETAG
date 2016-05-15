#include "stdafx.h"
#include "System.h"


CSystem::CSystem()
{
}


CSystem::~CSystem()
{
}

//=================================================================
// Initialize - 초기화
BOOL CSystem::Initialize(VOID)
{
	// 네트워크 객체 초기화
	NetWork = new CNetWork;

	if (NetWork->Initialize())
	{
		return FALSE;
	}

	bIsLoop = TRUE;

	return TRUE;
}

//=================================================================
// Loop - 루프
VOID CSystem::Loop(VOID)
{
	NetWork->Loop();
}

//=================================================================
// Release - 메모리 해제
VOID CSystem::Release(VOID)
{
	NetWork->Release();
}