#include "stdafx.h"
#include "S_HowtoPlay.h"

S_HowtoPlay::S_HowtoPlay()
{
}


S_HowtoPlay::~S_HowtoPlay()
{
}

//=================================================================
// Init : �ʱ�ȭ
VOID S_HowtoPlay::Init(VOID)
{
	// ���
	m_BackGround = new CSprite();
	m_BackGround->CreateSprite("Resource/HowtoPlay/HowtoPlay.png");
	m_BackGround->SetPosition(512, 383);

	// �ڷΰ��� ��ư
	m_BackButton = new CSprite();
	m_BackButton->CreateSprite("Resource/HowtoPlay/BackButton.png");
	m_BackButton->SetPosition(950, 700);
}

//=================================================================
// Process : ����
VOID S_HowtoPlay::Process(VOID)
{
	// ��ư�� Ŭ���Ǿ��ٸ�
	if (LBUTTON_CLICK_SPRITE(m_BackButton))
	{
		// ���θ޴��� ���ư���.
		SceneMgr->ChangeScene(Scene_Info::SceneInfo_Title);
	}
}

//=================================================================
// Render : �̹��� ���
VOID S_HowtoPlay::Render(VOID)
{
	// ���
	m_BackGround->Render();
	// ���ư��� ��ư
	m_BackButton->Render();
}

//=================================================================
// Release : �޸� ����
VOID S_HowtoPlay::Release(VOID)
{
	m_BackGround->Release();
	m_BackButton->Release();
}