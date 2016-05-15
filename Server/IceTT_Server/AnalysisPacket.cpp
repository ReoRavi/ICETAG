#include "stdafx.h"
#include "AnalysisPacket.h"

CAnalysisPacket::CAnalysisPacket()
{
}


CAnalysisPacket::~CAnalysisPacket()
{
}

//===========================================================
// Packet_Analysis_ConnectToRoom_ConnectAccept : 클라이언트에서 방에 접속 요청을 했다.
BOOL CAnalysisPacket::Packet_Analysis_ConnectToRoom_ConnectAccept(CStream* Buf, CNetWork* NetWork)
{
	// 이름 길이
	int Length;
	// 플레이어 인덱스
	int TempSerialNum;
	// 플레이어가 방장인가
	bool bIsMaster;
	char ch;
	// 이름
	std::string str;

	// 플레이어 인덱스 할당
	TempSerialNum = NetWork->SendClientNum;

	// 이름의 길이를 받아온다.
	Buf->ReadInt(&Length);

	// 이름을 읽어온다.
	for (int i = 0; i < Length; i++)
	{
		Buf->ReadChar(&ch);

		str += ch;
	}

	// 이름 할당
	NetWork->PlayerName[NetWork->SendClientNum] = str;

	printf("%s\n", str);

	// 플레이어가 들어왔음으로 모든 플레이어들에게 유저 정보를 업데이트해서 보낸다.
	for (int i = 0; i < MAX_CLIENT; i++)
	{
		if (NetWork->bIsPlayer[i])
		{
			if (NetWork->MasterNum == i)
				bIsMaster = true;
			else
				bIsMaster = false;

			CMakePacket::Packet_Send_Room_UserUpdate(Buf, NetWork->ClientCount, i, bIsMaster, NetWork->MasterNum, NetWork->bIsPlayer, NetWork->bIsPlayerReady, NetWork->PlayerName);
			send(NetWork->hClntSock[i], Buf->m_SendBuffer, Buf->m_BufferWritePoint, 0);
			Buf->ClearSendBuffer();
			Buf->ResetSendPoint();
		}
	}

	return TRUE;
}

//===========================================================
// Packet_Analysis_Room_GameStart : 클라이언트에서 게임 시작을 요청했다.
// 모든 클라이언트들에게 씬을 전환할것을 요청하는 패킷을 보낸다.
BOOL CAnalysisPacket::Packet_Analysis_Room_GameStart(CStream* Buf, CNetWork* NetWork)
{
	// 술래를 랜덤으로 설정한다.
	int TaggerNum = rand() % NetWork->ClientCount;

	// 모든 플레이어가 준비되었고, 플레이어가 최소 3명이라면
	if (NetWork->bIsAllPlayerReady && NetWork->ClientCount >= 3)
	{
		// 게임 시작 패킷을 보낸다.
		for (int i = 0; i < MAX_CLIENT; i++)
		{
			if (NetWork->bIsPlayer[i])
			{
				CMakePacket::Packet_Send_Room_GameStart(Buf, NetWork->ClientCount, i, TaggerNum, NetWork->PlayerState);
				send(NetWork->hClntSock[i], Buf->m_SendBuffer, Buf->m_BufferWritePoint, 0);
				Buf->ResetSendPoint();
				Buf->ClearSendBuffer();

				NetWork->InGameValueInit();
				NetWork->TaggerNum = TaggerNum;
				NetWork->StartTime = NetWork->TimetoSecond();
			}
		}
	}
	else
	{
		for (int i = 0; i < MAX_CLIENT; i++)
		{
			// 게임시작 실패 패킷을 보낸다.
			if (NetWork->bIsPlayer[i])
			{
				CMakePacket::Packet_Send_Room_GameStartFailed(Buf);
				send(NetWork->hClntSock[i], Buf->m_SendBuffer, Buf->m_BufferWritePoint, 0);
				Buf->ResetSendPoint();
				Buf->ClearSendBuffer();
			}
		}
	}


	printf("Packet- GameStart\n");

	return TRUE;
}

