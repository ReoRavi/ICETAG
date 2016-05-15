#pragma once

//=============================================
// CScene : 씬 객체
class CScene
{
public:
	CScene(VOID);
	~CScene(VOID);

	// 순수 가상함수
	// 초기화
	virtual VOID Init(VOID)		= 0;
	// 루프
	virtual VOID Process(VOID)	= 0;
	// 이미지 출력
	virtual VOID Render(VOID)	= 0;
	// 메모리 해제
	virtual VOID Release(VOID)	= 0;
	
	// 그리기 시작
	VOID PreRender(VOID);
	// 그리기 끝
	VOID PostRender(VOID);
};

