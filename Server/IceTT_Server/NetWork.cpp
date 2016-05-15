#include "stdafx.h"
#include "NetWork.h"

//===================================================
// KeepThreadCallBack : KeepAlive�� üũ�ϴ� ������.
// pArgument - CNetwork ��ü�� ���޵ȴ�.
unsigned int WINAPI KeepThreadCallBack(void* pArgument)
{
	CNetWork* pNetWork = (CNetWork*)pArgument;

	while (1)
	{
		// Ŭ���̾�Ʈ �� ��ŭ
		for (int i = 0; i < MAX_CLIENT; i++)
		{
			// �÷��̾ �����Ѵٸ�
			if (pNetWork->bIsPlayer[i])
			{
				// �ð� ����
				QueryPerformanceCounter(&pNetWork->m_CurSendTime[i]);

				// �ð��� �� �Ǹ�
				if ((pNetWork->m_CurSendTime[i].QuadPart - pNetWork->m_OldSendTime[i].QuadPart) / (pNetWork->m_TimeFrequency.QuadPart / 1000) > 10000)
				{
					CStream* Buf = new CStream();

					CMakePacket::Packet_Send_KeepAlive(Buf);

					// ��Ʈ��Ʈ üũ ��Ŷ�� ������.
					send(pNetWork->hClntSock[i], Buf->m_SendBuffer, Buf->m_BufferWritePoint, 0);

					pNetWork->m_HeartBeatCount[i]++;

					QueryPerformanceCounter(&pNetWork->m_OldSendTime[i]);
				}
				// ��Ʈ��Ʈ ī��Ʈ�� �ִ밡 �Ǿ���.
				if (pNetWork->m_HeartBeatCount[i] >= 6)
				{
					// Ŭ���̾�Ʈ�� ������ ����ٰ� �Ǵ��Ͽ� ������ ���´�.
					QueryPerformanceCounter(&pNetWork->m_CurSendTime[i]);
					QueryPerformanceCounter(&pNetWork->m_OldSendTime[i]);
					pNetWork->m_HeartBeatCount[i] = 0;

					printf("KeepAlive Check : %d Client Disconnected\n", i + 1);
					pNetWork->ClientRelease(i);

					// �ٸ� ����ִ� Ŭ���̾�Ʈ�鿡�� ���� ���� ������Ʈ ��Ŷ�� ������.
					for (int j = 0; j < MAX_CLIENT; j++)
					{
						if (pNetWork->bIsPlayer[j])
						{
							bool bIsMaster;

							if (pNetWork->MasterNum == j)
								bIsMaster = true;
							else
								bIsMaster = false;

							CStream* Buf = new CStream();

							CMakePacket::Packet_Send_Room_UserUpdate(Buf, pNetWork->ClientCount, j, bIsMaster, pNetWork->MasterNum, pNetWork->bIsPlayer, pNetWork->bIsPlayerReady, pNetWork->PlayerName);
							send(pNetWork->hClntSock[j], Buf->m_SendBuffer, Buf->m_BufferWritePoint, 0);
						}
					}
				}
			}
		}
	}

	return 0;
}
CNetWork::CNetWork()
{

}


CNetWork::~CNetWork()
{

}

