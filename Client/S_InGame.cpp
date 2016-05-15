#include "stdafx.h"
#include "S_InGame.h"

S_InGame::S_InGame()
{
}

S_InGame::~S_InGame()
{
}

//=================================================================
// Init : �ʱ�ȭ
VOID S_InGame::Init(VOID)
{
	//=======================================================================================================
	// Util
	//
	m_bIsKeyDown = false;
	m_SerialNum = DataManager->SerialNum;
	DataManager->bIsIceTagStart = false;
	//=======================================================================================================

	//=======================================================================================================
	// BackGround
	//
	m_BackGround = new CSprite();
	m_BackGround->CreateSprite("Resource/InGame/InGame_BackGround.png");
	m_BackGround->SetPosition(512, 383);
	//=======================================================================================================

	//=======================================================================================================
	// Player
	//
	// �÷��̾� ���� �� ��ǥ ����, �ִϸ��̼� ����

	int	m_RespawnXPoint[8] = { 250, 350, 450, 550, 250, 350, 450, 550 };
	int m_RespawnYPoint[8] = { 250, 250, 250, 250, 450, 450, 450, 450 };

	for (int i = 0; i < DataManager->PlayerNum; i++)
	{
		m_Player[i] = new CSprite();
		m_Player[i]->CreateSprite("Resource/InGame/Duck/Duck_Down1.png");
		m_Player[i]->SetPosition(m_RespawnXPoint[i], m_RespawnYPoint[i]);
		m_PlayerAlive[i] = TRUE;

		string PlayerAnimationSpriteName[2];
		PlayerAnimationSpriteName[0] = "Resource/InGame/Duck/Duck_Down1.png";
		PlayerAnimationSpriteName[1] = "Resource/InGame/Duck/Duck_Down2.png";

		m_PlayerAnimation[i] = new CAnimation();
		m_PlayerAnimation[i]->CreateAnimation(2, PlayerAnimationSpriteName);

		m_PlayerName[i] = new CLable();
		m_PlayerName[i]->CreateText("����", 25);
		m_PlayerName[i]->SetPosition(m_Player[i]->GetPosition().x - (DataManager->PlayerName[i].length() * 7), m_Player[i]->GetPosition().y + 50);

		m_PlayerState[i] = eCharacter_State::eCharacter_Idle;
		m_OldPlayerState[i] = eCharacter_State::eCharacter_Idle;

		m_PlayerDirection[i] = eCharacter_Direction::eDirection_DOWN;
		m_OldPlayerDirection[i] = eCharacter_Direction::eDirection_DOWN;

		m_PlayerAlive[i] = true;
	}
	//=======================================================================================================

	//=======================================================================================================
	// UI
	//
	int SignX = m_Player[m_SerialNum]->GetPosition().x;
	int SignY = m_Player[m_SerialNum]->GetPosition().y;

	m_MyCharacterSign = new CSprite();
	m_MyCharacterSign->CreateSprite("Resource/InGame/MyCharacterSign.png");
	m_MyCharacterSign->SetPosition(SignX, SignY - 50);

	m_GameResultWindow = new CSprite();
	m_GameResultWindow->SetPosition(500, 350);

	m_BacktoRoomButton = new CSprite();
	m_BacktoRoomButton->CreateSprite("Resource/InGame/BackButton.png");
	m_BacktoRoomButton->SetPosition(500, 465);
	//=======================================================================================================

	//=======================================================================================================
	// UI - Timer
	//
	m_TimeRenderXPos[0] = 410;
	m_TimeRenderXPos[1] = 525;
	m_TimeRenderXPos[2] = 605;

	for (int i = 0; i < 3; i++)
	{
		m_Time[i] = new CSprite();
		m_Time[i]->CreateSprite("Resource/InGame/Timer/InGame_0.png");
		m_Time[i]->SetPosition(m_TimeRenderXPos[i], 53);
	}

	m_TimeDivide = new CSprite();
	m_TimeDivide->CreateSprite("Resource/InGame/Timer/InGame_Time.png");
	m_TimeDivide->SetPosition(470, 53);
	//=======================================================================================================

	//=======================================================================================================
	//Effect
	//
	m_SnowManEffect = new CSprite();
	m_SnowManEffect->CreateSprite("Resource/InGame/SnowMan/Effect/1.png");
	m_SnowManEffect->SetPosition(470, 53);

	string EffectStr[7] = { "Resource/InGame/SnowMan/Effect/1.png",
		"Resource/InGame/SnowMan/Effect/2.png",
		"Resource/InGame/SnowMan/Effect/3.png",
		"Resource/InGame/SnowMan/Effect/4.png",
		"Resource/InGame/SnowMan/Effect/5.png",
		"Resource/InGame/SnowMan/Effect/6.png",
		"Resource/InGame/SnowMan/Effect/7.png" };

	m_SnowManEffectAnimation = new CAnimation();
	m_SnowManEffectAnimation->CreateAnimation(7, EffectStr);
	//=======================================================================================================

	//=======================================================================================================
	// Map
	//
	float RockXPos[MAP_ROCKNUM] = { 200, 255, 310, 365, 200, 200, 200,
		200, 255, 310, 365, 200, 200, 200,
		650, 705, 760, 815, 815, 815, 815,
		650, 705, 760, 815, 815, 815, 815 };

	float RockYPos[MAP_ROCKNUM] = { 150, 150, 150, 150, 200, 250, 300,
		650, 650, 650, 650, 500, 550, 600,
		150, 150, 150, 150, 200, 250, 300,
		650, 650, 650, 650, 500, 550, 600, };

	for (int i = 0; i < MAP_ROCKNUM; i++)
	{
		m_Rock[i] = new CSprite();
		m_Rock[i]->CreateSprite("Resource/InGame/Ice.png");
		m_Rock[i]->SetPosition(RockXPos[i], RockYPos[i]);
	}
	//=======================================================================================================

	//=======================================================================================================
	// Network
	//
	QueryPerformanceCounter(&m_CurSendTime);
	QueryPerformanceCounter(&m_OldSendTime);
	QueryPerformanceFrequency(&m_TimeFrequency);

	int PlayerX = m_Player[m_SerialNum]->GetPosition().x;
	int PlayerY = m_Player[m_SerialNum]->GetPosition().y;

	CStream* Buf = new CStream();

	CMakePacket::Packet_Send_InGame_All(Buf, m_SerialNum, PlayerX, PlayerY, DataManager->bIsQuit, m_PlayerState[m_SerialNum], m_PlayerDirection[m_SerialNum]);
	send(Network->hSocket, Buf->m_SendBuffer, Buf->m_BufferWritePoint, 0);
	//=======================================================================================================
}

