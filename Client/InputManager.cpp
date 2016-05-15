#include "stdafx.h"
#include "InputManager.h"
#include "WindowManager.h"

/*
* INPUT �Լ� ��ȯ�� �����
*
* GetKeyState(_key) �Ǵ� GetAsyncKeyState(_key) �ڿ� &value �� �ϸ� ��.
* 0 (0x0000)	: ������ ���� ���� ���� ȣ�� �������� �ȴ��� ����
* 0x8000		: ������ ���� ���� ���� ȣ�� �������� ���� ����
* 0x8001		: ������ ���� ���� �ְ� ȣ�� �������� ���� ����
* 1 (0x0001)	: ������ ���� ���� �ְ� ȣ�� �������� �ȴ��� ����
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
// Process : ����
VOID CInputManager::Process(VOID)
{
	RECT rt;

	// �������� ũ�⸦ ���Ѵ�.
	GetWindowRect(WinMgr->m_hWnd, &rt);

	pt.x = rt.left;
	pt.y = rt.top;

	// Ŀ���� ��ġ�� ���Ѵ�.
	GetCursorPos(&m_ptCurMouse);

	// â��� ��ǥ ����
	if (!WinMgr->m_bIsWindowMode)
	{
		pt = m_ptCurMouse;
		ScreenToClient(WinMgr->m_hWnd, &pt);
	}

	// ���� Ŭ��
	if (INPUT(VK_LBUTTON) & 1)
	{
		m_ptLOldMouse = m_ptCurMouse;
		m_bIsPushLButton = true;
	}
	else
	{
		m_bIsPushLButton = false;
	}

	// ������ Ŭ��
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