//===================================================
// Initialize : �ʱ�ȭ
BOOL CNetWork::Initialize(VOID)
{
	WSADATA wsaData;

	// ������ ���� ���α׷��� �ʱ�ȭ
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return FALSE;

	// ���� �ʱ�ȭ
	hServSock = socket(PF_INET, SOCK_STREAM, 0);

	memset(&ServAdr, 0, sizeof(ServAdr));

	// �ּ� �Ҵ�
	ServAdr.sin_family = AF_INET;
	ServAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	ServAdr.sin_port = htons(atoi("1237"));

	printf("================================\n");

	printf("Server Initialize Start.\n");
	printf("Port : %d\n", htons(ServAdr.sin_port));

	// ���Ͽ� �ּ� �Ҵ�
	if (bind(hServSock, (SOCKADDR*)&ServAdr, sizeof(ServAdr)) == SOCKET_ERROR)
	{
		printf("Bind Failed..\n");

		return FALSE;
	}
	else
	{
		printf("Bind Clear..!\n");
	}

	// ������ �����·� ��ȯ
	if (listen(hServSock, 5) == SOCKET_ERROR)
	{
		printf("Listen Failed..\n");

		return FALSE;
	}
	else
	{
		printf("Listen Clear..!\n");
	}

	FD_ZERO(&fd_Recv);
	FD_ZERO(&fd_Send);
	FD_ZERO(&cpyRecv);
	FD_ZERO(&cpySend);

	// ���������� ���� �˸��� �޵��� ���� .
	FD_SET(hServSock, &fd_Recv);

	// ������ ���� �ʱ�ȭ
	Buf = new CStream;
	Buf->Init();

	ClientCount = 0;

	SendClientNum = 0;

	// ���� �ɼ� ����
	LINGER Linger;
	Linger.l_onoff = 1;
	Linger.l_linger = 0;

	// ������ ����� ���Ḧ ���� �ʴ´�.
	setsockopt(hServSock, SOL_SOCKET, SO_LINGER, (char*)&Linger, sizeof(Linger));

	printf("\n================================\n");
	printf("Server Initialize Clear..!\n");
	printf("================================\n");

	printf("\n- Server Info -\n\n");
	printf("Model : Select Model\n");
	printf("MaxClient : %d\n", MAX_CLIENT);
	printf("Devloped by : Ravi\n");
	printf("Version : 0.1 - Test Ver.\n");
	printf("Date : 2015/10/19\n");

	printf("================================\n\n");


	// �÷��̾� �ʱ�ȭ
	ZeroMemory(bIsPlayer, sizeof(bIsPlayer));
	MasterNum = 0;
	bIsAllPlayerReady = FALSE;

	ZeroMemory(bIsPlayerReady, sizeof(bIsPlayerReady));
	ZeroMemory(bIsPlayerQuit, sizeof(bIsPlayerQuit));
	
	for (int i = 0; i < 8; i++)
	{
		PlayerState[i] = eCharacter_State::eCharacter_Idle;
		PlayerDirection[i] = eCharacter_Direction::eDirection_DOWN;
	}

	PlayerXPos[0] = 250;
	PlayerXPos[1] = 350;
	PlayerXPos[2] = 450;
	PlayerXPos[3] = 550;
	PlayerXPos[4] = 250;
	PlayerXPos[5] = 350;
	PlayerXPos[6] = 450;
	PlayerXPos[7] = 550;

	PlayerYPos[0] = 250;
	PlayerYPos[1] = 250;
	PlayerYPos[2] = 250;
	PlayerYPos[3] = 250;
	PlayerYPos[4] = 450;
	PlayerYPos[5] = 450;
	PlayerYPos[6] = 450;
	PlayerYPos[7] = 450;

	bIsTaggerON = false;
	bIsGameEnd = false;

	// ��Ʈ��Ʈ ī��Ʈ �ʱ�ȭ �� ������ ����
	ZeroMemory(m_HeartBeatCount, sizeof(m_HeartBeatCount));
	QueryPerformanceFrequency(&m_TimeFrequency);
	m_hKeepThread = (HANDLE)_beginthreadex(NULL, 0, KeepThreadCallBack, this, 0, NULL);

	return TRUE;
}

//===================================================
// Release : �޸� ����
BOOL CNetWork::Release(VOID)
{
	// fd_set ����ü �ʱ�ȭ
	FD_ZERO(&fd_Recv);
	FD_ZERO(&fd_Send);
	FD_ZERO(&cpyRecv);
	FD_ZERO(&cpySend);

	// ���� ����
	Buf->ReleaseBuffer();

	// Ŭ���̾�Ʈ ���� ����
	for (int index = 0; index < MAX_CLIENT; index++)
	{
		if (hClntSock[index])
			ClientRelease(index);
	}

	// ���� ���� ����
	closesocket(hServSock);


	return TRUE;
}

