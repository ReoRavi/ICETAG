#include "stdafx.h"
#include "Animation.h"
#include "Sprite.h"

CAnimation::CAnimation()
{
	CurTime = GetTickCount();
	MaxAnimationNumber = 0;
	CurrentAnimationCount = 0;
}


CAnimation::~CAnimation()
{
}

//=================================================================
// CreateAnimation : �ִϸ��̼��� �����.
// AnimationCount - �ִϸ��̼��� ����
// AnimationSpriteName - �ִϸ��̼� �̹����� �̸���
VOID CAnimation::CreateAnimation(int AnimationCount, string AnimationSpriteName[])
{
	// �ִϸ��̼� �̸� ���
	for (int i = 0; i < AnimationCount; i++)
	{
		SpriteName[i] = AnimationSpriteName[i];
	}

	CurrentAnimationCount = 0;
	MaxAnimationNumber = AnimationCount;
}

//=================================================================
// AnimationFrameControl : �ִϸ��̼��� �������� ��Ʈ���� ��.
// Sprite - ��Ʈ���� �ִϸ��̼��� ��������Ʈ ��ü
VOID CAnimation::AnimationFrameControl(CSprite* Sprite)
{
	// �ð��� ����Ͽ� �ִϸ��̼� �������� �ڿ������� �ٲ۴�.
	if (GetTickCount() - CurTime > 100)
	{
		CurTime = GetTickCount();

		Sprite->CreateSprite(SpriteName[CurrentAnimationCount].c_str());

		CurrentAnimationCount++;

		if (CurrentAnimationCount >= MaxAnimationNumber)
		{
			CurrentAnimationCount = 0;
		}
	}
}