//=================================================================
// Process : ����
VOID S_InGame::Process(VOID)
{
	// ������ �����ٸ�
	if (DataManager->bIsGameEnd)
	{
		// ������ ����� ���� �̹����� ����Ѵ�.
		if (DataManager->bIsPlayerWin)
		{
			m_GameResultWindow->CreateSprite("Resource/InGame/PlayerWin.png");
		}
		else
		{
			m_GameResultWindow->CreateSprite("Resource/InGame/TaggerWin.png");
		}

		// ������ �ǵ��ư��� ��ư�� ������ ��
		if (LBUTTON_CLICK_SPRITE(m_BacktoRoomButton))
		{	
			// ������ ���ư��ڴٴ� ��Ŷ�� ������.
			CStream* Buf = new CStream();

			CMakePacket::Packet_Send_InGame_ChangetoLobby(Buf, m_SerialNum);
			send(Network->hSocket, Buf->m_SendBuffer, Buf->m_BufferWritePoint, 0);
		}
	}
	else
	{
		// �ð��� 3�� ���ϰ� �Ǿ� ������ �����Ǿ��� ��
		if (DataManager->Time[0] < 3 && !DataManager->bIsIceTagStart)
		{
			// �÷��̾ ������� �ٲ۴�.
			PlayertoTagger();
			DataManager->bIsIceTagStart = true;
		}

		// �÷��̾� Ű �Է� ó��
		PlayerKeyControl();

		// �÷��̾���� �ִϸ��̼�, ����, ����, ��ǥ�� �����Ѵ�.
		for (int i = 0; i < DataManager->PlayerNum; i++)
		{
			PlayerAnimationControl(i);
			PlayerStateControl(i);	
			PlayerDirectionControl(i);
			PlayerPositionControl(i);
		}
		
		// �������̶��
		if (DataManager->bIsGameRun)
		{
			// �ǽð����� �÷��̾��� ������ ������Ʈ�Ѵ�.
			if ((m_CurSendTime.QuadPart - m_OldSendTime.QuadPart) / (m_TimeFrequency.QuadPart / 1000) > 5)
			{
				CStream* Buf = new CStream();

				CMakePacket::Packet_Send_InGame_All(Buf, m_SerialNum, m_Player[m_SerialNum]->GetPosition().x, m_Player[m_SerialNum]->GetPosition().y, DataManager->bIsQuit, m_PlayerState[m_SerialNum], m_PlayerDirection[m_SerialNum]);
				send(Network->hSocket, Buf->m_SendBuffer, Buf->m_BufferWritePoint, 0);

				QueryPerformanceCounter(&m_OldSendTime);
			}
		}

		QueryPerformanceCounter(&m_CurSendTime);
	}

}