//===================================================
// Loop : ����
VOID CNetWork::Loop(VOID)
{
	TimeOut.tv_sec = 0;
	TimeOut.tv_usec = 0;

	// fd_set ����ü�� �����ؼ� ����Ѵ�. (������ ����ϸ� ������ �ٲ��)
	cpyRecv = fd_Recv;
	cpySend = fd_Send;

	// �˸��� �´ٸ� 0���� ū ���� �����Ѵ�.
	int SockResult = select(0, &cpyRecv, 0, 0, &TimeOut);

	// �˸��� �־��ٸ�.
	if (0 < SockResult)
	{
		// �������Ͽ� ���� �˸��� �Դ�.
		if (FD_ISSET(hServSock, &cpyRecv))
		{
			// Ŭ���̾�Ʈ�� ���� ��û.
			int PlayerNum;

			// �÷��̾��� �ε��� ����
			for (int i = 0; i < MAX_CLIENT; i++)
			{
				if (!bIsPlayer[i])
				{
					PlayerNum = i;
					break;
				}
			}

			// Ŭ���̾�Ʈ�� ����, �۽� �˸��� �޵��� �����Ѵ�.
			int adrSz = sizeof(ClntAdr);
			hClntSock[PlayerNum] = accept(hServSock, (SOCKADDR*)&ClntAdr, &adrSz);
			FD_SET(hClntSock[PlayerNum], &fd_Recv);
			FD_SET(hClntSock[PlayerNum], &fd_Send);

			// ���� �ɼ� ����
			LINGER Linger;
			Linger.l_onoff = 1;
			Linger.l_linger = 0;

			// ������ ����� ���Ḧ ���� �ʰ� �ٷ� �����Ѵ�.
			setsockopt(hClntSock[PlayerNum], SOL_SOCKET, SO_LINGER, (char*)&Linger, sizeof(Linger));
			
			// ��Ʈ��Ʈ �ð� ����
			QueryPerformanceCounter(&m_CurSendTime[PlayerNum]);
			QueryPerformanceCounter(&m_OldSendTime[PlayerNum]);

			// Ŭ���̾�Ʈ�� ���� ������Ų��.
			ClientCount++;

			printf("New client Connected : %d (PORT : %d) \n", ClientCount, ClntAdr.sin_port);

			// �÷��̾� ��ü �Ҵ�
			for (int i = 0; i < 8; i++)
			{
				if (!bIsPlayer[i])
				{
					bIsPlayer[i] = true;

					break;
				}
			}
		}

		for (int i = 0; i < MAX_CLIENT; i++)
		{
			// Ŭ���̾�Ʈ�κ��� ��Ŷ�� ���ŵǾ���.
			if (FD_ISSET(hClntSock[i], &cpyRecv))
			{
				SendClientNum = i;

				// ��Ŷ�� �޴´�.
				recv(hClntSock[i], Buf->m_RecvBuffer, BUF_SIZE, 0);

				// ��Ŷ�� Ÿ���� ���Ѵ�.
				Buf->ReadProtocol(&PacketType);

				// ��Ŷ�� ���̸� ���Ѵ�.
				Buf->ReadDWORD(&PacketLength);

				// ���� ��Ŷ�� ó���Ѵ�.
				PacketProc(Buf, PacketType);

				// ��Ŷ�� �ʱ�ȭ�Ѵ�.
				Buf->ClearRecvBuffer();
				Buf->ResetRecvPoint();
			}
		}
	}

}

//===================================================
// PacketProc : ��Ŷ�� ó���Ѵ�.
// Buf : ��Ŷ�� ����
// ProtocolType : ��Ŷ�� Ÿ��
VOID CNetWork::PacketProc(CStream* Buf, ePacket_Protocol ProtocolType)
{
	// ��Ŷ�� Ÿ�Կ� ���� ó���Ѵ�.
	switch (ProtocolType)
	{
		// �÷��̾� ���� ��û
	case ePacket_Protocol::ePacket_ConnectRequest:
		CAnalysisPacket::Packet_Analysis_ConnectToRoom_ConnectAccept(Buf, this);

		break;

		// ���� ���� ��û
	case ePacket_Protocol::ePacket_Room_GameStart :
		CAnalysisPacket::Packet_Analysis_Room_GameStart(Buf, this);

		break;

		// �� ���� ������Ʈ
	case ePacket_Protocol::ePacket_RoomDataUpdate:
		CAnalysisPacket::Packet_Analysis_Room_DataUpdate(Buf, this);

		break;

		// �ΰ����� ��� ���� ������Ʈ
	case ePacket_Protocol::ePacket_InGame_All:
		CAnalysisPacket::Packet_Analysis_InGame_All(Buf, this);

		break;

		// ������ ���� �κ�� �̵��Ѵ�.
	case ePacket_Protocol::ePacket_InGame_ChangetoLobby:
		CAnalysisPacket::Packet_Analysis_InGame_ChangetoLobby(Buf, this);

		break;

		// �÷��̾��� �غ���¸� ������Ʈ�Ѵ�.
	case ePacket_Protocol::ePacket_InGame_PlayerReady:
		CAnalysisPacket::Packet_Analysis_Room_PlayerReady(Buf, this);

		break;

		// �÷��̾ ������ �����ߴ�.
	case ePacket_Protocol::ePacket_Room_GameQuit:
		CAnalysisPacket::Packet_Analysis_Room_GameQuit(Buf, this);

		break;

		// ��Ʈ��Ʈ ó��
	case ePacket_Protocol::ePacket_KeepAlive:
		CAnalysisPacket::Packet_Analysis_KeepAlive(Buf, this);

		break;

	default:
		break;
	}
}

