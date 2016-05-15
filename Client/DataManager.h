#pragma once

//=============================================
// CDataManager : ���� �������� �����ϴ� ��ü.
class CDataManager :
	public ISingleton <CDataManager>
{
public:
	CDataManager();
	virtual ~CDataManager();

public :
	VOID Initialize(VOID);

public :
	//========================================
	// Scene - InGame
	//
	// �÷��̾ ����ִ°�
	bool bIsPlayerAlive[8];
	// ���� Ŭ���̾�Ʈ�� �ִ°�
	bool bIsClientQuit[8];
	// ������ �����ǰ� ������ ���۵�
	bool bIsIceTagStart;
	// ���� Ŭ���̾�Ʈ�� ��
	int ClientNum;
	// �� Ŭ���̾�Ʈ�� ���� ��ȣ
	int SerialNum;
	// �÷��̾��� ��
	int PlayerNum;
	// �ٸ� �÷��̾��� ��ǥ
	int PlayerXPos[8], PlayerYPos[8];
	// �ð�
	// 0 - �� 1, 2 - ��
	int Time[3];
	// ���� ��ȣ
	int TaggerNum;
	// �÷��̾���� ����
	eCharacter_State	m_PlayerState[8];
	// �÷��̾���� ����
	eCharacter_Direction PlayerDirection[8];
	// �������ΰ�
	bool bIsGameEnd;
	// �÷��̾� �¸� üũ
	bool bIsPlayerWin;

	//========================================
	// Scene - Room
	//
	// ���ο� Ŭ���̾�Ʈ�� �������� �˸�.
	bool bIsNewClient;
	// �÷��̾���� ����
	bool bIsPlayer[8];
	// ��� Ŭ���̾�Ʈ�� �غ�Ǿ���.
	bool bIsAllClientReady;
	// ���� �����ΰ�
	bool bIsMaster;
	// �غ�� Ŭ���̾�Ʈ�� �ִ�.
	bool bIsReadyClient;
	// ���� ������ ���еǾ���.
	bool bIsGameStartFailed;
	// 
	bool bIsOhterPlayerQuit;
	// �÷��̾���� �غ� ����
	bool PlayerReadyState[8];
	// �غ�� Ŭ���̾�Ʈ�� ��ȣ
	int ReadyClientNum;
	// ������ ��ȣ
	int MasterNum;
	// 
	int QuitPlayerNumber;
	// .�÷��̾���� �̸�
	std::string PlayerName[8];

	std::string t_PlayerName;

	//========================================
	// Scene - ALL
	//
	// �÷��̾� ����.
	bool bIsQuit;
	// ���� ��
	bool bIsGameRun;

};

#define DataManager CDataManager::GetInstance()