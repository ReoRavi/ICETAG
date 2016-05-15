#pragma once

class CSprite;
class CLable;
class CAnimation;

#define MAP_ROCKNUM 28

//=============================================
// S_InGame : �ΰ��� ��
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
	
	// �ʱ�ȭ
	VOID Init(VOID) override;
	// ����
	VOID Process(VOID) override;
	// �̹��� ���
	VOID Render(VOID) override;
	// �޸� ����
	VOID Release(VOID) override;

	// �÷��̾� �̵�
	VOID PlayerMove(VOID);
	// �÷��̾� Ű ��Ʈ��
	VOID PlayerKeyControl(VOID);
	// �÷��̾� �ִϸ��̼� ��Ʈ��
	VOID PlayerAnimationControl(int Count);
	// �÷��̾� ���� ��Ʈ��
	VOID PlayerStateControl(int Count);
	// �÷��̾� ���� ��Ʈ��
	VOID PlayerDirectionControl(int Count);
	// �÷��̾� ��ǥ ��Ʈ��
	VOID PlayerPositionControl(int Count);
	// ���� �ִϸ��̼� ��Ʈ��
	VOID DuckDirectionImageControl(int PlayerCount, eCharacter_Direction Direction);
	// ����� �ִϸ��̼� ��Ʈ��
	VOID SnowManDirectionImageControl(int PlayerCount, eCharacter_Direction Direction);
	// �ð�UI�� �׸���.
	VOID TimeRender(VOID);
	// �÷��̾ ������ �ٲ۴�.
	VOID PlayertoTagger(VOID);
};

