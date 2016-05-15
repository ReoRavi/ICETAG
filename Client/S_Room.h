#pragma once

class CSprite;
class CLable;

//=============================================
// S_Room : �� ��
class S_Room :
	public CScene
{
public:
	S_Room();
	virtual ~S_Room();

public :
	// ���
	CSprite*	m_BackGround;
	// ������ ����
	CSprite*	m_UserAttendSign[8];
	// ���� ��� �ڽ�
	CSprite*	m_PlayerSite[8];
	// �غ� ��ư
	CSprite*	m_PlayerButton;
	// ������ ��ư
	CSprite*	m_ExitButton;
	// �÷��̾��� �̸� �ؽ�Ʈ
	CLable*	m_PlayerName[8];
	// ���� �޼���
	string		m_RoomMessage;

	// �ʱ�ȭ
	VOID Init(VOID) override;
	// ����
	VOID Process(VOID) override;
	// �̹��� ���
	VOID Render(VOID) override;
	// �޸� ����
	VOID Release(VOID) override;

	// �÷��̾��� ��ư�� ���°� ����Ǿ� �̹��� ����.
	VOID PlayerButtonChange(VOID);
	// �÷��̾� ���°� ����Ǿ���.
	VOID PlayerStateImageControl(VOID);
	// �÷��̾ �غ�Ǿ���.
	VOID PlayerReady(VOID);
	// �÷��̾ ��ư�� Ŭ���ߴ�.
	VOID PlayerButtonClick(VOID);
	// �÷��̾ ������.
	VOID PlayerExit(VOID);
};