//===========================================================
// Packet_Analysis_Room_DataUpdate : 방 데이터 업데이트
BOOL CAnalysisPacket::Packet_Analysis_Room_DataUpdate(CStream* Buf, CNetWork* NetWork)
{
	// 방장인지
	bool bIsMaster;
	// 플레이어의 인덱스
	int SerialNum;

	// 패킷을 보낸 플레이어의 인덱스를 읽는다.
	Buf->ReadInt(&SerialNum);

	// 방장인지 알아낸다.
	if (NetWork->MasterNum == SerialNum)
		bIsMaster = true;
	else
		bIsMaster = false;

	// 방 데이터를 업데이트하는 패킷을 보낸다.
	CMakePacket::Packet_Send_Room_UserUpdate(Buf, NetWork->ClientCount, SerialNum, bIsMaster, NetWork->MasterNum, NetWork->bIsPlayer, NetWork->bIsPlayerReady, NetWork->PlayerName);
	send(NetWork->hClntSock[SerialNum], Buf->m_SendBuffer, Buf->m_BufferWritePoint, 0);
	Buf->ClearSendBuffer();
	Buf->ResetSendPoint();

	return TRUE;
}

//===========================================================
// Packet_Analysis_Room_PlayerReady : 클라이언트가 준비되었음을 알렸다.
BOOL CAnalysisPacket::Packet_Analysis_Room_PlayerReady(CStream* Buf, CNetWork* NetWork)
{
	// 패킷을 보낸 플레이어의 인덱스
	int SerialNum;
	// 클라이언트의 수
	int ClientNum;

	// 플레이어의 인덱스를 읽는다,
	Buf->ReadInt(&SerialNum);
	// 클라이언트의 수를 읽는다.
	Buf->ReadInt(&ClientNum);

	// 플레이어의 준비 상태를 반전시킨다.
	NetWork->bIsPlayerReady[SerialNum] = !NetWork->bIsPlayerReady[SerialNum];

	int ReadyCheckCount = 0;

	// 준비된 플레이어들의 숫자를 구한다.
	for (int i = 0; i < MAX_CLIENT; i++)
	{
		if (NetWork->bIsPlayer[i])
		{
			if (NetWork->bIsPlayerReady[i])
			{
				ReadyCheckCount++;
			}
		}
	}

	// 방장을 제외한 모든 플레이어가 준비되었다.
	if ((ClientNum - 1) == ReadyCheckCount)
	{
		NetWork->bIsAllPlayerReady = TRUE;
	}
	else
	{
		NetWork->bIsAllPlayerReady = FALSE;
	}

	// 플레이어 준비 패킷을 보낸다.
	CMakePacket::Packet_Send_Room_PlayerReady(Buf, NetWork, SerialNum);
	for (int i = 0; i < MAX_CLIENT; i++)
	{
		if (NetWork->bIsPlayer[i])
		{
			send(NetWork->hClntSock[i], Buf->m_SendBuffer, Buf->m_BufferWritePoint, 0);
		}
	}


	Buf->ResetSendPoint();
	Buf->ClearSendBuffer();

	printf("Packet- PlayerReady\n");

	return TRUE;
}

//===========================================================
// Packet_Analysis_Room_GameQuit : 방에서 클라이언트와의 접속을 끊는다.
BOOL CAnalysisPacket::Packet_Analysis_Room_GameQuit(CStream* Buf, CNetWork* NetWork)
{
	// 모든 플레이어들에게 패킷을 보낸 플레이어가 종료했다고 알린다.
	for (int i = 0; i < MAX_CLIENT; i++)
	{
		if (NetWork->bIsPlayer[i])
		{
			CMakePacket::Packet_Send_Room_Exit(Buf, NetWork->SendClientNum);
			send(NetWork->hClntSock[i], Buf->m_SendBuffer, Buf->m_BufferWritePoint, 0);
		}
	}

	Buf->ResetSendPoint();
	Buf->ClearSendBuffer();

	// 패킷을 보낸 플레이어를 종료시킨다.
	NetWork->ClientRelease(NetWork->SendClientNum);

	printf("Packet- GameQuit\n");

	return TRUE;
}

