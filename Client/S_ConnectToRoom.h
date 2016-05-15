#pragma once

class CSprite;
class CLable;

//=============================================
// S_ConnectToRoom : �� ���� ��
class S_ConnectToRoom :
	public CScene
{
public:
	S_ConnectToRoom();
	virtual ~S_ConnectToRoom();

public:
	// �ʱ�ȭ
	VOID Init(VOID) override;
	// ����
	VOID Process(VOID) override;
	// �̹��� ���
	VOID Render(VOID) override;
	// �޸� ����
	VOID Release(VOID) override;

public :
	// ���
	CSprite*	m_BackGround;
	// IP �Է� ��
	CSprite*	m_IPBar;
	// �̸� �Է� ��
	CSprite*	m_NickNameBar;
	// �ڷΰ��� ��ư
	CSprite*	m_BackButton;
	// ���� ��ư
	CSprite*	m_ConnectButton;
	// IP �ؽ�Ʈ,
	CLable*	m_IPLable;
	// �̸� �ؽ�Ʈ
	CLable*	m_NickNameLable;
	// IP
	string		m_IP;
	// �̸�
	string		m_NickName;
	
	// IP�� �Է����ΰ�
	bool		m_bIsIPInput;
	// �̸��� �Է����̳�
	bool		m_bIsNickNameInput;
	// Ű���� �Է��� ���� ���� Ű
	bool		m_bIsNumberKeyDown[22];
	// Ű���� �Է��� ���� Ű
	bool		m_bIsKeyBoardDown[26];
	// ���� Ű �ĺ� 
	int			m_InputNumber;
	// Ű���� Ű �ĺ� 
	int			m_KeyInputNumber;

	// Ű���� �Է� üũ
	VOID KeyBoardInputCheck(bool bIsIP);
	// �����е� �Է� üũ
	VOID NumpadInputCheck(bool bIsIP);
};

