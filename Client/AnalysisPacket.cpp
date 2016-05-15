#include "stdafx.h"
#include "AnalysisPacket.h"

//==================================================
// Packet_Analysis_Room_UserUpdate 
// ������ ������ ������Ʈ�Ǿ���.
BOOL CAnalysisPacket::Packet_Analysis_Room_UserUpdate(CStream* Buf)
{
	int PlayerNameLength[8];

	// ���ο� Ŭ���̾�Ʈ�� ���Դ�.
	DataManager->bIsNewClient = true;

	// Ŭ���̾�Ʈ�� ����
	Buf->ReadInt(&DataManager->ClientNum);
	// Ŭ���̾�Ʈ�� �ε���
	Buf->ReadInt(&DataManager->SerialNum);
	// �����ΰ�
	Buf->ReadBool(&DataManager->bIsMaster);
	// ������ ��ȣ
	Buf->ReadInt(&DataManager->MasterNum);

	// �÷��̾ �������ΰ�
	for (int i = 0; i < 8; i++)
	{
		Buf->ReadBool(&DataManager->bIsPlayer[i]);
	}

	// �÷��̾��� �غ� ����
	for (int i = 0; i < 8; i++)
	{
		Buf->ReadBool(&DataManager->PlayerReadyState[i]);
	}

	// �÷��̾� �̸��� ����
	for (int i = 0; i < 8; i++)
	{
		Buf->ReadInt(&PlayerNameLength[i]);
	}

	// �÷��̾��� �̸��� �д´�.
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
// ������ �����Ѵ�.
BOOL CAnalysisPacket::Packet_Analysis_Room_GameStart(CStream* Buf)
{
	// �÷��̾��� ����
	Buf->ReadInt(&DataManager->PlayerNum);
	// �÷��̾��� ��ȣ
	Buf->ReadInt(&DataManager->SerialNum);
	// ������ ��ȣ
	Buf->ReadInt(&DataManager->TaggerNum);

	// �÷��̾��� ���¸� �����Ѵ�.
	for (int i = 0; i < 8; i++)
	{
		Buf->ReadCharacterState(&DataManager->m_PlayerState[i]);
	}

	// ������ ���۵Ǿ� �ΰ������� ���� �ٲ۴�.
	SceneMgr->ChangeScene(SceneInfo_InGame);

	return TRUE;
}

//==================================================
// Packet_Analysis_Room_DataUpdate 
// ���� ������ ������Ʈ �Ǿ���.
BOOL CAnalysisPacket::Packet_Analysis_Room_DataUpdate(CStream* Buf)
{
	int PlayerNameLength[8];

	// Ŭ���̾�Ʈ�� ����
	Buf->ReadInt(&DataManager->ClientNum);
	// Ŭ���̾�Ʈ�� �ε���
	Buf->ReadInt(&DataManager->SerialNum);
	// �����ΰ�
	Buf->ReadBool(&DataManager->bIsMaster);
	// ������ �ε���
	Buf->ReadInt(&DataManager->MasterNum);

	// �÷��̾ �������ΰ�
	for (int i = 0; i < 8; i++)
	{
		Buf->ReadBool(&DataManager->bIsPlayer[i]);
	}

	// �÷��̾ �غ����ΰ�
	for (int i = 0; i < 8; i++)
	{
		Buf->ReadBool(&DataManager->PlayerReadyState[i]);
	}

	// �÷��̾� �̸��� ���̸� �޴´�.
	for (int i = 0; i < 8; i++)
	{
		Buf->ReadInt(&PlayerNameLength[i]);
	}

	//�÷��̾� �̸��� �޴´�.
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
// �÷��̾� �غ���°� ���ŵǾ���.
BOOL CAnalysisPacket::Packet_Analysis_Room_PlayerReady(CStream* Buf)
{
	// �غ���¸� ������ �÷��̾ �ִ�.
	DataManager->bIsReadyClient = TRUE;
	// �غ���¸� ������ Ŭ���̾�Ʈ �ε���
	Buf->ReadInt(&DataManager->ReadyClientNum);

	return TRUE;
}

//==================================================
// Packet_Analysis_Room_GameStartFailed 
// ���� ���ۿ� �����ߴ�.
BOOL CAnalysisPacket::Packet_Analysis_Room_GameStartFailed(CStream* Buf)
{
	// ���� ���ۿ� ������
	DataManager->bIsGameStartFailed = TRUE;

	return TRUE;
}

//==================================================
// Packet_Analysis_Room_PlayerQuit 
// �濡�� ������ �����ߴ�.
BOOL CAnalysisPacket::Packet_Analysis_Room_PlayerQuit(CStream* Buf)
{
	int QuitPlayerNum;
	int SerialNum = DataManager->SerialNum;

	// ������ �÷��̾��� �ε����� ��´�.
	Buf->ReadInt(&QuitPlayerNum);

	// �÷��̾� ���� ó��
	DataManager->QuitPlayerNumber = QuitPlayerNum;

	// �ڽ��� ������ ���̶��
	if (DataManager->QuitPlayerNumber == DataManager->SerialNum)
	{
		// Ÿ��Ʋ�� ���ư���.
		SceneMgr->ChangeScene(Scene_Info::SceneInfo_Title);
		Buf->ClearRecvBuffer();
		Buf->ResetRecvPoint();

		Network->Release();
	}
	// �ٸ� �÷��̾ ��������
	else
	{
		DataManager->bIsOhterPlayerQuit = TRUE;
	}

	return TRUE;
}

//==================================================
// Packet_Analysis_InGame_All 
// �ΰ����� ��� ������ ������Ʈ�Ѵ�.
BOOL CAnalysisPacket::Packet_Analysis_InGame_All(CStream* Buf)
{
	// X��ǥ
	for (int i = 0; i < 8; i++)
	{
		Buf->ReadInt(&DataManager->PlayerXPos[i]);
	}

	// Y��ǥ
	for (int i = 0; i < 8; i++)
	{
		Buf->ReadInt(&DataManager->PlayerYPos[i]);
	}

	// Ŭ���̾�Ʈ ���� ����
	for (int i = 0; i < 8; i++)
	{
		Buf->ReadBool(&DataManager->bIsClientQuit[i]);
	}

	int t;

	// �ð�
	Buf->ReadInt(&DataManager->Time[0]);
	Buf->ReadInt(&t);

	// ��
	DataManager->Time[1] = t / 10;
	// ��
	DataManager->Time[2] = t % 10;

	// �÷��̾��� ����
	for (int i = 0; i < 8; i++)
	{
		Buf->ReadCharacterState(&DataManager->m_PlayerState[i]);
	}

	// ������ �����°�
	Buf->ReadBool(&DataManager->bIsGameEnd);
	// �¸� ����
	Buf->ReadBool(&DataManager->bIsPlayerWin);

	// �÷��̾��� ����
	for (int i = 0; i < 8; i++)
	{
		Buf->ReadCharacterDirection(&DataManager->PlayerDirection[i]);
	}

	// �÷��̾ �������ΰ�.
	for (int i = 0; i < 8; i++)
	{
		Buf->ReadBool(&DataManager->bIsPlayer[i]);
	}

	return TRUE;
}

//==================================================
// Packet_Analysis_InGame_ChangetoLobby 
// �ΰ��ӿ��� ������ ���� �κ�� �̵��Ѵ�.
BOOL CAnalysisPacket::Packet_Analysis_InGame_ChangetoLobby(CStream* Buf)
{
	// �÷��̾ �������ΰ�
	for (int i = 0; i < 8; i++)
	{
		Buf->ReadBool(&DataManager->bIsPlayer[i]);
	}

	// �÷��̾��� �غ� ����
	for (int i = 0; i < 8; i++)
	{
		Buf->ReadBool(&DataManager->PlayerReadyState[i]);
	}

	// ������ ���� ������ ���� �ٲ۴�.
	SceneMgr->ChangeScene(SceneInfo_Room);

	return TRUE;
}

//==================================================
// Packet_Analysis_KeepAlive 
// Ŭ���̾�Ʈ�� ������ ����Ǿ� �ִ��� üũ�Ѵ�.
BOOL CAnalysisPacket::Packet_Analysis_KeepAlive(CStream* Buf)
{
	CStream* Buff = new CStream();

	printf("KeepAlive\n");

	QueryPerformanceCounter(&Network->m_OldTime);

	CMakePacket::Packet_Send_KeepAlive(Buff);
	// �������� ��Ʈ��Ʈ�� ���� ������ ���ش�.
	send(Network->hSocket, Buff->m_SendBuffer, Buff->m_BufferWritePoint, 0);

	return TRUE;
}