//=================================================================
// Render : �̹��� ���
VOID S_InGame::Render(VOID)
{
	// Ÿ�̸� ���
	TimeRender();

	// ��� ���
	m_BackGround->Render();

	// �÷��̾�� ���
	for (int i = 0; i < MAX_CLIENT; i++)
	{
		if (DataManager->bIsPlayer[i])
		{
			m_Player[i]->Render();
			m_PlayerName[i]->Render(DataManager->PlayerName[i].c_str(), 0.02, 0.02, 0, 0, 0);
		}
	}

	// �� ĳ���� ȭ��ǥ ���
	m_MyCharacterSign->Render();

	// Ÿ�̸� �ð� ���
	for (int i = 0; i < 3; i++)
	{
		m_Time[i]->Render();
	}

	// : ���
	m_TimeDivide->Render();

	// ���� �� ���
	for (int i = 0; i < MAP_ROCKNUM; i++)
	{
		m_Rock[i]->Render();
	}

	// ������� �����Ǿ� ����Ʈ�� �߻���Ų��.
	if (DataManager->Time[0] <= 2)
	{
		if (m_SnowManEffectAnimation->CurrentAnimationCount != 6)
		{
			m_SnowManEffect->Render();
		}
	}

	// ������ �����ٸ� ���â�� ����Ѵ�.
	if (DataManager->bIsGameEnd)
	{
		m_GameResultWindow->Render();
		m_BacktoRoomButton->Render();
	}
}

//=================================================================
// Release : �޸� ����
VOID S_InGame::Release(VOID)
{
	m_BackGround->Release();

	for (int i = 0; i < DataManager->ClientNum; i++)
	{
		m_Player[i]->Release();
		m_PlayerName[i]->Release();
	}

	m_MyCharacterSign->Release();
	m_GameResultWindow->Release();
	m_BacktoRoomButton->Release();

	for (int i = 0; i < 3; i++)
	{
		m_Time[i]->Release();
	}

	m_TimeDivide->Release();
	m_SnowManEffect->Release();

	for (int i = 0; i < MAP_ROCKNUM; i++)
	{
		m_Rock[i]->Release();
	}
}

