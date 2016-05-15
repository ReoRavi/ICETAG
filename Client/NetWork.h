#pragma once

// ����
const DWORD ERROR_NULLPACKETRECEIVED = 1;

//=============================================
// CNetWork : ��Ʈ��ũ ó���� ����ϴ� Ŭ����.
class CNetWork :
	public ISingleton <CNetWork>
{
public :
	CNetWork();
	virtual ~CNetWork();

public :
	// ���� ����
	SOCKET					hSocket;
	// ���� �ּ�
	SOCKADDR_IN		servAddr;
	// �ۼ��� ����ü
	fd_set							fd_Recv, fd_Send;
	// ���� �Ͽ� ����� �ۼ��� ����ü
	fd_set							cpyRecv, cpySend;
	// �˸��� ��ٸ��� �ð�
	TIMEVAL					TimeOut;
	// ��Ŷ ���� �ð�
	LARGE_INTEGER	m_CurTime, m_OldTime, m_TimeFrequency;
	// �����°�
	bool								m_bIsConnected;
	// ��Ŷ�� ����
	DWORD PacketLength;
	// ��Ŷ Ÿ��
	ePacket_Protocol PacketType;

public :
	// �ʱ�ȭ
	BOOL Initialize(string IP);
	// ����
	VOID Loop();
	// �޸� ����
	VOID Release();
};

#define Network CNetWork::GetInstance()

