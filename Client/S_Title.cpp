#include "stdafx.h"
#include "S_Title.h"

S_Title::S_Title()
{
}


S_Title::~S_Title()
{
}

//=================================================================
// Init : 초기화
VOID S_Title::Init(VOID)
{
	// 배경
	m_BackGround = new CSprite();
	m_BackGround->CreateSprite("Resource/Title/BackGround.png");
	m_BackGround->SetPosition(512, 383);

	// 로고
	m_Logo = new CSprite();
	m_Logo->CreateSprite("Resource/Title/Logo.png");
	m_Logo->SetPosition(150, 100);

	// 게임 시작 버튼
	m_GameStartButton = new CSprite();
	m_GameStartButton->CreateSprite("Resource/Title/GameStartButton.png");
	m_GameStartButton->SetPosition(850, 450);

	// 게임 방법 버튼
	m_HowtoPlayButton = new CSprite();
	m_HowtoPlayButton->CreateSprite("Resource/Title/HowtoPlayButton.png");
	m_HowtoPlayButton->SetPosition(850, 575);

	// 나가기 버튼
	m_ExitButton = new CSprite();
	m_ExitButton->CreateSprite("Resource/Title/ExitButton.png");
	m_ExitButton->SetPosition(850, 700);
}

//=================================================================
// Process : 루프
VOID S_Title::Process(VOID)
{
	// 나가기 버튼이 눌렸다면
	if (LBUTTON_CLICK_SPRITE(m_ExitButton))
	{
		this->Release();
		PostQuitMessage(0);
	}

	if (SceneMgr->CurrentScene == Scene_Info::SceneInfo_Title)
	{
		// 게임 시작 버튼
		if (LBUTTON_CLICK_SPRITE(m_GameStartButton))
		{
			SceneMgr->ChangeScene(Scene_Info::SceneInfo_ConnectToRoom);
		}

		// 게임 방법 버튼
		if (LBUTTON_CLICK_SPRITE(m_HowtoPlayButton))
		{
			SceneMgr->ChangeScene(Scene_Info::SceneInfo_HowToPlay);
		}
	}
}

//=================================================================
// Render : 이미지 출력
VOID S_Title::Render(VOID)
{
	// 배경
	m_BackGround->Render();
	// 로고
	m_Logo->Render();
	// 게임 시작 버튼
	m_GameStartButton->Render();
	// 게임 방법 버튼
	m_HowtoPlayButton->Render();
	// 나가기 버튼
	m_ExitButton->Render();
}

//=================================================================
// Release : 메모리 해제
VOID S_Title::Release(VOID)
{
	m_BackGround->Release();
	m_Logo->Release();
	m_GameStartButton->Release();
	m_HowtoPlayButton->Release();
	m_ExitButton->Release();
}