//=================================================================
// PlayerMove : �÷��̾� �̵� ����
VOID S_InGame::PlayerMove(VOID)
{
	// ������ �÷��̾��� ���� ���� �ӵ��� �޶�����.
	float AddSpeed;
	// �̵��� �� �ִ°�
	bool bIsMove = false;

	// ������ �ӵ��� �����Ѵ�.
	if (DataManager->TaggerNum == m_SerialNum)
		AddSpeed = DataManager->ClientNum / 4;
	else
		AddSpeed = 0;

	// ����Ű �Է�
	if (INPUT(VK_LEFT))
	{
		m_PlayerDirection[m_SerialNum] = eCharacter_Direction::eDirection_LEFT;

		// ȭ���� �Ѿ�ٸ� �ݴ������ ȭ�鿡�� ��Ÿ����.
		if (m_Player[m_SerialNum]->GetPosition().x <= 0)
		{
			m_Player[m_SerialNum]->SetPosition(1024, m_Player[m_SerialNum]->GetPosition().y);
		}

		// ���� �ε��� �̵��� �� ���°�
		for (int i = 0; i < MAP_ROCKNUM; i++)
		{
			float RockSize = m_Rock[i]->GetSize().x / 2;
			float RockXPos = m_Rock[i]->GetPosition().x + 36;
			float RockYPos = m_Rock[i]->GetPosition().y;

			if (m_Player[m_SerialNum]->GetPosition().x < RockXPos + RockSize &&
				m_Player[m_SerialNum]->GetPosition().x > RockXPos - RockSize &&
				m_Player[m_SerialNum]->GetPosition().y < RockYPos + RockSize &&
				m_Player[m_SerialNum]->GetPosition().y > RockYPos - RockSize)
			{
				bIsMove = true;
			}
		}

		// �̵��� �� �ִٸ� 
		if (!bIsMove)
		{
			// �̵��Ѵ�
			m_Player[m_SerialNum]->SetPosition(m_Player[m_SerialNum]->GetPosition().x - 5 - AddSpeed, m_Player[m_SerialNum]->GetPosition().y);
		}
	}

	// ������ Ű �Է�
	if (INPUT(VK_RIGHT))
	{
		m_PlayerDirection[m_SerialNum] = eCharacter_Direction::eDirection_RIGHT;

		// ȭ���� �Ѿ�ٸ� �ݴ������ ȭ�鿡�� ��Ÿ����.
		if (m_Player[m_SerialNum]->GetPosition().x >= 1024)
		{
			m_Player[m_SerialNum]->SetPosition(0, m_Player[m_SerialNum]->GetPosition().y);
		}

		// ���� �ε��� �̵��� �� ���°�
		for (int i = 0; i < MAP_ROCKNUM; i++)
		{
			float RockSize = m_Rock[i]->GetSize().x / 2;
			float RockXPos = m_Rock[i]->GetPosition().x - 36;
			float RockYPos = m_Rock[i]->GetPosition().y;

			if (m_Player[m_SerialNum]->GetPosition().x < RockXPos + RockSize &&
				m_Player[m_SerialNum]->GetPosition().x > RockXPos - RockSize &&
				m_Player[m_SerialNum]->GetPosition().y < RockYPos + RockSize &&
				m_Player[m_SerialNum]->GetPosition().y > RockYPos - RockSize)
			{
				bIsMove = true;
			}
		}

		// �̵��� �� �ִٸ� 
		if (!bIsMove)
		{
			// �̵��Ѵ�
			m_Player[m_SerialNum]->SetPosition(m_Player[m_SerialNum]->GetPosition().x + 5 + AddSpeed, m_Player[m_SerialNum]->GetPosition().y);
		}
	}

	if (INPUT(VK_UP))
	{
		m_PlayerDirection[m_SerialNum] = eCharacter_Direction::eDirection_UP;

		// ȭ���� �Ѿ�ٸ� �ݴ������ ȭ�鿡�� ��Ÿ����.
		if (m_Player[m_SerialNum]->GetPosition().y <= 0)
		{
			m_Player[m_SerialNum]->SetPosition(m_Player[m_SerialNum]->GetPosition().x, 768);
		}

		// ���� �ε��� �̵��� �� ���°�
		for (int i = 0; i < MAP_ROCKNUM; i++)
		{
			float RockSize = m_Rock[i]->GetSize().x / 2;
			float RockXPos = m_Rock[i]->GetPosition().x;
			float RockYPos = m_Rock[i]->GetPosition().y + 36;

			if (m_Player[m_SerialNum]->GetPosition().x < RockXPos + RockSize &&
				m_Player[m_SerialNum]->GetPosition().x > RockXPos - RockSize &&
				m_Player[m_SerialNum]->GetPosition().y < RockYPos + RockSize &&
				m_Player[m_SerialNum]->GetPosition().y > RockYPos - RockSize)
			{
				bIsMove = true;
			}
		}

		// �̵��� �� �ִٸ� 
		if (!bIsMove)
		{
			// �̵��Ѵ�
			m_Player[m_SerialNum]->SetPosition(m_Player[m_SerialNum]->GetPosition().x, m_Player[m_SerialNum]->GetPosition().y - 5 - AddSpeed);
		}
	}

	if (INPUT(VK_DOWN))
	{
		m_PlayerDirection[m_SerialNum] = eCharacter_Direction::eDirection_DOWN;

		// ȭ���� �Ѿ�ٸ� �ݴ������ ȭ�鿡�� ��Ÿ����.
		if (m_Player[m_SerialNum]->GetPosition().y >= 768)
		{
			m_Player[m_SerialNum]->SetPosition(m_Player[m_SerialNum]->GetPosition().x, 0);
		}

		bool bIsMove = false;

		// ���� �ε��� �̵��� �� ���°�
		for (int i = 0; i < MAP_ROCKNUM; i++)
		{
			float RockSize = m_Rock[i]->GetSize().x / 2;
			float RockXPos = m_Rock[i]->GetPosition().x;
			float RockYPos = m_Rock[i]->GetPosition().y - 35;

			if (m_Player[m_SerialNum]->GetPosition().x < RockXPos + RockSize &&
				m_Player[m_SerialNum]->GetPosition().x > RockXPos - RockSize &&
				m_Player[m_SerialNum]->GetPosition().y < RockYPos + RockSize &&
				m_Player[m_SerialNum]->GetPosition().y > RockYPos - RockSize)
			{
				bIsMove = true;
			}
		}

		// �̵��� �� �ִٸ� 
		if (!bIsMove)
		{
			// �̵��Ѵ�.
			m_Player[m_SerialNum]->SetPosition(m_Player[m_SerialNum]->GetPosition().x, m_Player[m_SerialNum]->GetPosition().y + 5 + AddSpeed);
		}
	}

	// �� ĳ���͸� ǥ������ ȭ��ǥ�� ��ǥ ó��.
	int x = m_Player[m_SerialNum]->GetPosition().x;
	int y = m_Player[m_SerialNum]->GetPosition().y;

	m_MyCharacterSign->SetPosition(x, y - 50);
}

