#include "stdafx.h"
#include "S_Title.h"

S_Title::S_Title()
{
}


S_Title::~S_Title()
{
}

//=================================================================
// Init : �ʱ�ȭ
VOID S_Title::Init(VOID)
{
	// ���
	m_BackGround = new CSprite();
	m_BackGround->CreateSprite("Resource/Title/BackGround.png");
	m_BackGround->SetPosition(512, 383);

	// �ΰ�
	m_Logo = new CSprite();
	m_Logo->CreateSprite("Resource/Title/Logo.png");
	m_Logo->SetPosition(150, 100);

	// ���� ���� ��ư
	m_GameStartButton = new CSprite();
	m_GameStartButton->CreateSprite("Resource/Title/GameStartButton.png");
	m_GameStartButton->SetPosition(850, 450);

	// ���� ��� ��ư
	m_HowtoPlayButton = new CSprite();
	m_HowtoPlayButton->CreateSprite("Resource/Title/HowtoPlayButton.png");
	m_HowtoPlayButton->SetPosition(850, 575);

	// ������ ��ư
	m_ExitButton = new CSprite();
	m_ExitButton->CreateSprite("Resource/Title/ExitButton.png");
	m_ExitButton->SetPosition(850, 700);
}

//=================================================================
// Process : ����
VOID S_Title::Process(VOID)
{
	// ������ ��ư�� ���ȴٸ�
	if (LBUTTON_CLICK_SPRITE(m_ExitButton))
	{
		this->Release();
		PostQuitMessage(0);
	}

	if (SceneMgr->CurrentScene == Scene_Info::SceneInfo_Title)
	{
		// ���� ���� ��ư
		if (LBUTTON_CLICK_SPRITE(m_GameStartButton))
		{
			SceneMgr->ChangeScene(Scene_Info::SceneInfo_ConnectToRoom);
		}

		// ���� ��� ��ư
		if (LBUTTON_CLICK_SPRITE(m_HowtoPlayButton))
		{
			SceneMgr->ChangeScene(Scene_Info::SceneInfo_HowToPlay);
		}
	}
}

//=================================================================
// Render : �̹��� ���
VOID S_Title::Render(VOID)
{
	// ���
	m_BackGround->Render();
	// �ΰ�
	m_Logo->Render();
	// ���� ���� ��ư
	m_GameStartButton->Render();
	// ���� ��� ��ư
	m_HowtoPlayButton->Render();
	// ������ ��ư
	m_ExitButton->Render();
}

//=================================================================
// Release : �޸� ����
VOID S_Title::Release(VOID)
{
	m_BackGround->Release();
	m_Logo->Release();
	m_GameStartButton->Release();
	m_HowtoPlayButton->Release();
	m_ExitButton->Release();
}