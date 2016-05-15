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
// �ʱ�ȭ
BOOL CNetWork::Initialize(string IP)
{
	WSADATA					wsaData;

	// ������ ���� ���α׷��� �ʱ�ȭ
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
	
	// ���Ͽ� �ּ� �Ҵ�
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(IP.c_str());
	servAddr.sin_port = htons(atoi("1237"));

	// ����
	if (connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
	{
		MessageBox(NULL, "���ͳ� ���¸� Ȯ���Ͻðų�, ������ �����ִ��� Ȯ�����ּ���", "���ӿ���", MB_OK);

		return FALSE;
	}

	// �ۼ��� �˸� ����ü �ʱ�ȭ
	FD_ZERO(&fd_Recv);
	FD_ZERO(&cpyRecv);
	FD_ZERO(&fd_Send);
	FD_ZERO(&cpySend);

	FD_SET(hSocket, &fd_Recv);
	FD_SET(hSocket, &fd_Send);

	// ���� �ɼ� ���
	LINGER Linger;
	Linger.l_onoff = 1;
	Linger.l_linger = 0;

	// ����� ���Ḧ ������� ����
	setsockopt(hSocket, SOL_SOCKET, SO_LINGER, (char*)&Linger, sizeof(Linger));

	// ��Ŷ ���� �ð� ����
	QueryPerformanceCounter(&m_CurTime);
	QueryPerformanceCounter(&m_OldTime);
	QueryPerformanceFrequency(&m_TimeFrequency);

	m_bIsConnected = true;

	return TRUE;
}

//=================================================================
// Loop : ����
VOID CNetWork::Loop()
{
	// �����û�� ����
	if (m_bIsConnected)
	{
		QueryPerformanceCounter(&m_CurTime);

		// �����û�� ���� �� ���� �ð��� ������
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

	// �˸��� �ޱ� �� 0.1�� ����Ѵ�.
	TimeOut.tv_sec = 0.1F;
	TimeOut.tv_usec = 0.1F;

	// ����ü�� ���� ����ϸ� ���� ��Ʋ�� �����Ͽ� ����Ѵ�.
	cpyRecv = fd_Recv;
	cpySend = fd_Send;

	// �˸��� �޴´�.
	int SockResult = select(0, &cpyRecv, &cpySend, 0, &TimeOut);

	if (0 < SockResult)
	{
		// �����������κ��� �˸��� �Դٸ�
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

			// ��Ŷ Ÿ�Կ� ���� ó���Ѵ�.
			switch (PacketType)	
			{
				// ���� ������ ������Ʈ�Ѵ�.
			case ePacket_Protocol::ePacket_RoomDataUpdate:
				CAnalysisPacket::Packet_Analysis_Room_UserUpdate(Buf);

				break;

				// �濡 ������ ���Դ�.
			case ePacket_Protocol::ePacket_Room_UserAttend:
				CAnalysisPacket::Packet_Analysis_Room_UserUpdate(Buf);

				break;

				// Ŭ���̾�Ʈ���� ���� ������ ��û�Ǿ���.
			case ePacket_Protocol::ePacket_Room_GameStart:
				CAnalysisPacket::Packet_Analysis_Room_GameStart(Buf);

				break;

				// �÷��̾���� ���� �غ���� �ʾ� ������ ������ �� ����
			case ePacket_Protocol::ePacket_Room_GameStartFailed:
				CAnalysisPacket::Packet_Analysis_Room_GameStartFailed(Buf);

				break;

				// ������ �����Ѵ�.
			case ePacket_Protocol::ePacket_Room_GameQuit:
				CAnalysisPacket::Packet_Analysis_Room_PlayerQuit(Buf);

				break;

				// �÷��̾�鿡�� �ڽ��� �غ�Ǿ����� �˸���.
			case ePacket_Protocol::ePacket_InGame_PlayerReady:
				CAnalysisPacket::Packet_Analysis_Room_PlayerReady(Buf);

				break;

				// �ΰ��ӿ��� �ʿ��� �÷��̾��� ������ ��� �����Ѵ�.
			case ePacket_Protocol::ePacket_InGame_All:
				CAnalysisPacket::Packet_Analysis_InGame_All(Buf);

				break;

				// ������ ���� �κ�� �����Ѵ�.
			case ePacket_Protocol::ePacket_InGame_ChangetoLobby:
				CAnalysisPacket::Packet_Analysis_InGame_ChangetoLobby(Buf);

				break;

				// Ŭ���̾�Ʈ�� ���� üũ
			case ePacket_Protocol::ePacket_KeepAlive :
				CAnalysisPacket::Packet_Analysis_KeepAlive(Buf);

				break;
			}
		}
	}
}

//=================================================================
// Release : �޸� ����
VOID CNetWork::Release()
{
	closesocket(hSocket);
}
