#pragma once

//==================================================
// CNetwork : ��Ʈ��ũ ó���� ����Ѵ�.
// ISingleton - �̱����� ��ӹ޾� ���α׷� ������ �ϳ��� �����ϴ� �ν��Ͻ��� �����.
class CNetWork :
	public ISingleton<CNetWork>
{
public:
	CNetWork();
	virtual ~CNetWork();

public:
	// ���� ����, Ŭ���̾�Ʈ ����
	SOCKET hServSock, hClntSock[MAX_CLIENT];
	// ������ �ּ�, Ŭ���̾�Ʈ�� �ּ�
	SOCKADDR_IN ServAdr, ClntAdr;
	// �˸��� ������� ����� �ð�
	TIMEVAL TimeOut;
	// ������ ����, �۽� �˸��� ���� ���� �迭�� ���� ����ü.
	fd_set fd_Recv, fd_Send;
	// select �Լ��� ����ϸ� ������ fd_set ����ü�� ��Ʋ���� ������ �����Ͽ� ����Ѵ�.
	fd_set cpyRecv, cpySend;
	
	// ��Ŷ ����
	CStream* Buf;
	// ��Ŷ�� ����
	DWORD PacketLength;
	// ��Ŷ �������� Ÿ��
	ePacket_Protocol PacketType;

	// ������ Ŭ���̾�Ʈ�� ��
	int ClientCount;

	//���� ��Ŷ�� �����°�
	int SendClientNum;

public:
	// �ʱ�ȭ
	BOOL Initialize(VOID);
	// �޸� ����
	BOOL	Release(VOID);
	// ���� ����
	VOID	Loop(VOID);

	// Ŭ���̾�Ʈ�� ������ �����Ѵ�.
	VOID ClientRelease(int SerialNum);
	// ��Ŷ �������� ó��
	VOID PacketProc(CStream* Buf, ePacket_Protocol ProtocolType);

public :

	//==========================================================================
	//Room
	//
	// ������ ��ȣ
	int MasterNum;
	// �÷��̾ ������ �迭
	bool bIsPlayer[8];
	// �÷��̾��� �غ� ����
	bool bIsPlayerReady[8];
	// �÷��̾ ��� �غ�Ǿ����� üũ��
	bool bIsAllPlayerReady;
	// �÷��̾���� �̸�
	std::string PlayerName[8];
	// �� ���� �ʱ�ȭ
	void RoomValueInit();
	//==========================================================================

	//==========================================================================
	//InGame
	//
	// �÷��̾� X��ǥ
	int					PlayerXPos[8];
	// �÷��̾� Y��ǥ
	int					PlayerYPos[8];
	// ������ ��ȣ
	int					TaggerNum;
	// �÷��̾ �����ߴ°�
	bool				bIsPlayerQuit[8];
	// ������ ���۵Ǿ� ������ ������°�
	bool				bIsTaggerON;
	// ������ �����°�
	bool				bIsGameEnd;
	// �÷��̾�(����)�� �̰�°�
	bool				bIsPlayerWin;
	// �÷��̾��� ���� ���� (���, ����, ����, ����)
	eCharacter_State	PlayerState[8];
	// �÷��̾��� �̵�����
	eCharacter_Direction PlayerDirection[8];
	// ���� �ð�
	float StartTime;
	// �ΰ��� ���� �ʱ�ȭ
	void InGameValueInit();
	//==========================================================================
	
	//==========================================================================
	// KeepAlive - Ŭ���̾�Ʈ�� ���ͳ� ���¸� üũ�ϰ�, �Ҿ����ϸ� ������ ���´�.
	//
	// �������� �ڵ�
	HANDLE	m_hKeepThread;
	// Ŭ���̾�Ʈ�� ������ KeepAlive ������ üũ�� �ð�.
	LARGE_INTEGER			m_CurSendTime[8], m_OldSendTime[8], m_TimeFrequency;
	// Ŭ���̾�Ʈ���� ��Ʈ��Ʈ ī��Ʈ
	int		m_HeartBeatCount[8];
	//==========================================================================

	// �ð��� �ʷ� ġȯ�ؼ� ������.
	float TimetoSecond(VOID);
	// ������ ���۵ǰ� �ð��� �帣�� �Ѵ�.
	int GameTimeLoop(VOID);
};

