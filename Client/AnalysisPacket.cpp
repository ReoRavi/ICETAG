#include "stdafx.h"
#include "AnalysisPacket.h"

//==================================================
// Packet_Analysis_Room_UserUpdate 
// 유저의 정보가 업데이트되었다.
BOOL CAnalysisPacket::Packet_Analysis_Room_UserUpdate(CStream* Buf)
{
	int PlayerNameLength[8];

	// 새로운 클라이언트가 들어왔다.
	DataManager->bIsNewClient = true;

	// 클라이언트의 갯수
	Buf->ReadInt(&DataManager->ClientNum);
	// 클라이언트의 인덱스
	Buf->ReadInt(&DataManager->SerialNum);
	// 방장인가
	Buf->ReadBool(&DataManager->bIsMaster);
	// 방장의 번호
	Buf->ReadInt(&DataManager->MasterNum);

	// 플레이어가 접속중인가
	for (int i = 0; i < 8; i++)
	{
		Buf->ReadBool(&DataManager->bIsPlayer[i]);
	}

	// 플레이어의 준비 상태
	for (int i = 0; i < 8; i++)
	{
		Buf->ReadBool(&DataManager->PlayerReadyState[i]);
	}

	// 플레이어 이름의 길이
	for (int i = 0; i < 8; i++)
	{
		Buf->ReadInt(&PlayerNameLength[i]);
	}

	// 플레이어의 이름을 읽는다.
	for (int i = 0; i < 8; i++)
	{
		string str;

		for (int j = 0; j < PlayerNameLength[i]; j++)
		{
			char ch;

			Buf->ReadChar(&ch);

			str += ch;
		}

		DataManager->PlayerName[i] = str;
	}

	return TRUE;
}

//==================================================
// Packet_Analysis_Room_GameStart 
// 게임을 시작한다.
BOOL CAnalysisPacket::Packet_Analysis_Room_GameStart(CStream* Buf)
{
	// 플레이어의 갯수
	Buf->ReadInt(&DataManager->PlayerNum);
	// 플레이어의 번호
	Buf->ReadInt(&DataManager->SerialNum);
	// 술래의 번호
	Buf->ReadInt(&DataManager->TaggerNum);

	// 플레이어의 상태를 갱신한다.
	for (int i = 0; i < 8; i++)
	{
		Buf->ReadCharacterState(&DataManager->m_PlayerState[i]);
	}

	// 게임이 시작되어 인게임으로 씬을 바꾼다.
	SceneMgr->ChangeScene(SceneInfo_InGame);

	return TRUE;
}

//==================================================
// Packet_Analysis_Room_DataUpdate 
// 방의 정보가 업데이트 되었다.
BOOL CAnalysisPacket::Packet_Analysis_Room_DataUpdate(CStream* Buf)
{
	int PlayerNameLength[8];

	// 클라이언트의 갯수
	Buf->ReadInt(&DataManager->ClientNum);
	// 클라이언트의 인덱스
	Buf->ReadInt(&DataManager->SerialNum);
	// 방장인가
	Buf->ReadBool(&DataManager->bIsMaster);
	// 방장의 인덱스
	Buf->ReadInt(&DataManager->MasterNum);

	// 플레이어가 접속중인가
	for (int i = 0; i < 8; i++)
	{
		Buf->ReadBool(&DataManager->bIsPlayer[i]);
	}

	// 플레이어가 준비중인가
	for (int i = 0; i < 8; i++)
	{
		Buf->ReadBool(&DataManager->PlayerReadyState[i]);
	}

	// 플레이어 이름의 길이를 받는다.
	for (int i = 0; i < 8; i++)
	{
		Buf->ReadInt(&PlayerNameLength[i]);
	}

	//플레이어 이름을 받는다.
	for (int i = 0; i < 8; i++)
	{
		string str;

		for (int j = 0; j < PlayerNameLength[i]; j++)
		{
			char ch;

			Buf->ReadChar(&ch);

			str += ch;
		}

		DataManager->PlayerName[i] = str;
	}

	return TRUE;
}

//==================================================
// Packet_Analysis_Room_PlayerReady 
// 플레이어 준비상태가 갱신되었다.
BOOL CAnalysisPacket::Packet_Analysis_Room_PlayerReady(CStream* Buf)
{
	// 준비상태를 갱신한 플레이어가 있다.
	DataManager->bIsReadyClient = TRUE;
	// 준비상태를 갱신한 클라이언트 인덱스
	Buf->ReadInt(&DataManager->ReadyClientNum);

	return TRUE;
}

