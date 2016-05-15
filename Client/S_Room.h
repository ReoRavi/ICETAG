#pragma once

class CSprite;
class CLable;

//=============================================
// S_Room : 방 씬
class S_Room :
	public CScene
{
public:
	S_Room();
	virtual ~S_Room();

public :
	// 배경
	CSprite*	m_BackGround;
	// 유저의 상태
	CSprite*	m_UserAttendSign[8];
	// 유저 출력 박스
	CSprite*	m_PlayerSite[8];
	// 준비 버튼
	CSprite*	m_PlayerButton;
	// 나가기 버튼
	CSprite*	m_ExitButton;
	// 플레이어의 이름 텍스트
	CLable*	m_PlayerName[8];
	// 방의 메세지
	string		m_RoomMessage;

	// 초기화
	VOID Init(VOID) override;
	// 루프
	VOID Process(VOID) override;
	// 이미지 출력
	VOID Render(VOID) override;
	// 메모리 해제
	VOID Release(VOID) override;

	// 플레이어의 버튼의 상태가 변경되어 이미지 변경.
	VOID PlayerButtonChange(VOID);
	// 플레이어 상태가 변경되었다.
	VOID PlayerStateImageControl(VOID);
	// 플레이어가 준비되었다.
	VOID PlayerReady(VOID);
	// 플레이어가 버튼을 클릭했다.
	VOID PlayerButtonClick(VOID);
	// 플레이어가 나갔다.
	VOID PlayerExit(VOID);
};

