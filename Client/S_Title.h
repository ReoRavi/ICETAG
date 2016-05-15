#pragma once

class CSprite;
class CLable;
class CAnimation;

//=============================================
// S_Title : 타이틀 씬
class S_Title :
	public CScene
{
public:
	S_Title();
	virtual ~S_Title();

	// 초기화
	VOID Init(VOID) override;
	// 루프
	VOID Process(VOID) override;
	// 이미지 출력
	VOID Render(VOID) override;
	// 메모리 해제
	VOID Release(VOID) override;

public  :
	// 배경
	CSprite* m_BackGround;
	// 로고
	CSprite* m_Logo;
	// 게임 시작 버튼
	CSprite* m_GameStartButton;
	// 게임 방법 버튼
	CSprite* m_HowtoPlayButton;
	// 나가기 버튼
	CSprite* m_ExitButton;
};

