#pragma once

class CSprite;
class CLable;
class CAnimation;

#define MAP_ROCKNUM 28

//=============================================
// S_InGame : 인게임 씬
class S_InGame :
	public CScene
{
public:
	S_InGame();
	virtual ~S_InGame();

public :
	//================================================================
	// Util
	//
	bool					m_bIsKeyDown;
	int						m_SerialNum;
	//================================================================


	//================================================================
	// BackGround
	//
	CSprite*				m_BackGround;
	//================================================================'

	//================================================================
	// Player
	//
	CSprite*							m_Player[8];
	CAnimation*					m_PlayerAnimation[8];
	CLable*							m_PlayerName[8];
	eCharacter_State			m_PlayerState[8];
	eCharacter_State			m_OldPlayerState[8];
	eCharacter_Direction		m_PlayerDirection[8];
	eCharacter_Direction		m_OldPlayerDirection[8];
	BOOL								m_PlayerAlive[8];
	//================================================================

	//================================================================
	// UI
	//
	CSprite*				m_MyCharacterSign;
	CSprite*				m_GameResultWindow;
	CSprite*				m_BacktoRoomButton;
	//================================================================

	//================================================================
	// UI - TImer
	//
	int						m_TimeRenderXPos[3];
	CSprite*				m_Time[3];
	CSprite*				m_TimeDivide;
	//================================================================
	
	//================================================================
	// Effect
	//
	CSprite*				m_SnowManEffect;
	CAnimation*		m_SnowManEffectAnimation;
	//================================================================

	//================================================================
	// Map
	//
	CSprite*				m_Rock[MAP_ROCKNUM];
	//================================================================
	
	//================================================================
	// Network
	//
	LARGE_INTEGER			m_CurSendTime, m_OldSendTime, m_TimeFrequency;
	//================================================================
	
	// 초기화
	VOID Init(VOID) override;
	// 루프
	VOID Process(VOID) override;
	// 이미지 출력
	VOID Render(VOID) override;
	// 메모리 해제
	VOID Release(VOID) override;

	// 플레이어 이동
	VOID PlayerMove(VOID);
	// 플레이어 키 컨트롤
	VOID PlayerKeyControl(VOID);
	// 플레이어 애니메이션 컨트롤
	VOID PlayerAnimationControl(int Count);
	// 플레이어 상태 컨트롤
	VOID PlayerStateControl(int Count);
	// 플레이어 방향 컨트롤
	VOID PlayerDirectionControl(int Count);
	// 플레이어 좌표 컨트롤
	VOID PlayerPositionControl(int Count);
	// 오리 애니메이션 컨트롤
	VOID DuckDirectionImageControl(int PlayerCount, eCharacter_Direction Direction);
	// 눈사람 애니메이션 컨트롤
	VOID SnowManDirectionImageControl(int PlayerCount, eCharacter_Direction Direction);
	// 시간UI를 그린다.
	VOID TimeRender(VOID);
	// 플레이어를 술래로 바꾼다.
	VOID PlayertoTagger(VOID);
};

