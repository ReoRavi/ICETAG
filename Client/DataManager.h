#pragma once

//=============================================
// CDataManager : 공용 변수들을 포함하는 객체.
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
	// 플레이어가 살아있는가
	bool bIsPlayerAlive[8];
	// 나간 클라이언트가 있는가
	bool bIsClientQuit[8];
	// 술래가 결정되고 게임이 시작됨
	bool bIsIceTagStart;
	// 현재 클라이언트의 수
	int ClientNum;
	// 내 클라이언트의 고유 번호
	int SerialNum;
	// 플레이어의 수
	int PlayerNum;
	// 다른 플레이어의 좌표
	int PlayerXPos[8], PlayerYPos[8];
	// 시간
	// 0 - 분 1, 2 - 초
	int Time[3];
	// 술래 번호
	int TaggerNum;
	// 플레이어들의 상태
	eCharacter_State	m_PlayerState[8];
	// 플레이어들의 방향
	eCharacter_Direction PlayerDirection[8];
	// 게임중인가
	bool bIsGameEnd;
	// 플레이어 승리 체크
	bool bIsPlayerWin;

	//========================================
	// Scene - Room
	//
	// 새로운 클라이언트가 들어왔음을 알림.
	bool bIsNewClient;
	// 플레이어들의 상태
	bool bIsPlayer[8];
	// 모든 클라이언트가 준비되었나.
	bool bIsAllClientReady;
	// 내가 방장인가
	bool bIsMaster;
	// 준비된 클라이언트가 있다.
	bool bIsReadyClient;
	// 게임 시작이 실패되었다.
	bool bIsGameStartFailed;
	// 
	bool bIsOhterPlayerQuit;
	// 플레이어들의 준비 여부
	bool PlayerReadyState[8];
	// 준비된 클라이언트의 번호
	int ReadyClientNum;
	// 방장의 번호
	int MasterNum;
	// 
	int QuitPlayerNumber;
	// .플레이어들의 이름
	std::string PlayerName[8];

	std::string t_PlayerName;

	//========================================
	// Scene - ALL
	//
	// 플레이어 종료.
	bool bIsQuit;
	// 게임 중
	bool bIsGameRun;

};

#define DataManager CDataManager::GetInstance()