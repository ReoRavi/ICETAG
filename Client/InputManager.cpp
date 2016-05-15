#include "stdafx.h"
#include "InputManager.h"
#include "WindowManager.h"

/*
* INPUT 함수 반환값 사용방법
*
* GetKeyState(_key) 또는 GetAsyncKeyState(_key) 뒤에 &value 를 하면 됨.
* 0 (0x0000)	: 이전에 누른 적이 없고 호출 시점에서 안눌린 상태
* 0x8000		: 이전에 누른 적이 없고 호출 시점에서 눌린 상태
* 0x8001		: 이전에 누른 적이 있고 호출 시점에서 눌린 상태
* 1 (0x0001)	: 이전에 누른 적이 있고 호출 시점에서 안눌린 상태
*/

CInputManager::CInputManager(VOID)
{
	// empty...
}

CInputManager::~CInputManager(VOID)
{
	// empty...
}

//===============================
// Process : 루프
VOID CInputManager::Process(VOID)
{
	RECT rt;

	// 윈도우의 크기를 구한다.
	GetWindowRect(WinMgr->m_hWnd, &rt);

	pt.x = rt.left;
	pt.y = rt.top;

	// 커서의 위치를 구한다.
	GetCursorPos(&m_ptCurMouse);

	// 창모드 촤표 수정
	if (!WinMgr->m_bIsWindowMode)
	{
		pt = m_ptCurMouse;
		ScreenToClient(WinMgr->m_hWnd, &pt);
	}

	// 왼쪽 클릭
	if (INPUT(VK_LBUTTON) & 1)
	{
		m_ptLOldMouse = m_ptCurMouse;
		m_bIsPushLButton = true;
	}
	else
	{
		m_bIsPushLButton = false;
	}

	// 오른쪽 클릭
	if (INPUT(VK_RBUTTON) & 1)
	{
		m_ptROldMouse = m_ptCurMouse;
		m_bIsPushRButton = true;
	}
	else
	{
		m_bIsPushRButton = false;
	}
}