#include "stdafx.h"
#include "AnalysisPacket.h"

CAnalysisPacket::CAnalysisPacket()
{
}


CAnalysisPacket::~CAnalysisPacket()
{
}

//===========================================================
// Packet_Analysis_ConnectToRoom_ConnectAccept : Ŭ���̾�Ʈ���� �濡 ���� ��û�� �ߴ�.
BOOL CAnalysisPacket::Packet_Analysis_ConnectToRoom_ConnectAccept(CStream* Buf, CNetWork* NetWork)
{
	// �̸� ����
	int Length;
	// �÷��̾� �ε���
	int TempSerialNum;
	// �÷��̾ �����ΰ�
	bool bIsMaster;
	char ch;
	// �̸�
	std::string str;

	// �÷��̾� �ε��� �Ҵ�
	TempSerialNum = NetWork->SendClientNum;

	// �̸��� ���̸� �޾ƿ´�.
	Buf->ReadInt(&Length);

	// �̸��� �о�´�.
	for (int i = 0; i < Length; i++)
	{
		Buf->ReadChar(&ch);

		str += ch;
	}

	// �̸� �Ҵ�
	NetWork->PlayerName[NetWork->SendClientNum] = str;

	printf("%s\n", str);

	// �÷��̾ ���������� ��� �÷��̾�鿡�� ���� ������ ������Ʈ�ؼ� ������.
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
// Packet_Analysis_Room_GameStart : Ŭ���̾�Ʈ���� ���� ������ ��û�ߴ�.
// ��� Ŭ���̾�Ʈ�鿡�� ���� ��ȯ�Ұ��� ��û�ϴ� ��Ŷ�� ������.
BOOL CAnalysisPacket::Packet_Analysis_Room_GameStart(CStream* Buf, CNetWork* NetWork)
{
	// ������ �������� �����Ѵ�.
	int TaggerNum = rand() % NetWork->ClientCount;

	// ��� �÷��̾ �غ�Ǿ���, �÷��̾ �ּ� 3���̶��
	if (NetWork->bIsAllPlayerReady && NetWork->ClientCount >= 3)
	{
		// ���� ���� ��Ŷ�� ������.
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
			// ���ӽ��� ���� ��Ŷ�� ������.
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
// Packet_Analysis_Room_DataUpdate : �� ������ ������Ʈ
BOOL CAnalysisPacket::Packet_Analysis_Room_DataUpdate(CStream* Buf, CNetWork* NetWork)
{
	// ��������
	bool bIsMaster;
	// �÷��̾��� �ε���
	int SerialNum;

	// ��Ŷ�� ���� �÷��̾��� �ε����� �д´�.
	Buf->ReadInt(&SerialNum);

	// �������� �˾Ƴ���.
	if (NetWork->MasterNum == SerialNum)
		bIsMaster = true;
	else
		bIsMaster = false;

	// �� �����͸� ������Ʈ�ϴ� ��Ŷ�� ������.
	CMakePacket::Packet_Send_Room_UserUpdate(Buf, NetWork->ClientCount, SerialNum, bIsMaster, NetWork->MasterNum, NetWork->bIsPlayer, NetWork->bIsPlayerReady, NetWork->PlayerName);
	send(NetWork->hClntSock[SerialNum], Buf->m_SendBuffer, Buf->m_BufferWritePoint, 0);
	Buf->ClearSendBuffer();
	Buf->ResetSendPoint();

	return TRUE;
}

//===========================================================
// Packet_Analysis_Room_PlayerReady : Ŭ���̾�Ʈ�� �غ�Ǿ����� �˷ȴ�.
BOOL CAnalysisPacket::Packet_Analysis_Room_PlayerReady(CStream* Buf, CNetWork* NetWork)
{
	// ��Ŷ�� ���� �÷��̾��� �ε���
	int SerialNum;
	// Ŭ���̾�Ʈ�� ��
	int ClientNum;

	// �÷��̾��� �ε����� �д´�,
	Buf->ReadInt(&SerialNum);
	// Ŭ���̾�Ʈ�� ���� �д´�.
	Buf->ReadInt(&ClientNum);

	// �÷��̾��� �غ� ���¸� ������Ų��.
	NetWork->bIsPlayerReady[SerialNum] = !NetWork->bIsPlayerReady[SerialNum];

	int ReadyCheckCount = 0;

	// �غ�� �÷��̾���� ���ڸ� ���Ѵ�.
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

	// ������ ������ ��� �÷��̾ �غ�Ǿ���.
	if ((ClientNum - 1) == ReadyCheckCount)
	{
		NetWork->bIsAllPlayerReady = TRUE;
	}
	else
	{
		NetWork->bIsAllPlayerReady = FALSE;
	}

	// �÷��̾� �غ� ��Ŷ�� ������.
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
// Packet_Analysis_Room_GameQuit : �濡�� Ŭ���̾�Ʈ���� ������ ���´�.
BOOL CAnalysisPacket::Packet_Analysis_Room_GameQuit(CStream* Buf, CNetWork* NetWork)
{
	// ��� �÷��̾�鿡�� ��Ŷ�� ���� �÷��̾ �����ߴٰ� �˸���.
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

	// ��Ŷ�� ���� �÷��̾ �����Ų��.
	NetWork->ClientRelease(NetWork->SendClientNum);

	printf("Packet- GameQuit\n");

	return TRUE;
}

//===========================================================
// Packet_Analysis_InGame_All : �ΰ��ӿ��� �ʿ��� ��� �÷��̾��� ������ �޴´�.
BOOL CAnalysisPacket::Packet_Analysis_InGame_All(CStream* Buf, CNetWork* NetWork)
{
	// x��ǥ, y��ǥ
	int TempXPos, TempYPos;
	// �÷��̾��� �ε���
	int TempSerialNum;
	// �����ߴ°�
	bool bIsQuit;

	// �÷��̾��� �ε����� �о�´�.
	Buf->ReadInt(&TempSerialNum);
	// x��ǥ�� �д´�.
	Buf->ReadInt(&TempXPos);
	// y��ǥ�� �д´�.
	Buf->ReadInt(&TempYPos);
	// �����ߴ��� ���θ� �д´�.
	Buf->ReadBool(&bIsQuit);
	// �÷��̾��� ���¸� �д´�.
	Buf->ReadCharacterState(&NetWork->PlayerState[TempSerialNum]);
	// �÷��̾��� ������ �д´�.
	Buf->ReadCharacterDirection(&NetWork->PlayerDirection[TempSerialNum]);

	NetWork->PlayerXPos[TempSerialNum] = TempXPos;
	NetWork->PlayerYPos[TempSerialNum] = TempYPos;
	NetWork->bIsPlayerQuit[TempSerialNum] = bIsQuit;

	if (NetWork->bIsPlayerQuit[TempSerialNum])
	{
		NetWork->ClientRelease(TempSerialNum);
	}

	//===================================================================================================
	// ������ �÷��̾�� �浹 ó��
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
	// ������ �¸� üũ
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

	// ��ΰ� �� ������ �й��ߴ�.
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
	// �ð� ���� ó��
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

	// �ΰ����� ������ ������ ��Ŷ�� ������.
	CMakePacket::Packet_Send_InGame_All(Buf, NetWork, NetWork->PlayerXPos, NetWork->PlayerYPos, NetWork->bIsPlayerQuit, Min, Sec, NetWork->PlayerState, NetWork->bIsGameEnd, NetWork->bIsPlayerWin, NetWork->PlayerDirection);
	send(NetWork->hClntSock[TempSerialNum], Buf->m_SendBuffer, Buf->m_BufferWritePoint, 0);

	Buf->ResetSendPoint();
	Buf->ClearSendBuffer();

	return TRUE;
}

//===========================================================
// Packet_Analysis_InGame_ChangetoLobby : Ŭ���̾�Ʈ�� ���â�� Ȯ���ϰ� �κ�� ���ư���.
BOOL CAnalysisPacket::Packet_Analysis_InGame_ChangetoLobby(CStream* Buf, CNetWork* NetWork)
{
	// ��Ŷ�� ���� �÷��̾��� �ε���
	int TempSerialNum;

	// �÷��̾��� �ε����� �д´�.
	Buf->ReadInt(&TempSerialNum);

	// �κ�� ���ư��� ��Ŷ�� ������.
	CMakePacket::Packet_Send_InGame_ChangetoLobby(Buf, NetWork->bIsPlayer, NetWork->bIsPlayerReady);
	send(NetWork->hClntSock[TempSerialNum], Buf->m_SendBuffer, Buf->m_BufferWritePoint, 0);

	Buf->ResetSendPoint();
	Buf->ClearSendBuffer();

	return TRUE;
}

//===========================================================
// Packet_Analysis_KeepAlive : Ŭ���̾�Ʈ�� ����ִ��� üũ�Ѵ�.
BOOL CAnalysisPacket::Packet_Analysis_KeepAlive(CStream* Buf, CNetWork* NetWork)
{
	// Ŭ���̾�Ʈ�� ��Ʈ��Ʈ üũ�� �����Ͽ� ��Ʈ��Ʈ ī��Ʈ�� 0���� ���ȴ�.
	NetWork->m_HeartBeatCount[NetWork->SendClientNum] = 0;

	printf("Client to Message : KeepAlive\n");

	return TRUE;
}