//===========================================================
// Packet_Analysis_InGame_All : 인게임에서 필요한 모든 플레이어의 정보를 받는다.
BOOL CAnalysisPacket::Packet_Analysis_InGame_All(CStream* Buf, CNetWork* NetWork)
{
	// x좌표, y좌표
	int TempXPos, TempYPos;
	// 플레이어의 인덱스
	int TempSerialNum;
	// 종료했는가
	bool bIsQuit;

	// 플레이어의 인덱스를 읽어온다.
	Buf->ReadInt(&TempSerialNum);
	// x좌표를 읽는다.
	Buf->ReadInt(&TempXPos);
	// y좌표를 읽는다.
	Buf->ReadInt(&TempYPos);
	// 종료했는지 여부를 읽는다.
	Buf->ReadBool(&bIsQuit);
	// 플레이어의 상태를 읽는다.
	Buf->ReadCharacterState(&NetWork->PlayerState[TempSerialNum]);
	// 플레이어의 방향을 읽는다.
	Buf->ReadCharacterDirection(&NetWork->PlayerDirection[TempSerialNum]);

	NetWork->PlayerXPos[TempSerialNum] = TempXPos;
	NetWork->PlayerYPos[TempSerialNum] = TempYPos;
	NetWork->bIsPlayerQuit[TempSerialNum] = bIsQuit;

	if (NetWork->bIsPlayerQuit[TempSerialNum])
	{
		NetWork->ClientRelease(TempSerialNum);
	}

	//===================================================================================================
	// 술래와 플레이어간의 충돌 처리
	//
	for (int i = 0; i < MAX_CLIENT; i++)
	{
		if (NetWork->bIsPlayer[i])
		{
			if (NetWork->bIsTaggerON)
			{
				if (TempSerialNum != i)
				{
					if (i != NetWork->TaggerNum)
					{
						if ((NetWork->PlayerXPos[TempSerialNum] - 32 <= NetWork->PlayerXPos[i]) &&
							(NetWork->PlayerXPos[TempSerialNum] + 32 >= NetWork->PlayerXPos[i]) &&
							(NetWork->PlayerYPos[TempSerialNum] - 32 <= NetWork->PlayerYPos[i]) &&
							(NetWork->PlayerYPos[TempSerialNum] + 32 >= NetWork->PlayerYPos[i]))
						{
							if (NetWork->PlayerState[TempSerialNum] == eCharacter_State::eCharacter_Freeze)
							{
								NetWork->PlayerState[TempSerialNum] = eCharacter_State::eCharacter_Idle;
							}

						}

					}
					else if (NetWork->TaggerNum == i)
					{
						if (TempSerialNum != NetWork->TaggerNum)
						{
							if ((NetWork->PlayerXPos[TempSerialNum] - 32 <= NetWork->PlayerXPos[i]) &&
								(NetWork->PlayerXPos[TempSerialNum] + 32 >= NetWork->PlayerXPos[i]) &&
								(NetWork->PlayerYPos[TempSerialNum] - 32 <= NetWork->PlayerYPos[i]) &&
								(NetWork->PlayerYPos[TempSerialNum] + 32 >= NetWork->PlayerYPos[i]))
							{
								if (NetWork->PlayerState[TempSerialNum] == eCharacter_State::eCharacter_Idle)
								{
									NetWork->PlayerState[TempSerialNum] = eCharacter_State::eCharacter_Dead;
								}
							}
						}
					}
				}
			}
			else
			{
				if (TempSerialNum != i)
				{
					if ((NetWork->PlayerXPos[TempSerialNum] - 32 <= NetWork->PlayerXPos[i]) &&
						(NetWork->PlayerXPos[TempSerialNum] + 32 >= NetWork->PlayerXPos[i]) &&
						(NetWork->PlayerYPos[TempSerialNum] - 32 <= NetWork->PlayerYPos[i]) &&
						(NetWork->PlayerYPos[TempSerialNum] + 32 >= NetWork->PlayerYPos[i]))
					{
						if (NetWork->PlayerState[TempSerialNum] == eCharacter_State::eCharacter_Freeze)
						{
							NetWork->PlayerState[TempSerialNum] = eCharacter_State::eCharacter_Idle;
						}
					}
				}
			}
		}
	}
	//===================================================================================================

	//===================================================================================================
	// 술래의 승리 체크
	//
	int FreezeCount = 0;
	int DeadCount = 0;
	int TaggerCount = 0;

	for (int i = 0; i < MAX_CLIENT; i++)
	{
		if (NetWork->bIsPlayer[i])
		{
			if (NetWork->PlayerState[i] == eCharacter_State::eCharacter_Freeze)
			{
				FreezeCount++;
			}

			if (NetWork->PlayerState[i] == eCharacter_State::eCharacter_Dead)
			{
				DeadCount++;
			}

			if (NetWork->PlayerState[i] == eCharacter_State::eCharacter_Tagger)
			{
				TaggerCount++;
			}
		}
	}

	// 모두가 얼어서 게임을 패배했다.
	if (NetWork->ClientCount - TaggerCount == FreezeCount + DeadCount)
	{
		printf("ALL FREEZE\n");
		NetWork->bIsGameEnd = true;
		NetWork->bIsPlayerWin = false;
	}
	//===================================================================================================

	if (NetWork->bIsGameEnd)
	{
		NetWork->RoomValueInit();
	}

	//===================================================================================================
	// 시간 관련 처리
	//
	int Min;
	int Sec;

	Min = (MAXTIME - NetWork->GameTimeLoop()) / 60;
	Sec = (MAXTIME - NetWork->GameTimeLoop()) % 60;

	if (Min == 0 && Sec == 1)
	{
		printf("Time Over\n");
		NetWork->bIsGameEnd = true;
		NetWork->bIsPlayerWin = true;
	}

	if (Min <= 2)
	{
		NetWork->PlayerState[NetWork->TaggerNum] = eCharacter_State::eCharacter_Tagger;
		NetWork->bIsTaggerON = true;
	}
	//===================================================================================================

	Buf->ResetSendPoint();
	Buf->ClearSendBuffer();

	// 인게임의 정보를 포함한 패킷을 보낸다.
	CMakePacket::Packet_Send_InGame_All(Buf, NetWork, NetWork->PlayerXPos, NetWork->PlayerYPos, NetWork->bIsPlayerQuit, Min, Sec, NetWork->PlayerState, NetWork->bIsGameEnd, NetWork->bIsPlayerWin, NetWork->PlayerDirection);
	send(NetWork->hClntSock[TempSerialNum], Buf->m_SendBuffer, Buf->m_BufferWritePoint, 0);

	Buf->ResetSendPoint();
	Buf->ClearSendBuffer();

	return TRUE;
}

