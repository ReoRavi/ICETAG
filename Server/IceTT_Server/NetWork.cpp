#include "stdafx.h"
#include "NetWork.h"

//===================================================
// KeepThreadCallBack : KeepAlive를 체크하는 쓰레드.
// pArgument - CNetwork 객체가 전달된다.
unsigned int WINAPI KeepThreadCallBack(void* pArgument)
{
	CNetWork* pNetWork = (CNetWork*)pArgument;

	while (1)
	{
		// 클라이언트 수 만큼
		for (int i = 0; i < MAX_CLIENT; i++)
		{
			// 플레이어가 존재한다면
			if (pNetWork->bIsPlayer[i])
			{
				// 시간 갱신
				QueryPerformanceCounter(&pNetWork->m_CurSendTime[i]);

				// 시간이 다 되면
				if ((pNetWork->m_CurSendTime[i].QuadPart - pNetWork->m_OldSendTime[i].QuadPart) / (pNetWork->m_TimeFrequency.QuadPart / 1000) > 10000)
				{
					CStream* Buf = new CStream();

					CMakePacket::Packet_Send_KeepAlive(Buf);

					// 하트비트 체크 패킷을 보낸다.
					send(pNetWork->hClntSock[i], Buf->m_SendBuffer, Buf->m_BufferWritePoint, 0);

					pNetWork->m_HeartBeatCount[i]++;

					QueryPerformanceCounter(&pNetWork->m_OldSendTime[i]);
				}
				// 하트비트 카운트가 최대가 되었다.
				if (pNetWork->m_HeartBeatCount[i] >= 6)
				{
					// 클라이언트에 문제가 생겼다고 판단하여 연결을 끊는다.
					QueryPerformanceCounter(&pNetWork->m_CurSendTime[i]);
					QueryPerformanceCounter(&pNetWork->m_OldSendTime[i]);
					pNetWork->m_HeartBeatCount[i] = 0;

					printf("KeepAlive Check : %d Client Disconnected\n", i + 1);
					pNetWork->ClientRelease(i);

					// 다른 살아있는 클라이언트들에게 유저 정보 업데이트 패킷을 보낸다.
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
// Initialize : 초기화
BOOL CNetWork::Initialize(VOID)
{
	WSADATA wsaData;

	// 윈도우 소켓 프로그래밍 초기화
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return FALSE;

	// 소켓 초기화
	hServSock = socket(PF_INET, SOCK_STREAM, 0);

	memset(&ServAdr, 0, sizeof(ServAdr));

	// 주소 할당
	ServAdr.sin_family = AF_INET;
	ServAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	ServAdr.sin_port = htons(atoi("1237"));

	printf("================================\n");

	printf("Server Initialize Start.\n");
	printf("Port : %d\n", htons(ServAdr.sin_port));

	// 소켓에 주소 할당
	if (bind(hServSock, (SOCKADDR*)&ServAdr, sizeof(ServAdr)) == SOCKET_ERROR)
	{
		printf("Bind Failed..\n");

		return FALSE;
	}
	else
	{
		printf("Bind Clear..!\n");
	}

	// 소켓을 대기상태로 전환
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

	// 서버소켓이 수신 알림을 받도록 연결 .
	FD_SET(hServSock, &fd_Recv);

	// 데이터 버퍼 초기화
	Buf = new CStream;
	Buf->Init();

	ClientCount = 0;

	SendClientNum = 0;

	// 링거 옵션 설정
	LINGER Linger;
	Linger.l_onoff = 1;
	Linger.l_linger = 0;

	// 소켓은 우아한 종료를 하지 않는다.
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


	// 플레이어 초기화
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

	// 하트비트 카운트 초기화 및 쓰레드 실행
	ZeroMemory(m_HeartBeatCount, sizeof(m_HeartBeatCount));
	QueryPerformanceFrequency(&m_TimeFrequency);
	m_hKeepThread = (HANDLE)_beginthreadex(NULL, 0, KeepThreadCallBack, this, 0, NULL);

	return TRUE;
}

//===================================================
// Release : 메모리 해제
BOOL CNetWork::Release(VOID)
{
	// fd_set 구조체 초기화
	FD_ZERO(&fd_Recv);
	FD_ZERO(&fd_Send);
	FD_ZERO(&cpyRecv);
	FD_ZERO(&cpySend);

	// 버퍼 해제
	Buf->ReleaseBuffer();

	// 클라이언트 소켓 종료
	for (int index = 0; index < MAX_CLIENT; index++)
	{
		if (hClntSock[index])
			ClientRelease(index);
	}

	// 서버 소켓 종료
	closesocket(hServSock);


	return TRUE;
}

//===================================================
// Loop : 루프
VOID CNetWork::Loop(VOID)
{
	TimeOut.tv_sec = 0;
	TimeOut.tv_usec = 0;

	// fd_set 구조체를 복사해서 사용한다. (원본을 사용하면 정보가 바뀐다)
	cpyRecv = fd_Recv;
	cpySend = fd_Send;

	// 알림이 온다면 0보다 큰 값을 리턴한다.
	int SockResult = select(0, &cpyRecv, 0, 0, &TimeOut);

	// 알림이 있었다면.
	if (0 < SockResult)
	{
		// 서버소켓에 수신 알림이 왔다.
		if (FD_ISSET(hServSock, &cpyRecv))
		{
			// 클라이언트의 연결 요청.
			int PlayerNum;

			// 플레이어의 인덱스 설정
			for (int i = 0; i < MAX_CLIENT; i++)
			{
				if (!bIsPlayer[i])
				{
					PlayerNum = i;
					break;
				}
			}

			// 클라이언트를 수신, 송신 알림을 받도록 연결한다.
			int adrSz = sizeof(ClntAdr);
			hClntSock[PlayerNum] = accept(hServSock, (SOCKADDR*)&ClntAdr, &adrSz);
			FD_SET(hClntSock[PlayerNum], &fd_Recv);
			FD_SET(hClntSock[PlayerNum], &fd_Send);

			// 링거 옵션 설정
			LINGER Linger;
			Linger.l_onoff = 1;
			Linger.l_linger = 0;

			// 소켓은 우아한 종료를 하지 않고 바로 종료한다.
			setsockopt(hClntSock[PlayerNum], SOL_SOCKET, SO_LINGER, (char*)&Linger, sizeof(Linger));
			
			// 하트비트 시간 설정
			QueryPerformanceCounter(&m_CurSendTime[PlayerNum]);
			QueryPerformanceCounter(&m_OldSendTime[PlayerNum]);

			// 클라이언트의 수를 증가시킨다.
			ClientCount++;

			printf("New client Connected : %d (PORT : %d) \n", ClientCount, ClntAdr.sin_port);

			// 플레이어 객체 할당
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
			// 클라이언트로부터 패킷이 수신되었다.
			if (FD_ISSET(hClntSock[i], &cpyRecv))
			{
				SendClientNum = i;

				// 패킷을 받는다.
				recv(hClntSock[i], Buf->m_RecvBuffer, BUF_SIZE, 0);

				// 패킷의 타입을 구한다.
				Buf->ReadProtocol(&PacketType);

				// 패킷의 길이를 구한다.
				Buf->ReadDWORD(&PacketLength);

				// 받은 패킷을 처리한다.
				PacketProc(Buf, PacketType);

				// 패킷을 초기화한다.
				Buf->ClearRecvBuffer();
				Buf->ResetRecvPoint();
			}
		}
	}

}

//===================================================
// PacketProc : 패킷을 처리한다.
// Buf : 패킷의 버퍼
// ProtocolType : 패킷의 타입
VOID CNetWork::PacketProc(CStream* Buf, ePacket_Protocol ProtocolType)
{
	// 패킷의 타입에 따라 처리한다.
	switch (ProtocolType)
	{
		// 플레이어 연결 요청
	case ePacket_Protocol::ePacket_ConnectRequest:
		CAnalysisPacket::Packet_Analysis_ConnectToRoom_ConnectAccept(Buf, this);

		break;

		// 게임 시작 요청
	case ePacket_Protocol::ePacket_Room_GameStart :
		CAnalysisPacket::Packet_Analysis_Room_GameStart(Buf, this);

		break;

		// 방 정보 업데이트
	case ePacket_Protocol::ePacket_RoomDataUpdate:
		CAnalysisPacket::Packet_Analysis_Room_DataUpdate(Buf, this);

		break;

		// 인게임의 모든 정보 업데이트
	case ePacket_Protocol::ePacket_InGame_All:
		CAnalysisPacket::Packet_Analysis_InGame_All(Buf, this);

		break;

		// 게임이 끝나 로비로 이동한다.
	case ePacket_Protocol::ePacket_InGame_ChangetoLobby:
		CAnalysisPacket::Packet_Analysis_InGame_ChangetoLobby(Buf, this);

		break;

		// 플레이어의 준비상태를 업데이트한다.
	case ePacket_Protocol::ePacket_InGame_PlayerReady:
		CAnalysisPacket::Packet_Analysis_Room_PlayerReady(Buf, this);

		break;

		// 플레이어가 게임을 종료했다.
	case ePacket_Protocol::ePacket_Room_GameQuit:
		CAnalysisPacket::Packet_Analysis_Room_GameQuit(Buf, this);

		break;

		// 하트비트 처리
	case ePacket_Protocol::ePacket_KeepAlive:
		CAnalysisPacket::Packet_Analysis_KeepAlive(Buf, this);

		break;

	default:
		break;
	}
}

//===================================================
// ClientRelease : 클라이언트가 접속을 종료했다.
VOID CNetWork::ClientRelease(int SerialNum)
{
	// 클라이언트의 연결을 끊는다.
	shutdown(hClntSock[SerialNum], SD_BOTH);

	// 플레이어ㅓ 관련 처리
	bIsPlayerReady[SerialNum] = FALSE;
	bIsPlayer[SerialNum] = false;
	// 송수신 연결 해제
	FD_CLR(fd_Recv.fd_array[SerialNum + 1], &fd_Recv);
	FD_CLR(fd_Send.fd_array[SerialNum], &fd_Send);

	// 소켓 닫기
	closesocket(hClntSock[SerialNum]);

	printf("Client Disconnected : %d (PORT : %d) \n", SerialNum, ClntAdr.sin_port);
	ClientCount--;
}

//===================================================
// RoomValueInit : 방 변수 초기화
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
// InGameValueInit : 인게임 변수 초기화
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
// TimetoSecond : 시간을 초로 치환해서 보낸다.
float CNetWork::TimetoSecond(VOID)
{
	SYSTEMTIME t;

	GetLocalTime(&t);

	return (t.wHour * 3600) + (t.wMinute * 60) + (t.wSecond);
}

//===================================================
// GameTimeLoop : 게임이 시작되고 시간이 흐르게 한다.
int CNetWork::GameTimeLoop(VOID)
{
	float Now;
	// 경과 시간
	int TimeElapse;

	Now = TimetoSecond();

	TimeElapse = Now - StartTime;

	return TimeElapse;
}
