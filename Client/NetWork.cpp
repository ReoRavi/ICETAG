#include "stdafx.h"
#include "NetWork.h"

CNetWork::CNetWork()
{
	PacketLength = 0;
}

CNetWork::~CNetWork()
{
}

//======================================
// Initialize
// 초기화
BOOL CNetWork::Initialize(string IP)
{
	WSADATA					wsaData;

	// 윈도우 소켓 프로그래밍 초기화
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		MessageBox(NULL, "NewWork Initialize Failed!\n\nError::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0", "ERROR", MB_ICONERROR);
		PostQuitMessage(0);
		return FALSE;
	}

	hSocket = socket(PF_INET, SOCK_STREAM, 0);

	if (hSocket == INVALID_SOCKET)
	{
		MessageBox(NULL, "NewWork Initialize Failed!\n\nError::hSocket == INVALID_SOCKE", "ERROR", MB_ICONERROR);
		PostQuitMessage(0);
		return FALSE;
	}
	 
	ZeroMemory(&servAddr, 0, sizeof(servAddr));
	
	// 소켓에 주소 할당
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(IP.c_str());
	servAddr.sin_port = htons(atoi("1237"));

	// 연결
	if (connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
	{
		MessageBox(NULL, "인터넷 상태를 확인하시거나, 서버가 열려있는지 확인해주세요", "접속오류", MB_OK);

		return FALSE;
	}

	// 송수신 알림 구조체 초기화
	FD_ZERO(&fd_Recv);
	FD_ZERO(&cpyRecv);
	FD_ZERO(&fd_Send);
	FD_ZERO(&cpySend);

	FD_SET(hSocket, &fd_Recv);
	FD_SET(hSocket, &fd_Send);

	// 링거 옵션 사용
	LINGER Linger;
	Linger.l_onoff = 1;
	Linger.l_linger = 0;

	// 우아한 종료를 사용하지 않음
	setsockopt(hSocket, SOL_SOCKET, SO_LINGER, (char*)&Linger, sizeof(Linger));

	// 패킷 지연 시간 설정
	QueryPerformanceCounter(&m_CurTime);
	QueryPerformanceCounter(&m_OldTime);
	QueryPerformanceFrequency(&m_TimeFrequency);

	m_bIsConnected = true;

	return TRUE;
}

//=================================================================
// Loop : 루프
VOID CNetWork::Loop()
{
	// 연결요청을 보냄
	if (m_bIsConnected)
	{
		QueryPerformanceCounter(&m_CurTime);

		// 연결요청을 보낸 후 일정 시간이 지났음
		if ((m_CurTime.QuadPart - m_OldTime.QuadPart) / (m_TimeFrequency.QuadPart / 1000) > 30000)
		{
			QueryPerformanceCounter(&m_CurTime);
			QueryPerformanceCounter(&m_OldTime);
			m_bIsConnected = false;
			printf("Server Condition Bad....\n");
			Release();
			SceneMgr->ChangeScene(Scene_Info::SceneInfo_Title);
		}
	}

	// 알림을 받기 전 0.1초 대기한다.
	TimeOut.tv_sec = 0.1F;
	TimeOut.tv_usec = 0.1F;

	// 구조체를 직접 사용하면 값이 뒤틀려 복사하여 사용한다.
	cpyRecv = fd_Recv;
	cpySend = fd_Send;

	// 알림을 받는다.
	int SockResult = select(0, &cpyRecv, &cpySend, 0, &TimeOut);

	if (0 < SockResult)
	{
		// 서버소켓으로부터 알림이 왔다면
		if (FD_ISSET(hSocket, &cpyRecv))
		{
			CStream* Buf = new CStream();

			recv(hSocket, Buf->m_RecvBuffer, BUF_SIZE, 0);

			Buf->ReadProtocol(&PacketType);

			Buf->ReadDWORD(&PacketLength);

			try
			{
				if (PacketType == ePacket_NULL)
				{
					throw ERROR_NULLPACKETRECEIVED;
				}
			}
			catch (DWORD eError)
			{
				printf("Error Code : %d", eError);
			}

			// 패킷 타입에 따라 처리한다.
			switch (PacketType)	
			{
				// 방의 정보를 업데이트한다.
			case ePacket_Protocol::ePacket_RoomDataUpdate:
				CAnalysisPacket::Packet_Analysis_Room_UserUpdate(Buf);

				break;

				// 방에 유저가 들어왔다.
			case ePacket_Protocol::ePacket_Room_UserAttend:
				CAnalysisPacket::Packet_Analysis_Room_UserUpdate(Buf);

				break;

				// 클라이언트에서 게임 시작이 요청되었다.
			case ePacket_Protocol::ePacket_Room_GameStart:
				CAnalysisPacket::Packet_Analysis_Room_GameStart(Buf);

				break;

				// 플레이어들이 전부 준비되지 않아 게임을 시작할 수 없다
			case ePacket_Protocol::ePacket_Room_GameStartFailed:
				CAnalysisPacket::Packet_Analysis_Room_GameStartFailed(Buf);

				break;

				// 게임을 종료한다.
			case ePacket_Protocol::ePacket_Room_GameQuit:
				CAnalysisPacket::Packet_Analysis_Room_PlayerQuit(Buf);

				break;

				// 플레이어들에게 자신이 준비되었음을 알린다.
			case ePacket_Protocol::ePacket_InGame_PlayerReady:
				CAnalysisPacket::Packet_Analysis_Room_PlayerReady(Buf);

				break;

				// 인게임에서 필요한 플레이어의 정보를 모두 전송한다.
			case ePacket_Protocol::ePacket_InGame_All:
				CAnalysisPacket::Packet_Analysis_InGame_All(Buf);

				break;

				// 게임이 끝나 로비로 복귀한다.
			case ePacket_Protocol::ePacket_InGame_ChangetoLobby:
				CAnalysisPacket::Packet_Analysis_InGame_ChangetoLobby(Buf);

				break;

				// 클라이언트의 상태 체크
			case ePacket_Protocol::ePacket_KeepAlive :
				CAnalysisPacket::Packet_Analysis_KeepAlive(Buf);

				break;
			}
		}
	}
}

//=================================================================
// Release : 메모리 해제
VOID CNetWork::Release()
{
	closesocket(hSocket);
}
