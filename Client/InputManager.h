#pragma once

// 키가 눌려있는가
#define INPUT(_key) GetAsyncKeyState(_key)
// 키가 눌렸는가
#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000 ? 1 : 0))
// Key가 눌리지 않았는가
#define KEYUP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000 ? 0 : 1))

//=========================================================================
// 윈도우의 위치 - 실제 프로그램에서 마우스 포인터의 위치가 스프라이트 안일 경우를 체크한다. 
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
// CInputManager : 키보드, 마우스 클릭 등을 처리하는 매니저
class CInputManager :
	public ISingleton <CInputManager>
{
public: // public 변수
	POINT		m_ptLOldMouse;			// 왼쪽 클릭 후 그 마우스 위치
	POINT		m_ptROldMouse;			// 오른쪽 클릭 후 그 마우스 위치
	POINT		m_ptCurMouse;				// 현재 마우스 위치
	bool			m_bIsPushLButton;		// 왼쪽 버튼 클릭 체크
	bool			m_bIsPushRButton;		// 오른쪽 버튼 클릭 체크
	float			m_LButtonInputDelay;
	
	POINT		pt;

public: // public 함수
	CInputManager(VOID);
	~CInputManager(VOID);

	// 루프
	VOID Process(VOID);
};

#define InputMgr CInputManager::GetInstance()