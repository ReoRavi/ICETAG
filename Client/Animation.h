#pragma once

#define MAX_ANIMATION 256

class CSprite;

//=============================================
// CAnimation : 애니메이션 부분을 담당한다.
class CAnimation
{
public:
	CAnimation();
	virtual ~CAnimation();

	// 애니메이션을 만든다.
	VOID CreateAnimation(int AnimationCount, string AnimationSpriteName[]);
	// 애니메이션의 프레임을 컨트롤한다.
	VOID AnimationFrameControl(CSprite* Sprite);

public :
	// 애니메이션 이미지 이름들
	string	SpriteName[MAX_ANIMATION];
	// 애니메이션 갯수
	int		MaxAnimationNumber;
	// 현재 애니메이션 갯수
	int		CurrentAnimationCount;
	// 프레임 컨트롤 변수
	float	CurTime;
};