//===================================================
// ClientRelease : Ŭ���̾�Ʈ�� ������ �����ߴ�.
VOID CNetWork::ClientRelease(int SerialNum)
{
	// Ŭ���̾�Ʈ�� ������ ���´�.
	shutdown(hClntSock[SerialNum], SD_BOTH);

	// �÷��̾�� ���� ó��
	bIsPlayerReady[SerialNum] = FALSE;
	bIsPlayer[SerialNum] = false;
	// �ۼ��� ���� ����
	FD_CLR(fd_Recv.fd_array[SerialNum + 1], &fd_Recv);
	FD_CLR(fd_Send.fd_array[SerialNum], &fd_Send);

	// ���� �ݱ�
	closesocket(hClntSock[SerialNum]);

	printf("Client Disconnected : %d (PORT : %d) \n", SerialNum, ClntAdr.sin_port);
	ClientCount--;
}

//===================================================
// RoomValueInit : �� ���� �ʱ�ȭ
void CNetWork::RoomValueInit()
{
	MasterNum = 0;
	bIsAllPlayerReady = FALSE;

	ZeroMemory(bIsPlayerReady, sizeof(bIsPlayerReady));
	ZeroMemory(bIsPlayerQuit, sizeof(bIsPlayerQuit));

	for (int i = 0; i < 8; i++)
	{
		PlayerState[i] = eCharacter_State::eCharacter_Idle;
	}
}

//===================================================
// InGameValueInit : �ΰ��� ���� �ʱ�ȭ
void CNetWork::InGameValueInit()
{
	for (int i = 0; i < 8; i++)
	{
		PlayerState[i] = eCharacter_State::eCharacter_Idle;
	}

	PlayerXPos[0] = 250;
	PlayerXPos[1] = 350;
	PlayerXPos[2] = 450;
	PlayerXPos[3] = 550;
	PlayerXPos[4] = 250;
	PlayerXPos[5] = 350;
	PlayerXPos[6] = 450;
	PlayerXPos[7] = 550;

	PlayerYPos[0] = 350;
	PlayerYPos[1] = 350;
	PlayerYPos[2] = 350;
	PlayerYPos[3] = 350;
	PlayerYPos[4] = 450;
	PlayerYPos[5] = 450;
	PlayerYPos[6] = 450;
	PlayerYPos[7] = 450;

	bIsTaggerON = false;
	bIsGameEnd = false;
	bIsPlayerWin = TRUE;
}

//===================================================
// TimetoSecond : �ð��� �ʷ� ġȯ�ؼ� ������.
float CNetWork::TimetoSecond(VOID)
{
	SYSTEMTIME t;

	GetLocalTime(&t);

	return (t.wHour * 3600) + (t.wMinute * 60) + (t.wSecond);
}

//===================================================
// GameTimeLoop : ������ ���۵ǰ� �ð��� �帣�� �Ѵ�.
int CNetWork::GameTimeLoop(VOID)
{
	float Now;
	// ��� �ð�
	int TimeElapse;

	Now = TimetoSecond();

	TimeElapse = Now - StartTime;

	return TimeElapse;
}
