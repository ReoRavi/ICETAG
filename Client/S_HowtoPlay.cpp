#include "stdafx.h"
#include "S_HowtoPlay.h"

S_HowtoPlay::S_HowtoPlay()
{
}


S_HowtoPlay::~S_HowtoPlay()
{
}

//=================================================================
// Init : 초기화
VOID S_HowtoPlay::Init(VOID)
{
	// 배경
	m_BackGround = new CSprite();
	m_BackGround->CreateSprite("Resource/HowtoPlay/HowtoPlay.png");
	m_BackGround->SetPosition(512, 383);

	// 뒤로가기 버튼
	m_BackButton = new CSprite();
	m_BackButton->CreateSprite("Resource/HowtoPlay/BackButton.png");
	m_BackButton->SetPosition(950, 700);
}

//=================================================================
// Process : 루프
VOID S_HowtoPlay::Process(VOID)
{
	// 버튼이 클릭되었다면
	if (LBUTTON_CLICK_SPRITE(m_BackButton))
	{
		// 메인메뉴로 돌아간다.
		SceneMgr->ChangeScene(Scene_Info::SceneInfo_Title);
	}
}

//=================================================================
// Render : 이미지 출력
VOID S_HowtoPlay::Render(VOID)
{
	// 배경
	m_BackGround->Render();
	// 돌아가기 버튼
	m_BackButton->Render();
}

//=================================================================
// Release : 메모리 해제
VOID S_HowtoPlay::Release(VOID)
{
	m_BackGround->Release();
	m_BackButton->Release();
}