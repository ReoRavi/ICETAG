#pragma once

class CSprite;
class CLable;

//=============================================
// S_ConnectToRoom : 방 접속 씬
class S_ConnectToRoom :
	public CScene
{
public:
	S_ConnectToRoom();
	virtual ~S_ConnectToRoom();

public:
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
	// IP 입력 바
	CSprite*	m_IPBar;
	// 이름 입력 바
	CSprite*	m_NickNameBar;
	// 뒤로가기 버튼
	CSprite*	m_BackButton;
	// 접속 버튼
	CSprite*	m_ConnectButton;
	// IP 텍스트,
	CLable*	m_IPLable;
	// 이름 텍스트
	CLable*	m_NickNameLable;
	// IP
	string		m_IP;
	// 이름
	string		m_NickName;
	
	// IP를 입력중인가
	bool		m_bIsIPInput;
	// 이름을 입력중이낙
	bool		m_bIsNickNameInput;
	// 키보드 입력을 받은 숫자 키
	bool		m_bIsNumberKeyDown[22];
	// 키보드 입력을 받은 키
	bool		m_bIsKeyBoardDown[26];
	// 숫자 키 식별 
	int			m_InputNumber;
	// 키보드 키 식별 
	int			m_KeyInputNumber;

	// 키보드 입력 체크
	VOID KeyBoardInputCheck(bool bIsIP);
	// 숫자패드 입력 체크
	VOID NumpadInputCheck(bool bIsIP);
};