//==================================================
// Packet_Analysis_Room_GameStartFailed 
// 게임 시작에 실패했다.
BOOL CAnalysisPacket::Packet_Analysis_Room_GameStartFailed(CStream* Buf)
{
	// 게임 시작에 실패함
	DataManager->bIsGameStartFailed = TRUE;

	return TRUE;
}

//==================================================
// Packet_Analysis_Room_PlayerQuit 
// 방에서 유저가 종료했다.
BOOL CAnalysisPacket::Packet_Analysis_Room_PlayerQuit(CStream* Buf)
{
	int QuitPlayerNum;
	int SerialNum = DataManager->SerialNum;

	// 종료한 플레이어의 인덱스를 얻는다.
	Buf->ReadInt(&QuitPlayerNum);

	// 플레이어 종료 처리
	DataManager->QuitPlayerNumber = QuitPlayerNum;

	// 자신이 종료한 것이라면
	if (DataManager->QuitPlayerNumber == DataManager->SerialNum)
	{
		// 타이틀로 돌아간다.
		SceneMgr->ChangeScene(Scene_Info::SceneInfo_Title);
		Buf->ClearRecvBuffer();
		Buf->ResetRecvPoint();

		Network->Release();
	}
	// 다른 플레이어가 종료했음
	else
	{
		DataManager->bIsOhterPlayerQuit = TRUE;
	}

	return TRUE;
}

//==================================================
// Packet_Analysis_InGame_All 
// 인게임의 모든 정보를 업데이트한다.
BOOL CAnalysisPacket::Packet_Analysis_InGame_All(CStream* Buf)
{
	// X좌표
	for (int i = 0; i < 8; i++)
	{
		Buf->ReadInt(&DataManager->PlayerXPos[i]);
	}

	// Y좌표
	for (int i = 0; i < 8; i++)
	{
		Buf->ReadInt(&DataManager->PlayerYPos[i]);
	}

	// 클라이언트 종료 상태
	for (int i = 0; i < 8; i++)
	{
		Buf->ReadBool(&DataManager->bIsClientQuit[i]);
	}

	int t;

	// 시간
	Buf->ReadInt(&DataManager->Time[0]);
	Buf->ReadInt(&t);

	// 분
	DataManager->Time[1] = t / 10;
	// 초
	DataManager->Time[2] = t % 10;

	// 플레이어의 상태
	for (int i = 0; i < 8; i++)
	{
		Buf->ReadCharacterState(&DataManager->m_PlayerState[i]);
	}

	// 게임이 끝났는가
	Buf->ReadBool(&DataManager->bIsGameEnd);
	// 승리 상태
	Buf->ReadBool(&DataManager->bIsPlayerWin);

	// 플레이어의 방향
	for (int i = 0; i < 8; i++)
	{
		Buf->ReadCharacterDirection(&DataManager->PlayerDirection[i]);
	}

	// 플레이어가 접속중인가.
	for (int i = 0; i < 8; i++)
	{
		Buf->ReadBool(&DataManager->bIsPlayer[i]);
	}

	return TRUE;
}

//==================================================
// Packet_Analysis_InGame_ChangetoLobby 
// 인게임에서 게임이 끝나 로비로 이동한다.
BOOL CAnalysisPacket::Packet_Analysis_InGame_ChangetoLobby(CStream* Buf)
{
	// 플레이어가 접속중인가
	for (int i = 0; i < 8; i++)
	{
		Buf->ReadBool(&DataManager->bIsPlayer[i]);
	}

	// 플레이어의 준비 상태
	for (int i = 0; i < 8; i++)
	{
		Buf->ReadBool(&DataManager->PlayerReadyState[i]);
	}

	// 게임이 끝나 방으로 씬을 바꾼다.
	SceneMgr->ChangeScene(SceneInfo_Room);

	return TRUE;
}

//==================================================
// Packet_Analysis_KeepAlive 
// 클라이언트가 제데로 연결되어 있는지 체크한다.
BOOL CAnalysisPacket::Packet_Analysis_KeepAlive(CStream* Buf)
{
	CStream* Buff = new CStream();

	printf("KeepAlive\n");

	QueryPerformanceCounter(&Network->m_OldTime);

	CMakePacket::Packet_Send_KeepAlive(Buff);
	// 서버에게 하트비트에 대한 응답을 해준다.
	send(Network->hSocket, Buff->m_SendBuffer, Buff->m_BufferWritePoint, 0);

	return TRUE;
}