//===========================================================
// Packet_Analysis_InGame_ChangetoLobby : 클라이언트가 결과창을 확인하고 로비로 돌아간다.
BOOL CAnalysisPacket::Packet_Analysis_InGame_ChangetoLobby(CStream* Buf, CNetWork* NetWork)
{
	// 패킷을 보낸 플레이어의 인덱스
	int TempSerialNum;

	// 플레이어의 인덱스를 읽는다.
	Buf->ReadInt(&TempSerialNum);

	// 로비로 돌아가는 패킷을 보낸다.
	CMakePacket::Packet_Send_InGame_ChangetoLobby(Buf, NetWork->bIsPlayer, NetWork->bIsPlayerReady);
	send(NetWork->hClntSock[TempSerialNum], Buf->m_SendBuffer, Buf->m_BufferWritePoint, 0);

	Buf->ResetSendPoint();
	Buf->ClearSendBuffer();

	return TRUE;
}

//===========================================================
// Packet_Analysis_KeepAlive : 클라이언트가 살아있는지 체크한다.
BOOL CAnalysisPacket::Packet_Analysis_KeepAlive(CStream* Buf, CNetWork* NetWork)
{
	// 클라이언트가 하트비트 체크에 응답하여 하트비트 카운트를 0으로 돌렸다.
	NetWork->m_HeartBeatCount[NetWork->SendClientNum] = 0;

	printf("Client to Message : KeepAlive\n");

	return TRUE;
}