#pragma once

class CSprite;

//=============================================
// S_HowtoPlay : 플레이 방법 씬
class S_HowtoPlay :
	public CScene
{
public:
	S_HowtoPlay();
	virtual ~S_HowtoPlay();

	// 초기화
	VOID Init(VOID) override;
	// 루프
	VOID Process(VOID) override;
	// 이미지 출력
	VOID Render(VOID) override;
	// 메모리 해제
	VOID Release(VOID) override;

public :
	// 배경
	CSprite*	m_BackGround;
	// 돌아가기 버튼
	CSprite*	m_BackButton;
};

