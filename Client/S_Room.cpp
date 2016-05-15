#include "stdafx.h"
#include "S_Room.h"

S_Room::S_Room()
{
}


S_Room::~S_Room()
{
}

//=================================================================
// Init : �ʱ�ȭ
VOID S_Room::Init(VOID)
{
	// ���
	m_BackGround = new CSprite();
	m_BackGround->CreateSprite("Resource/Room/Room_BackGround.png");
	m_BackGround->SetPosition(512, 383);

	string ButtonName;

	// �����̸� ��ư�̸��� �ٸ���.
	if (DataManager->bIsMaster)
	{
		ButtonName = "Resource/Room/Room_StartButton.png";
	}
	else
	{
		ButtonName = "Resource/Room/Room_ReadyButton.png";
	}

	// �÷��̾� ��ư
	m_PlayerButton = new CSprite();
	m_PlayerButton->CreateSprite(ButtonName.c_str());
	m_PlayerButton->SetPosition(450, 640);
	
	// �÷��̾� �ڽ� �� �̸����� 
	for (int i = 0; i < 8; i++)
	{
		m_PlayerSite[i] = new CSprite();
		m_PlayerSite[i]->CreateSprite("Resource/Room/Room_PlayerSite.png");
		m_PlayerSite[i]->SetPosition(210 + ((i % 4) * 200), 160 + ((i / 4) * 220));

		m_UserAttendSign[i] = new CSprite();

		m_PlayerName[i] = new CLable();
		m_PlayerName[i]->CreateText("����", 30);
		m_PlayerName[i]->SetPosition((210 - (DataManager->PlayerName[i].length() * 9)) + ((i % 4) * 190), 60 + ((i / 4) * 220));
	}

	// ������ ��ư
	m_ExitButton = new CSprite();
	m_ExitButton->CreateSprite("Resource/Room/ExitButton.png");
	m_ExitButton->SetPosition(850, 650);

	m_RoomMessage = "������ ������ ������Դϴ�..!";

	// �� �ʱ�ȭ�� ������ ���� ������ ������Ʈ�Ѵ�.
	CStream* Buf = new CStream();

	CMakePacket::Packet_Send_Room_UserDataUpdate(Buf);
	send(Network->hSocket, Buf->m_SendBuffer, Buf->m_BufferWritePoint, 0);
}

//=================================================================
// Process : ����
VOID S_Room::Process(VOID)
{
	// �÷��̾� ���¿� ���� �̹��� ����.
	PlayerStateImageControl();
	// �÷��̾ �غ�Ǿ����� üũ
	PlayerReady();
	// �÷��̾ ��ư�� Ŭ���ߴ��� üũ
	PlayerButtonClick();
	// �÷��̾ ������ ��û�ߴ��� üũ
	PlayerExit();
}

//=================================================================
// Render : �̹��� ���
VOID S_Room::Render(VOID)
{
	// ���
	m_BackGround->Render();
	// �غ� ��ư
	m_PlayerButton->Render();
	// ������ ��ư
	m_ExitButton->Render();

	// �÷��̾� �ڽ�
	for (int i = 0; i < 8; i++)
	{
		m_PlayerSite[i]->Render();
	}

	// �÷��̾� ����
	for (int i = 0; i < 8; i++)
	{
		// �÷��̾ �������̶��
		if (DataManager->bIsPlayer[i])
		{
			m_UserAttendSign[i]->Render();
			m_PlayerName[i]->Render(DataManager->PlayerName[i].c_str(), 1, 1, 0, 0, 0);
		}
	}
}

//=================================================================
// Release : �޸� ����
VOID S_Room::Release(VOID)
{
	m_BackGround->Release();
	m_PlayerButton->Release();

	for (int i = 0; i < DataManager->ClientNum; i++)
	{
		m_UserAttendSign[i]->Release();
		m_PlayerSite[i]->Release();
		m_PlayerName[i]->Release();
	}
}

//=================================================================
// PlayerButtonChange : �÷��̾� ��ư�� ���¿� �°� �����Ѵ�.
VOID S_Room::PlayerButtonChange(VOID)
{
	string ButtonName;

	// ������ ��ư�� �ٸ���.
	if (DataManager->bIsMaster)
	{
		ButtonName = "Resource/Room/Room_StartButton.png";
	}
	else
	{
		ButtonName = "Resource/Room/Room_ReadyButton.png";
	}

	m_PlayerButton->CreateSprite(ButtonName.c_str());
}