//=================================================================
// PlayerKeyControl : �÷��̾��� Ű �Է��� �����Ѵ�.
VOID S_InGame::PlayerKeyControl(VOID)
{
	// �÷��̾ ���� Ȥ�� �������
	if (DataManager->m_PlayerState[m_SerialNum] == eCharacter_State::eCharacter_Idle ||
		DataManager->m_PlayerState[m_SerialNum] == eCharacter_State::eCharacter_Tagger)
	{
		// �÷��̾� �̵�
		PlayerMove();
	}

	// �����̽��� Ű�� �ԷµǾ���.
	if (KEYDOWN(VK_SPACE))
	{
		m_bIsKeyDown = true;
	}

	// �����̽��� Ű�� ��ȴ�.
	if (KEYUP(VK_SPACE))
	{
		if (DataManager->bIsIceTagStart)
		{
			// Ű�� �Էµ� ���¿��ٸ�
			if (m_bIsKeyDown)
			{
				// ���¸� �������� �ٲ۴�.
				if (m_PlayerState[m_SerialNum] == eCharacter_State::eCharacter_Idle)
				{
					m_PlayerState[m_SerialNum] = eCharacter_State::eCharacter_Freeze;
				}
			}
		}

		m_bIsKeyDown = false;
	}
}

//=================================================================
// PlayerAnimationControl : �÷��̾��� �ִϸ��̼��� �����Ѵ�.
// Count - �÷��̾��� �ε���
VOID S_InGame::PlayerAnimationControl(int Count)
{
	// �÷��̾ ����ִٸ�
	if (m_PlayerAlive[Count])
	{
		m_PlayerAnimation[Count]->AnimationFrameControl(m_Player[Count]);
	}
	else if (m_PlayerAnimation[Count]->CurrentAnimationCount != 4)
	{
		m_PlayerAnimation[Count]->AnimationFrameControl(m_Player[Count]);
	}

	// ����� ����Ʈ �ִϸ��̼� ó��. �ѹ��� �ִϸ��̼��� ����ǰ� �����.
	if ((m_SnowManEffectAnimation->CurrentAnimationCount != 6) && (DataManager->bIsIceTagStart))
	{
		m_SnowManEffect->SetPosition(m_Player[DataManager->TaggerNum]->GetPosition().x, m_Player[DataManager->TaggerNum]->GetPosition().y);
		m_SnowManEffectAnimation->AnimationFrameControl(m_SnowManEffect);
	}
}

