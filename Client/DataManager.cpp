#include "stdafx.h"
#include "DataManager.h"


CDataManager::CDataManager()
{
}


CDataManager::~CDataManager()
{
}
//============================================
// Initialize : √ ±‚»≠
VOID CDataManager::Initialize(VOID)
{
	//========================================
	// Scene - InGame
	ZeroMemory(bIsPlayerAlive, sizeof(bIsPlayerAlive));
	ZeroMemory(bIsClientQuit, sizeof(bIsClientQuit));
	bIsIceTagStart = false;
	ClientNum = 0;
	SerialNum = 0;
	PlayerNum = 0;
	ZeroMemory(PlayerXPos, sizeof(PlayerXPos));
	ZeroMemory(PlayerYPos, sizeof(PlayerYPos));
	ZeroMemory(Time, sizeof(Time));
	Time[0] = 9;
	TaggerNum = 0;
	bIsGameEnd = false;
	bIsPlayerWin = false;

	//========================================
	// Scene - Room
	ZeroMemory(bIsPlayer, sizeof(bIsPlayer));
	bIsNewClient = false;
	bIsAllClientReady = false;
	bIsMaster = false;
	bIsReadyClient = false;
	bIsGameStartFailed = false;
	bIsOhterPlayerQuit = false;
	ZeroMemory(PlayerReadyState, sizeof(PlayerReadyState));
	ReadyClientNum = 0;
	MasterNum = 0;
	QuitPlayerNumber = 0;


	//========================================
	// Scene - ALL
	bIsQuit = FALSE;
	bIsGameRun = TRUE;
}
