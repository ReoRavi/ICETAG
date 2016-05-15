#pragma once

// Ű�� �����ִ°�
#define INPUT(_key) GetAsyncKeyState(_key)
// Ű�� ���ȴ°�
#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000 ? 1 : 0))
// Key�� ������ �ʾҴ°�
#define KEYUP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000 ? 0 : 1))

//=========================================================================
// �������� ��ġ - ���� ���α׷����� ���콺 �������� ��ġ�� ��������Ʈ ���� ��츦 üũ�Ѵ�. 
#define LBUTTON_CLICK_SPRITE(pSprite) \
	InputMgr->m_ptLOldMouse.x - (InputMgr->m_ptLOldMouse.x - InputMgr->pt.x) > pSprite->GetPosition().x - pSprite->GetSize().x / 2 && \
	InputMgr->m_ptLOldMouse.x - (InputMgr->m_ptLOldMouse.x - InputMgr->pt.x) < pSprite->GetPosition().x + pSprite->GetSize().x / 2 && \
	InputMgr->m_ptLOldMouse.y - (InputMgr->m_ptLOldMouse.y - InputMgr->pt.y) > pSprite->GetPosition().y - pSprite->GetSize().y / 2 && \
	InputMgr->m_ptLOldMouse.y - (InputMgr->m_ptLOldMouse.y - InputMgr->pt.y) < pSprite->GetPosition().y + pSprite->GetSize().y / 2 && \
	InputMgr->m_bIsPushLButton

#define LBUTTON_UNCLICK_SPRITE(pSprite) \
	!(InputMgr->m_ptLOldMouse.x > pSprite->GetPosition().x - pSprite->GetSize().x / 2 && \
	InputMgr->m_ptLOldMouse.x < pSprite->GetPosition().x + pSprite->GetSize().x / 2 && \
	InputMgr->m_ptLOldMouse.y > pSprite->GetPosition().y - pSprite->GetSize().y / 2 && \
	InputMgr->m_ptLOldMouse.y < pSprite->GetPosition().y + pSprite->GetSize().y / 2) && \
	InputMgr->m_bIsPushLButton


#define RBUTTON_CLICK_SPRITE(pSprite) \
	InputMgr->m_ptLOldMouse.x > pSprite->GetPosition().x - pSprite->GetSize().x / 2 && \
	InputMgr->m_ptLOldMouse.x < pSprite->GetPosition().x + pSprite->GetSize().x / 2 && \
	InputMgr->m_ptLOldMouse.y > pSprite->GetPosition().y - pSprite->GetSize().y / 2 && \
	InputMgr->m_ptLOldMouse.y < pSprite->GetPosition().y + pSprite->GetSize().y / 2 && \
	InputMgr->m_bIsPushRButton

#define RBUTTON_UNCLICK_SPRITE(pSprite) \
	!(InputMgr->m_ptLOldMouse.x > pSprite->GetPosition().x - pSprite->GetSize().x / 2 && \
	InputMgr->m_ptLOldMouse.x < pSprite->GetPosition().x + pSprite->GetSize().x / 2 && \
	InputMgr->m_ptLOldMouse.y > pSprite->GetPosition().y - pSprite->GetSize().y / 2 && \
	InputMgr->m_ptLOldMouse.y < pSprite->GetPosition().y + pSprite->GetSize().y / 2) && \
	InputMgr->m_bIsPushRButton

//=========================================================================
// CInputManager : Ű����, ���콺 Ŭ�� ���� ó���ϴ� �Ŵ���
class CInputManager :
	public ISingleton <CInputManager>
{
public: // public ����
	POINT		m_ptLOldMouse;			// ���� Ŭ�� �� �� ���콺 ��ġ
	POINT		m_ptROldMouse;			// ������ Ŭ�� �� �� ���콺 ��ġ
	POINT		m_ptCurMouse;				// ���� ���콺 ��ġ
	bool			m_bIsPushLButton;		// ���� ��ư Ŭ�� üũ
	bool			m_bIsPushRButton;		// ������ ��ư Ŭ�� üũ
	float			m_LButtonInputDelay;
	
	POINT		pt;

public: // public �Լ�
	CInputManager(VOID);
	~CInputManager(VOID);

	// ����
	VOID Process(VOID);
};

#define InputMgr CInputManager::GetInstance()