//=================================================================
// PlayerStateControl : �÷��̾��� ���¸� �����Ѵ�.
// Count - �÷��̾��� �ε���
VOID S_InGame::PlayerStateControl(int Count)
{
	string SpriteName[5];

	// ��Ʈ��ũ���� ���� �÷��̾��� ���¿� Ŭ���̾�Ʈ�� �÷��̾��� ���°� �ٸ� ��� 
	if (m_OldPlayerState[Count] != DataManager->m_PlayerState[Count])
	{
		// ���¸� �����Ѵ�.
		m_PlayerState[Count] = DataManager->m_PlayerState[Count];
		m_OldPlayerState[Count] = DataManager->m_PlayerState[Count];

		switch (m_PlayerState[Count])
		{
			// ������ ���
		case eCharacter_State::eCharacter_Tagger:

			// ������ �� �����Ǿ��� ��� (2�д� ����)
			if (DataManager->Time[0] <= 2)
			{
				// �÷��̾ ������ �ٲ۴�
				PlayertoTagger();
			}

			break;

			// �÷��̾ �׾��� ���
		case eCharacter_State::eCharacter_Dead:

			m_PlayerAlive[Count] = false;

			// �ѹ��� ����Ǵ� �״� �ִϸ��̼��� �����Ѵ�.
			SpriteName[0] = "Resource/InGame/Duck/Dead/Duck_Dead1.png";
			SpriteName[1] = "Resource/InGame/Duck/Dead/Duck_Dead2.png";
			SpriteName[2] = "Resource/InGame/Duck/Dead/Duck_Dead3.png";
			SpriteName[3] = "Resource/InGame/Duck/Dead/Duck_Dead4.png";
			SpriteName[4] = "Resource/InGame/Duck/Dead/Duck_Dead5.png";

			m_Player[Count]->CreateSprite(SpriteName[0].c_str());
			m_PlayerAnimation[Count]->CreateAnimation(5, SpriteName);

			break;

			// ���� ���¶��
		case eCharacter_State::eCharacter_Freeze:

			// ���� ���·� ����
			SpriteName[0] = "Resource/InGame/Duck/Freeze/Duck_Freeze1.png";

			m_Player[Count]->CreateSprite(SpriteName[0].c_str());
			m_PlayerAnimation[Count]->CreateAnimation(1, SpriteName);

			break;

			// ��� ����
		case eCharacter_State::eCharacter_Idle:
			// ���� �ִϸ��̼� ��Ʈ��
			DuckDirectionImageControl(Count, DataManager->PlayerDirection[Count]);

			break;
		}
	}
}

//=================================================================
// PlayerPositionControl : �÷��̾��� ��ǥ�� �����Ѵ�.
// Count - �÷��̾��� �ε���
VOID S_InGame::PlayerPositionControl(int Count)
{
	// �ٸ� �÷��̾���� ��ǥ�� �����Ѵ�.
	if (Count != m_SerialNum)
	{
		m_Player[Count]->SetPosition(DataManager->PlayerXPos[Count], DataManager->PlayerYPos[Count]);
	}

	// �� ĳ������ ��ǥ�� �����Ѵ�.
	m_PlayerName[Count]->SetPosition(m_Player[Count]->GetPosition().x - (DataManager->PlayerName[Count].length() * 7), m_Player[Count]->GetPosition().y + 50);
}

//=================================================================
// PlayerDirectionControl : �÷��̾��� ������ �����Ѵ�.
// Count - �÷��̾��� �ε���
VOID S_InGame::PlayerDirectionControl(int Count)
{
	// ��Ʈ��ũ���� ���� ����� Ŭ���̾�Ʈ������ ������ �ٸ� ���
	if (m_OldPlayerDirection[Count] != DataManager->PlayerDirection[Count])
	{
		// ������ �����Ѵ�.
		m_PlayerDirection[Count] = DataManager->PlayerDirection[Count];
		m_OldPlayerDirection[Count] = DataManager->PlayerDirection[Count];

		// ������ ���
		if (m_PlayerState[Count] == eCharacter_State::eCharacter_Tagger && DataManager->TaggerNum == Count)
		{
			SnowManDirectionImageControl(Count, m_PlayerDirection[Count]);
		}
		// ������ ���
		else if (m_PlayerState[Count] == eCharacter_State::eCharacter_Idle && DataManager->TaggerNum != Count)
		{
			DuckDirectionImageControl(Count, m_PlayerDirection[Count]);
		}
	}
}

