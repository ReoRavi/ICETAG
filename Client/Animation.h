#pragma once

#define MAX_ANIMATION 256

class CSprite;

//=============================================
// CAnimation : �ִϸ��̼� �κ��� ����Ѵ�.
class CAnimation
{
public:
	CAnimation();
	virtual ~CAnimation();

	// �ִϸ��̼��� �����.
	VOID CreateAnimation(int AnimationCount, string AnimationSpriteName[]);
	// �ִϸ��̼��� �������� ��Ʈ���Ѵ�.
	VOID AnimationFrameControl(CSprite* Sprite);

public :
	// �ִϸ��̼� �̹��� �̸���
	string	SpriteName[MAX_ANIMATION];
	// �ִϸ��̼� ����
	int		MaxAnimationNumber;
	// ���� �ִϸ��̼� ����
	int		CurrentAnimationCount;
	// ������ ��Ʈ�� ����
	float	CurTime;
};

