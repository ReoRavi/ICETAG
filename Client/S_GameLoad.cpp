#include "stdafx.h"
#include "S_GameLoad.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "DataManager.h"
#include "Sprite.h"
#include "Lable.h"

S_GameLoad::S_GameLoad()
{
}


S_GameLoad::~S_GameLoad()
{

}

void S_GameLoad::Init(void)
{
	m_BackGround = new CSprite();
	m_BackGround->CreateSprite("Resource/Load/Load_BackGround.png");
	m_BackGround->SetPosition(640, 384);

	m_LoadMessage = new CLable();
	m_LoadMessage->CreateText("돋음", 30);
	m_LoadMessage->SetPosition(100, 100);
}

void S_GameLoad::Process(void)
{

}

void S_GameLoad::Render(void)
{
	m_BackGround->Render();
	m_LoadMessage->Render("로딩중입니다..!", 1, 1, 0, 0, 0);
}

void S_GameLoad::Release(void)
{

}