//=================================================================
// DuckDirectionImageControl : ���� �ִϸ��̼� ����
// PlayerCount - �÷��̾��� �ε���
// Direction - �÷��̾��� ����
VOID S_InGame::DuckDirectionImageControl(int PlayerCount, eCharacter_Direction Direction)
{
	string PlayerAnimationSpriteName[3];

	// ���⿡ ���� �ִϸ��̼��� �����Ѵ�.
	switch (DataManager->PlayerDirection[PlayerCount])
	{
		// ����
	case eCharacter_Direction::eDirection_LEFT:

		PlayerAnimationSpriteName[0] = "Resource/InGame/Duck/Duck_Left1.png";
		PlayerAnimationSpriteName[1] = "Resource/InGame/Duck/Duck_Left2.png";
		PlayerAnimationSpriteName[2] = "Resource/InGame/Duck/Duck_Left3.png";

		m_Player[PlayerCount]->CreateSprite(PlayerAnimationSpriteName[0].c_str());
		m_PlayerAnimation[PlayerCount]->CreateAnimation(3, PlayerAnimationSpriteName);

		break;

		// ������
	case eCharacter_Direction::eDirection_RIGHT:

		PlayerAnimationSpriteName[0] = "Resource/InGame/Duck/Duck_Right1.png";
		PlayerAnimationSpriteName[1] = "Resource/InGame/Duck/Duck_Right2.png";
		PlayerAnimationSpriteName[2] = "Resource/InGame/Duck/Duck_Right3.png";

		m_Player[PlayerCount]->CreateSprite(PlayerAnimationSpriteName[0].c_str());
		m_PlayerAnimation[PlayerCount]->CreateAnimation(3, PlayerAnimationSpriteName);

		break;

		// ����
	case eCharacter_Direction::eDirection_UP:

		PlayerAnimationSpriteName[0] = "Resource/InGame/Duck/Duck_Up1.png";
		PlayerAnimationSpriteName[1] = "Resource/InGame/Duck/Duck_Up2.png";

		m_Player[PlayerCount]->CreateSprite(PlayerAnimationSpriteName[0].c_str());
		m_PlayerAnimation[PlayerCount]->CreateAnimation(2, PlayerAnimationSpriteName);

		break;

		// �Ʒ���
	case eCharacter_Direction::eDirection_DOWN:

		PlayerAnimationSpriteName[0] = "Resource/InGame/Duck/Duck_Down1.png";
		PlayerAnimationSpriteName[1] = "Resource/InGame/Duck/Duck_Down2.png";

		m_Player[PlayerCount]->CreateSprite(PlayerAnimationSpriteName[0].c_str());
		m_PlayerAnimation[PlayerCount]->CreateAnimation(2, PlayerAnimationSpriteName);

		break;

	default:
		break;
	}
}

