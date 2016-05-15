#pragma once

// 에러
const DWORD ERROR_NULLPACKETRECEIVED = 1;

//=============================================
// CNetWork : 네트워크 처리를 담당하는 클래스.
class CNetWork :
	public ISingleton <CNetWork>
{
public :
	CNetWork();
	virtual ~CNetWork();

public :
	// 서버 소켓
	SOCKET					hSocket;
	// 서버 주소
	SOCKADDR_IN		servAddr;
	// 송수신 구조체
	fd_set							fd_Recv, fd_Send;
	// 복사 하여 사용할 송수신 구조체
	fd_set							cpyRecv, cpySend;
	// 알림을 기다리는 시간
	TIMEVAL					TimeOut;
	// 패킷 지연 시간
	LARGE_INTEGER	m_CurTime, m_OldTime, m_TimeFrequency;
	// 연결됬는가
	bool								m_bIsConnected;
	// 패킷의 길이
	DWORD PacketLength;
	// 패킷 타입
	ePacket_Protocol PacketType;

public :
	// 초기화
	BOOL Initialize(string IP);
	// 루프
	VOID Loop();
	// 메모리 해제
	VOID Release();
};

#define Network CNetWork::GetInstance()

