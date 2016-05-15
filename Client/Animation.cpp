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
// CreateAnimation : 애니메이션을 만든다.
// AnimationCount - 애니메이션의 갯수
// AnimationSpriteName - 애니메이션 이미지의 이름들
VOID CAnimation::CreateAnimation(int AnimationCount, string AnimationSpriteName[])
{
	// 애니메이션 이름 등록
	for (int i = 0; i < AnimationCount; i++)
	{
		SpriteName[i] = AnimationSpriteName[i];
	}

	CurrentAnimationCount = 0;
	MaxAnimationNumber = AnimationCount;
}

//=================================================================
// AnimationFrameControl : 애니메이션의 프레임을 컨트롤한 다.
// Sprite - 컨트롤할 애니메이션의 스프라이트 객체
VOID CAnimation::AnimationFrameControl(CSprite* Sprite)
{
	// 시간을 계산하여 애니메이션 프레임을 자연스럽게 바꾼다.
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
