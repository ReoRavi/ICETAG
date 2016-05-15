#include "stdafx.h"
#include "System.h"


CSystem::CSystem()
{
}


CSystem::~CSystem()
{
}

//=================================================================
// Initialize - �ʱ�ȭ
BOOL CSystem::Initialize(VOID)
{
	// ��Ʈ��ũ ��ü �ʱ�ȭ
	NetWork = new CNetWork;

	if (NetWork->Initialize())
	{
		return FALSE;
	}

	bIsLoop = TRUE;

	return TRUE;
}

//=================================================================
// Loop - ����
VOID CSystem::Loop(VOID)
{
	NetWork->Loop();
}

//=================================================================
// Release - �޸� ����
VOID CSystem::Release(VOID)
{
	NetWork->Release();
}