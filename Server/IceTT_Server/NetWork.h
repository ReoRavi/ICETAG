#pragma once

//==================================================
// CNetwork : 네트워크 처리를 담당한다.
// ISingleton - 싱글톤을 상속받아 프로그램 내에서 하나만 존재하는 인스턴스로 만든다.
class CNetWork :
	public ISingleton<CNetWork>
{
public:
	CNetWork();
	virtual ~CNetWork();

public:
	// 서버 소켓, 클라이언트 소켓
	SOCKET hServSock, hClntSock[MAX_CLIENT];
	// 서버의 주소, 클라이언트의 주소
	SOCKADDR_IN ServAdr, ClntAdr;
	// 알림이 오기까지 대기할 시간
	TIMEVAL TimeOut;
	// 데이터 수신, 송신 알림을 받을 소켓 배열을 가진 구조체.
	fd_set fd_Recv, fd_Send;
	// select 함수를 사용하면 원래의 fd_set 구조체가 뒤틀리기 때문에 복사하여 사용한다.
	fd_set cpyRecv, cpySend;
	
	// 패킷 버퍼
	CStream* Buf;
	// 패킷의 길이
	DWORD PacketLength;
	// 패킷 프로토콜 타입
	ePacket_Protocol PacketType;

	// 접속한 클라이언트의 수
	int ClientCount;

	//누가 패킷을 보냇는가
	int SendClientNum;

public:
	// 초기화
	BOOL Initialize(VOID);
	// 메모리 해제
	BOOL	Release(VOID);
	// 메인 루프
	VOID	Loop(VOID);

	// 클라이언트의 접속을 종료한다.
	VOID ClientRelease(int SerialNum);
	// 패킷 프로토콜 처리
	VOID PacketProc(CStream* Buf, ePacket_Protocol ProtocolType);

public :

	//==========================================================================
	//Room
	//
	// 방장의 번호
	int MasterNum;
	// 플레이어를 관리할 배열
	bool bIsPlayer[8];
	// 플레이어의 준비 상태
	bool bIsPlayerReady[8];
	// 플레이어가 모두 준비되었는지 체크함
	bool bIsAllPlayerReady;
	// 플레이어들의 이름
	std::string PlayerName[8];
	// 방 변수 초기화
	void RoomValueInit();
	//==========================================================================

	//==========================================================================
	//InGame
	//
	// 플레이어 X좌표
	int					PlayerXPos[8];
	// 플레이어 Y좌표
	int					PlayerYPos[8];
	// 술래의 번호
	int					TaggerNum;
	// 플레이어가 종료했는가
	bool				bIsPlayerQuit[8];
	// 게임이 시작되어 술래가 결정됬는가
	bool				bIsTaggerON;
	// 게임이 끝났는가
	bool				bIsGameEnd;
	// 플레이어(오리)가 이겼는가
	bool				bIsPlayerWin;
	// 플레이어의 현재 상태 (평소, 얼음, 죽음, 술래)
	eCharacter_State	PlayerState[8];
	// 플레이어의 이동방향
	eCharacter_Direction PlayerDirection[8];
	// 시작 시간
	float StartTime;
	// 인게임 변수 초기화
	void InGameValueInit();
	//==========================================================================
	
	//==========================================================================
	// KeepAlive - 클라이언트의 인터넷 상태를 체크하고, 불안정하면 연결은 끊는다.
	//
	// 쓰레드의 핸들
	HANDLE	m_hKeepThread;
	// 클라이언트의 마지막 KeepAlive 수신을 체크할 시간.
	LARGE_INTEGER			m_CurSendTime[8], m_OldSendTime[8], m_TimeFrequency;
	// 클라이언트들의 하트비트 카운트
	int		m_HeartBeatCount[8];
	//==========================================================================

	// 시간을 초로 치환해서 보낸다.
	float TimetoSecond(VOID);
	// 게임이 시작되고 시간이 흐르게 한다.
	int GameTimeLoop(VOID);
};

