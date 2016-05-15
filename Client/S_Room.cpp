#include "stdafx.h"
#include "S_Room.h"

S_Room::S_Room()
{
}


S_Room::~S_Room()
{
}

//=================================================================
// Init : 초기화
VOID S_Room::Init(VOID)
{
	// 배경
	m_BackGround = new CSprite();
	m_BackGround->CreateSprite("Resource/Room/Room_BackGround.png");
	m_BackGround->SetPosition(512, 383);

	string ButtonName;

	// 방장이면 버튼이름이 다르다.
	if (DataManager->bIsMaster)
	{
		ButtonName = "Resource/Room/Room_StartButton.png";
	}
	else
	{
		ButtonName = "Resource/Room/Room_ReadyButton.png";
	}

	// 플레이어 버튼
	m_PlayerButton = new CSprite();
	m_PlayerButton->CreateSprite(ButtonName.c_str());
	m_PlayerButton->SetPosition(450, 640);
	
	// 플레이어 박스 및 이름공간 
	for (int i = 0; i < 8; i++)
	{
		m_PlayerSite[i] = new CSprite();
		m_PlayerSite[i]->CreateSprite("Resource/Room/Room_PlayerSite.png");
		m_PlayerSite[i]->SetPosition(210 + ((i % 4) * 200), 160 + ((i / 4) * 220));

		m_UserAttendSign[i] = new CSprite();

		m_PlayerName[i] = new CLable();
		m_PlayerName[i]->CreateText("돋음", 30);
		m_PlayerName[i]->SetPosition((210 - (DataManager->PlayerName[i].length() * 9)) + ((i % 4) * 190), 60 + ((i / 4) * 220));
	}

	// 나가기 버튼
	m_ExitButton = new CSprite();
	m_ExitButton->CreateSprite("Resource/Room/ExitButton.png");
	m_ExitButton->SetPosition(850, 650);

	m_RoomMessage = "방장의 시작을 대기중입니다..!";

	// 방 초기화를 끝내고 유저 정보를 업데이트한다.
	CStream* Buf = new CStream();

	CMakePacket::Packet_Send_Room_UserDataUpdate(Buf);
	send(Network->hSocket, Buf->m_SendBuffer, Buf->m_BufferWritePoint, 0);
}

//=================================================================
// Process : 루프
VOID S_Room::Process(VOID)
{
	// 플레이어 상태에 따라 이미지 제어.
	PlayerStateImageControl();
	// 플레이어가 준비되었는지 체크
	PlayerReady();
	// 플레이어가 버튼을 클릭했는지 체크
	PlayerButtonClick();
	// 플레이어가 나감을 요청했는지 체크
	PlayerExit();
}

//=================================================================
// Render : 이미지 출력
VOID S_Room::Render(VOID)
{
	// 배경
	m_BackGround->Render();
	// 준비 버튼
	m_PlayerButton->Render();
	// 나가기 버튼
	m_ExitButton->Render();

	// 플레이어 박스
	for (int i = 0; i < 8; i++)
	{
		m_PlayerSite[i]->Render();
	}

	// 플레이어 상태
	for (int i = 0; i < 8; i++)
	{
		// 플레이어가 접속중이라면
		if (DataManager->bIsPlayer[i])
		{
			m_UserAttendSign[i]->Render();
			m_PlayerName[i]->Render(DataManager->PlayerName[i].c_str(), 1, 1, 0, 0, 0);
		}
	}
}

//=================================================================
// Release : 메모리 해제
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
// PlayerButtonChange : 플레이어 버튼을 상태에 맞게 변경한다.
VOID S_Room::PlayerButtonChange(VOID)
{
	string ButtonName;

	// 방장은 버튼이 다르다.
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
// PlayerStateImageControl : 플레이어 상태에 따라 이미지를 변경한다.
VOID S_Room::PlayerStateImageControl(VOID)
{
	for (int i = 0; i < 8; i++)
	{
		// 좌표 설정
		m_PlayerName[i]->SetPosition((210 - (DataManager->PlayerName[i].length() * 9)) + ((i % 4) * 200), 60 + ((i / 4) * 220));

		// 플레이어가 접속중이라면
		if (DataManager->bIsPlayer[i])
		{
			// 방장
			if (DataManager->MasterNum == i)
			{
				m_UserAttendSign[i]->CreateSprite("Resource/Room/Room_MasterPlayerImage.png");
				m_UserAttendSign[i]->SetPosition(210 + (i % 4 * 200), 145 + (i / 4 * 200));
			}
			// 일반 플레이어
			else
			{
				m_UserAttendSign[i]->CreateSprite("Resource/Room/Room_PlayerImage.png");
				m_UserAttendSign[i]->SetPosition(210 + (i % 4 * 200), 145 + (i / 4 * 220));
			}

			// 플레이어가 준비됬다면
			if (DataManager->PlayerReadyState[i])
			{
				m_UserAttendSign[i]->CreateSprite("Resource/Room/Room_ReadyPlayerImage.png");
			}

			PlayerButtonChange();
		}
	}
}

//=================================================================
// PlayerReady : 플레이어가 준비버튼을 눌렸는지에 따라 이미지 변경
VOID S_Room::PlayerReady(VOID)
{
	// 준비버튼을 누른 클라이언트가 있으면
	if (DataManager->bIsReadyClient)
	{
		// 플레이어가 준비되지 않았다면
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
// PlayerButtonClick : 플레이어가 버튼을 클릭했다면
VOID S_Room::PlayerButtonClick(VOID)
{
	// 방장
	if (DataManager->bIsMaster)
	{
		m_PlayerButton->CreateSprite("Resource/Room/Room_StartButton.png");

		// 게임 시작 요청 패킷을 보낸다.
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
		// 플레이어의 준비상태를 업데이트 하는 패킷을 보낸다.
		if (LBUTTON_CLICK_SPRITE(m_PlayerButton))
		{
			CStream* Buf = new CStream();
			CMakePacket::Packet_Send_Room_PlayerReady(Buf, DataManager->SerialNum, DataManager->ClientNum);
			send(Network->hSocket, Buf->m_SendBuffer, Buf->m_BufferWritePoint, 0);
		}
	}

	// 나가기 처리
	if (LBUTTON_CLICK_SPRITE(m_ExitButton))
	{
		CStream* Buf = new CStream();
		CMakePacket::Packet_Send_Room_Exit(Buf, DataManager->SerialNum);
		send(Network->hSocket, Buf->m_SendBuffer, Buf->m_BufferWritePoint, 0);
	}
}

//=================================================================
// PlayerExit : 플레이어가 나갔다.
VOID S_Room::PlayerExit(VOID)
{
	// 종료한 플레이어가 있으면
	if (DataManager->bIsOhterPlayerQuit)
	{
		m_UserAttendSign[DataManager->bIsOhterPlayerQuit]->Release();
		DataManager->bIsPlayer[DataManager->QuitPlayerNumber] = FALSE;
		DataManager->bIsOhterPlayerQuit = FALSE;
	}
}