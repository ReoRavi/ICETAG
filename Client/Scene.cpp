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
// PreRender : 그리기 시작
VOID CScene::PreRender(VOID)
{
	WinMgr->m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	// Scene을 시작합니다.
	WinMgr->m_pd3dDevice->BeginScene();
}

//==================================
// PostRender : 그리기 끝
VOID CScene::PostRender(VOID)
{
	// Scene을 종료합니다.
	WinMgr->m_pd3dDevice->EndScene();
	WinMgr->m_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}