//=================================================================
// PlayerStateImageControl : �÷��̾� ���¿� ���� �̹����� �����Ѵ�.
VOID S_Room::PlayerStateImageControl(VOID)
{
	for (int i = 0; i < 8; i++)
	{
		// ��ǥ ����
		m_PlayerName[i]->SetPosition((210 - (DataManager->PlayerName[i].length() * 9)) + ((i % 4) * 200), 60 + ((i / 4) * 220));

		// �÷��̾ �������̶��
		if (DataManager->bIsPlayer[i])
		{
			// ����
			if (DataManager->MasterNum == i)
			{
				m_UserAttendSign[i]->CreateSprite("Resource/Room/Room_MasterPlayerImage.png");
				m_UserAttendSign[i]->SetPosition(210 + (i % 4 * 200), 145 + (i / 4 * 200));
			}
			// �Ϲ� �÷��̾�
			else
			{
				m_UserAttendSign[i]->CreateSprite("Resource/Room/Room_PlayerImage.png");
				m_UserAttendSign[i]->SetPosition(210 + (i % 4 * 200), 145 + (i / 4 * 220));
			}

			// �÷��̾ �غ��ٸ�
			if (DataManager->PlayerReadyState[i])
			{
				m_UserAttendSign[i]->CreateSprite("Resource/Room/Room_ReadyPlayerImage.png");
			}

			PlayerButtonChange();
		}
	}
}

//=================================================================
// PlayerReady : �÷��̾ �غ��ư�� ���ȴ����� ���� �̹��� ����
VOID S_Room::PlayerReady(VOID)
{
	// �غ��ư�� ���� Ŭ���̾�Ʈ�� ������
	if (DataManager->bIsReadyClient)
	{
		// �÷��̾ �غ���� �ʾҴٸ�
		if (DataManager->PlayerReadyState[DataManager->ReadyClientNum] == FALSE)
		{
			m_UserAttendSign[DataManager->ReadyClientNum]->CreateSprite("Resource/Room/Room_ReadyPlayerImage.png");
			DataManager->PlayerReadyState[DataManager->ReadyClientNum] = TRUE;
		}
		else
		{
			m_UserAttendSign[DataManager->ReadyClientNum]->CreateSprite("Resource/Room/Room_PlayerImage.png");
			DataManager->PlayerReadyState[DataManager->ReadyClientNum] = FALSE;
		}

		DataManager->bIsReadyClient = FALSE;
	}
}

//=================================================================
// PlayerButtonClick : �÷��̾ ��ư�� Ŭ���ߴٸ�
VOID S_Room::PlayerButtonClick(VOID)
{
	// ����
	if (DataManager->bIsMaster)
	{
		m_PlayerButton->CreateSprite("Resource/Room/Room_StartButton.png");

		// ���� ���� ��û ��Ŷ�� ������.
		if (LBUTTON_CLICK_SPRITE(m_PlayerButton))
		{
			if (!(DataManager->ClientNum == 1))
			{
				CStream* Buf = new CStream();
				CMakePacket::Packet_Send_Room_GameStart(Buf);
				send(Network->hSocket, Buf->m_SendBuffer, Buf->m_BufferWritePoint, 0);
			}
		}
	}
	else
	{
		// �÷��̾��� �غ���¸� ������Ʈ �ϴ� ��Ŷ�� ������.
		if (LBUTTON_CLICK_SPRITE(m_PlayerButton))
		{
			CStream* Buf = new CStream();
			CMakePacket::Packet_Send_Room_PlayerReady(Buf, DataManager->SerialNum, DataManager->ClientNum);
			send(Network->hSocket, Buf->m_SendBuffer, Buf->m_BufferWritePoint, 0);
		}
	}

	// ������ ó��
	if (LBUTTON_CLICK_SPRITE(m_ExitButton))
	{
		CStream* Buf = new CStream();
		CMakePacket::Packet_Send_Room_Exit(Buf, DataManager->SerialNum);
		send(Network->hSocket, Buf->m_SendBuffer, Buf->m_BufferWritePoint, 0);
	}
}

//=================================================================
// PlayerExit : �÷��̾ ������.
VOID S_Room::PlayerExit(VOID)
{
	// ������ �÷��̾ ������
	if (DataManager->bIsOhterPlayerQuit)
	{
		m_UserAttendSign[DataManager->bIsOhterPlayerQuit]->Release();
		DataManager->bIsPlayer[DataManager->QuitPlayerNumber] = FALSE;
		DataManager->bIsOhterPlayerQuit = FALSE;
	}
}