//=================================================================
// SnowManDirectionImageControl : ����� �ִϸ��̼� ��Ʈ��
// PlayerCount - �÷��̾��� �ε���
// Direction - �÷��̾��� ����
VOID S_InGame::SnowManDirectionImageControl(int PlayerCount, eCharacter_Direction Direction)
{
	string PlayerAnimationSpriteName[3];

	// ���⿡ ���� �����Ѵ�.
	switch (DataManager->PlayerDirection[PlayerCount])
	{
		// ����
	case eCharacter_Direction::eDirection_LEFT:

		PlayerAnimationSpriteName[0] = "Resource/InGame/SnowMan/SnowMan_Left1.png";
		PlayerAnimationSpriteName[1] = "Resource/InGame/SnowMan/SnowMan_Left2.png";

		m_Player[PlayerCount]->CreateSprite(PlayerAnimationSpriteName[0].c_str());
		m_PlayerAnimation[PlayerCount]->CreateAnimation(2, PlayerAnimationSpriteName);

		break;

		// ������
	case eCharacter_Direction::eDirection_RIGHT:

		PlayerAnimationSpriteName[0] = "Resource/InGame/SnowMan/SnowMan_Right1.png";
		PlayerAnimationSpriteName[1] = "Resource/InGame/SnowMan/SnowMan_Right2.png";

		m_Player[PlayerCount]->CreateSprite(PlayerAnimationSpriteName[0].c_str());
		m_PlayerAnimation[PlayerCount]->CreateAnimation(2, PlayerAnimationSpriteName);

		break;

		// ����
	case eCharacter_Direction::eDirection_UP:

		PlayerAnimationSpriteName[0] = "Resource/InGame/SnowMan/SnowMan_Up1.png";
		PlayerAnimationSpriteName[1] = "Resource/InGame/SnowMan/SnowMan_Up2.png";
		PlayerAnimationSpriteName[2] = "Resource/InGame/SnowMan/SnowMan_Up3.png";

		m_Player[PlayerCount]->CreateSprite(PlayerAnimationSpriteName[0].c_str());
		m_PlayerAnimation[PlayerCount]->CreateAnimation(3, PlayerAnimationSpriteName);

		break;

		// �Ʒ���
	case eCharacter_Direction::eDirection_DOWN:

		PlayerAnimationSpriteName[0] = "Resource/InGame/SnowMan/SnowMan_Down1.png";
		PlayerAnimationSpriteName[1] = "Resource/InGame/SnowMan/SnowMan_Down2.png";
		PlayerAnimationSpriteName[2] = "Resource/InGame/SnowMan/SnowMan_Down3.png";

		m_Player[PlayerCount]->CreateSprite(PlayerAnimationSpriteName[0].c_str());
		m_PlayerAnimation[PlayerCount]->CreateAnimation(3, PlayerAnimationSpriteName);

		break;

	default:
		break;
	}
}

//=================================================================
// TimeRender : �ð��� �׸���.
VOID S_InGame::TimeRender(VOID)
{
	for (int i = 0; i < 3; i++)
	{
		string str;

		switch (DataManager->Time[i])
		{
		case 0:
			str = "Resource/InGame/Timer/InGame_0.png";

			break;

		case 1:
			str = "Resource/InGame/Timer/InGame_1.png";

			break;

		case 2:
			str = "Resource/InGame/Timer/InGame_2.png";

			break;

		case 3:
			str = "Resource/InGame/Timer/InGame_3.png";

			break;

		case 4:
			str = "Resource/InGame/Timer/InGame_4.png";

			break;

		case 5:
			str = "Resource/InGame/Timer/InGame_5.png";

			break;

		case 6:
			str = "Resource/InGame/Timer/InGame_6.png";

			break;

		case 7:
			str = "Resource/InGame/Timer/InGame_7.png";

			break;

		case 8:
			str = "Resource/InGame/Timer/InGame_8.png";

			break;

		case 9:
			str = "Resource/InGame/Timer/InGame_9.png";

			break;

		default:
			break;
		}

		m_Time[i]->CreateSprite(str.c_str());
	}
}

//=================================================================
// PlayertoTagger : �÷��̾ ������ �ٲ۴�.
VOID S_InGame::PlayertoTagger(VOID)
{
	// ������ �̹����� �޶� ���� �ִϸ��̼� �̹����� �������־�� �Ѵ�.
	string PlayerAnimationSpriteName[3];
	PlayerAnimationSpriteName[0] = "Resource/InGame/SnowMan/SnowMan_Down1.png";
	PlayerAnimationSpriteName[1] = "Resource/InGame/SnowMan/SnowMan_Down2.png";
	PlayerAnimationSpriteName[2] = "Resource/InGame/SnowMan/SnowMan_Down3.png";

	m_PlayerState[DataManager->TaggerNum] = eCharacter_State::eCharacter_Tagger;
	m_OldPlayerState[DataManager->TaggerNum] = eCharacter_State::eCharacter_Tagger;

	// �ִϸ��̼� ����
	m_PlayerAnimation[DataManager->TaggerNum]->CreateAnimation(3, PlayerAnimationSpriteName);
}