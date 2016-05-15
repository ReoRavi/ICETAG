#include "stdafx.h"
#include "Scene.h"
#include "WindowManager.h"


CScene::CScene(VOID)
{
	// empty...
}

CScene::~CScene(VOID)
{
	// empty...
}

//==================================
// PreRender : �׸��� ����
VOID CScene::PreRender(VOID)
{
	WinMgr->m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	// Scene�� �����մϴ�.
	WinMgr->m_pd3dDevice->BeginScene();
}

//==================================
// PostRender : �׸��� ��
VOID CScene::PostRender(VOID)
{
	// Scene�� �����մϴ�.
	WinMgr->m_pd3dDevice->EndScene();
	WinMgr->m_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}