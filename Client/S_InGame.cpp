#include "stdafx.h"
#include "S_InGame.h"

S_InGame::S_InGame()
{
}

S_InGame::~S_InGame()
{
}

//=================================================================
// Init : 초기화
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
	// 플레이어 생성 및 좌표 설정, 애니메이션 설정

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
		m_PlayerName[i]->CreateText("돋음", 25);
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
// Process : 루프
VOID S_InGame::Process(VOID)
{
	// 게임이 끝났다면
	if (DataManager->bIsGameEnd)
	{
		// 게임의 결과에 따라 이미지를 출력한다.
		if (DataManager->bIsPlayerWin)
		{
			m_GameResultWindow->CreateSprite("Resource/InGame/PlayerWin.png");
		}
		else
		{
			m_GameResultWindow->CreateSprite("Resource/InGame/TaggerWin.png");
		}

		// 방으로 되돌아가는 버튼을 눌렀을 시
		if (LBUTTON_CLICK_SPRITE(m_BacktoRoomButton))
		{	
			// 방으로 돌아가겠다는 패킷을 보낸다.
			CStream* Buf = new CStream();

			CMakePacket::Packet_Send_InGame_ChangetoLobby(Buf, m_SerialNum);
			send(Network->hSocket, Buf->m_SendBuffer, Buf->m_BufferWritePoint, 0);
		}
	}
	else
	{
		// 시간이 3분 이하가 되어 술래가 생성되었을 때
		if (DataManager->Time[0] < 3 && !DataManager->bIsIceTagStart)
		{
			// 플레이어가 술래라면 바꾼다.
			PlayertoTagger();
			DataManager->bIsIceTagStart = true;
		}

		// 플레이어 키 입력 처리
		PlayerKeyControl();

		// 플레이어들의 애니메이션, 상태, 방향, 좌표를 제어한다.
		for (int i = 0; i < DataManager->PlayerNum; i++)
		{
			PlayerAnimationControl(i);
			PlayerStateControl(i);	
			PlayerDirectionControl(i);
			PlayerPositionControl(i);
		}
		
		// 게임중이라면
		if (DataManager->bIsGameRun)
		{
			// 실시간으로 플레이어의 정보를 업데이트한다.
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
// Render : 이미지 출력
VOID S_InGame::Render(VOID)
{
	// 타이머 출력
	TimeRender();

	// 배경 출력
	m_BackGround->Render();

	// 플레이어들 출력
	for (int i = 0; i < MAX_CLIENT; i++)
	{
		if (DataManager->bIsPlayer[i])
		{
			m_Player[i]->Render();
			m_PlayerName[i]->Render(DataManager->PlayerName[i].c_str(), 0.02, 0.02, 0, 0, 0);
		}
	}

	// 내 캐릭터 화살표 출력
	m_MyCharacterSign->Render();

	// 타이머 시간 출력
	for (int i = 0; i < 3; i++)
	{
		m_Time[i]->Render();
	}

	// : 출력
	m_TimeDivide->Render();

	// 맵의 돌 출력
	for (int i = 0; i < MAP_ROCKNUM; i++)
	{
		m_Rock[i]->Render();
	}

	// 눈사람이 생성되어 이펙트를 발생시킨다.
	if (DataManager->Time[0] <= 2)
	{
		if (m_SnowManEffectAnimation->CurrentAnimationCount != 6)
		{
			m_SnowManEffect->Render();
		}
	}

	// 게임이 끝났다면 결과창을 출력한다.
	if (DataManager->bIsGameEnd)
	{
		m_GameResultWindow->Render();
		m_BacktoRoomButton->Render();
	}
}

//=================================================================
// Release : 메모리 해제
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
// PlayerMove : 플레이어 이동 제어
VOID S_InGame::PlayerMove(VOID)
{
	// 술래는 플레이어의 수에 따라 속도가 달라지낟.
	float AddSpeed;
	// 이동할 수 있는가
	bool bIsMove = false;

	// 술래의 속도를 결정한다.
	if (DataManager->TaggerNum == m_SerialNum)
		AddSpeed = DataManager->ClientNum / 4;
	else
		AddSpeed = 0;

	// 왼쪽키 입력
	if (INPUT(VK_LEFT))
	{
		m_PlayerDirection[m_SerialNum] = eCharacter_Direction::eDirection_LEFT;

		// 화면을 넘어간다면 반대방향의 화면에서 나타난다.
		if (m_Player[m_SerialNum]->GetPosition().x <= 0)
		{
			m_Player[m_SerialNum]->SetPosition(1024, m_Player[m_SerialNum]->GetPosition().y);
		}

		// 돌에 부딛혀 이동할 수 없는가
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

		// 이동할 수 있다면 
		if (!bIsMove)
		{
			// 이동한다
			m_Player[m_SerialNum]->SetPosition(m_Player[m_SerialNum]->GetPosition().x - 5 - AddSpeed, m_Player[m_SerialNum]->GetPosition().y);
		}
	}

	// 오른쪽 키 입력
	if (INPUT(VK_RIGHT))
	{
		m_PlayerDirection[m_SerialNum] = eCharacter_Direction::eDirection_RIGHT;

		// 화면을 넘어간다면 반대방향의 화면에서 나타난다.
		if (m_Player[m_SerialNum]->GetPosition().x >= 1024)
		{
			m_Player[m_SerialNum]->SetPosition(0, m_Player[m_SerialNum]->GetPosition().y);
		}

		// 돌에 부딛혀 이동할 수 없는가
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

		// 이동할 수 있다면 
		if (!bIsMove)
		{
			// 이동한다
			m_Player[m_SerialNum]->SetPosition(m_Player[m_SerialNum]->GetPosition().x + 5 + AddSpeed, m_Player[m_SerialNum]->GetPosition().y);
		}
	}

	if (INPUT(VK_UP))
	{
		m_PlayerDirection[m_SerialNum] = eCharacter_Direction::eDirection_UP;

		// 화면을 넘어간다면 반대방향의 화면에서 나타난다.
		if (m_Player[m_SerialNum]->GetPosition().y <= 0)
		{
			m_Player[m_SerialNum]->SetPosition(m_Player[m_SerialNum]->GetPosition().x, 768);
		}

		// 돌에 부딛혀 이동할 수 없는가
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

		// 이동할 수 있다면 
		if (!bIsMove)
		{
			// 이동한다
			m_Player[m_SerialNum]->SetPosition(m_Player[m_SerialNum]->GetPosition().x, m_Player[m_SerialNum]->GetPosition().y - 5 - AddSpeed);
		}
	}

	if (INPUT(VK_DOWN))
	{
		m_PlayerDirection[m_SerialNum] = eCharacter_Direction::eDirection_DOWN;

		// 화면을 넘어간다면 반대방향의 화면에서 나타난다.
		if (m_Player[m_SerialNum]->GetPosition().y >= 768)
		{
			m_Player[m_SerialNum]->SetPosition(m_Player[m_SerialNum]->GetPosition().x, 0);
		}

		bool bIsMove = false;

		// 돌에 부딛혀 이동할 수 없는가
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

		// 이동할 수 있다면 
		if (!bIsMove)
		{
			// 이동한다.
			m_Player[m_SerialNum]->SetPosition(m_Player[m_SerialNum]->GetPosition().x, m_Player[m_SerialNum]->GetPosition().y + 5 + AddSpeed);
		}
	}

	// 내 캐릭터를 표시해줄 화살표의 좌표 처리.
	int x = m_Player[m_SerialNum]->GetPosition().x;
	int y = m_Player[m_SerialNum]->GetPosition().y;

	m_MyCharacterSign->SetPosition(x, y - 50);
}

//=================================================================
// PlayerKeyControl : 플레이어의 키 입력을 제어한다.
VOID S_InGame::PlayerKeyControl(VOID)
{
	// 플레이어가 오리 혹은 술래라면
	if (DataManager->m_PlayerState[m_SerialNum] == eCharacter_State::eCharacter_Idle ||
		DataManager->m_PlayerState[m_SerialNum] == eCharacter_State::eCharacter_Tagger)
	{
		// 플레이어 이동
		PlayerMove();
	}

	// 스페이스바 키가 입력되었다.
	if (KEYDOWN(VK_SPACE))
	{
		m_bIsKeyDown = true;
	}

	// 스페이스바 키가 들렸다.
	if (KEYUP(VK_SPACE))
	{
		if (DataManager->bIsIceTagStart)
		{
			// 키가 입력된 상태였다면
			if (m_bIsKeyDown)
			{
				// 상태를 얼음으로 바꾼다.
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
// PlayerAnimationControl : 플레이어의 애니메이션을 제어한다.
// Count - 플레이어의 인덱스
VOID S_InGame::PlayerAnimationControl(int Count)
{
	// 플레이어가 살아있다면
	if (m_PlayerAlive[Count])
	{
		m_PlayerAnimation[Count]->AnimationFrameControl(m_Player[Count]);
	}
	else if (m_PlayerAnimation[Count]->CurrentAnimationCount != 4)
	{
		m_PlayerAnimation[Count]->AnimationFrameControl(m_Player[Count]);
	}

	// 눈사람 이펙트 애니메이션 처리. 한번만 애니메이션이 실행되고 멈춘다.
	if ((m_SnowManEffectAnimation->CurrentAnimationCount != 6) && (DataManager->bIsIceTagStart))
	{
		m_SnowManEffect->SetPosition(m_Player[DataManager->TaggerNum]->GetPosition().x, m_Player[DataManager->TaggerNum]->GetPosition().y);
		m_SnowManEffectAnimation->AnimationFrameControl(m_SnowManEffect);
	}
}

//=================================================================
// PlayerStateControl : 플레이어의 상태를 제어한다.
// Count - 플레이어의 인덱스
VOID S_InGame::PlayerStateControl(int Count)
{
	string SpriteName[5];

	// 네트워크에서 받은 플레이어의 상태와 클라이언트의 플레이어의 상태가 다를 경우 
	if (m_OldPlayerState[Count] != DataManager->m_PlayerState[Count])
	{
		// 상태를 제어한다.
		m_PlayerState[Count] = DataManager->m_PlayerState[Count];
		m_OldPlayerState[Count] = DataManager->m_PlayerState[Count];

		switch (m_PlayerState[Count])
		{
			// 술래일 경우
		case eCharacter_State::eCharacter_Tagger:

			// 술래가 막 생성되었을 경우 (2분대 시작)
			if (DataManager->Time[0] <= 2)
			{
				// 플레이어를 술래로 바꾼다
				PlayertoTagger();
			}

			break;

			// 플레이어가 죽었을 경우
		case eCharacter_State::eCharacter_Dead:

			m_PlayerAlive[Count] = false;

			// 한번만 실행되는 죽는 애니메이션을 설정한다.
			SpriteName[0] = "Resource/InGame/Duck/Dead/Duck_Dead1.png";
			SpriteName[1] = "Resource/InGame/Duck/Dead/Duck_Dead2.png";
			SpriteName[2] = "Resource/InGame/Duck/Dead/Duck_Dead3.png";
			SpriteName[3] = "Resource/InGame/Duck/Dead/Duck_Dead4.png";
			SpriteName[4] = "Resource/InGame/Duck/Dead/Duck_Dead5.png";

			m_Player[Count]->CreateSprite(SpriteName[0].c_str());
			m_PlayerAnimation[Count]->CreateAnimation(5, SpriteName);

			break;

			// 얼음 상태라면
		case eCharacter_State::eCharacter_Freeze:

			// 얼음 상태로 변경
			SpriteName[0] = "Resource/InGame/Duck/Freeze/Duck_Freeze1.png";

			m_Player[Count]->CreateSprite(SpriteName[0].c_str());
			m_PlayerAnimation[Count]->CreateAnimation(1, SpriteName);

			break;

			// 평소 상태
		case eCharacter_State::eCharacter_Idle:
			// 오리 애니메이션 컨트롤
			DuckDirectionImageControl(Count, DataManager->PlayerDirection[Count]);

			break;
		}
	}
}

//=================================================================
// PlayerPositionControl : 플레이어의 좌표를 제어한다.
// Count - 플레이어의 인덱스
VOID S_InGame::PlayerPositionControl(int Count)
{
	// 다른 플레이어들의 좌표를 제어한다.
	if (Count != m_SerialNum)
	{
		m_Player[Count]->SetPosition(DataManager->PlayerXPos[Count], DataManager->PlayerYPos[Count]);
	}

	// 내 캐릭터의 좌표를 제어한다.
	m_PlayerName[Count]->SetPosition(m_Player[Count]->GetPosition().x - (DataManager->PlayerName[Count].length() * 7), m_Player[Count]->GetPosition().y + 50);
}

//=================================================================
// PlayerDirectionControl : 플레이어의 방향을 제어한다.
// Count - 플레이어의 인덱스
VOID S_InGame::PlayerDirectionControl(int Count)
{
	// 네트워크에서 받은 방향과 클라이언트에서의 방향이 다를 경우
	if (m_OldPlayerDirection[Count] != DataManager->PlayerDirection[Count])
	{
		// 방향을 제어한다.
		m_PlayerDirection[Count] = DataManager->PlayerDirection[Count];
		m_OldPlayerDirection[Count] = DataManager->PlayerDirection[Count];

		// 술래일 경우
		if (m_PlayerState[Count] == eCharacter_State::eCharacter_Tagger && DataManager->TaggerNum == Count)
		{
			SnowManDirectionImageControl(Count, m_PlayerDirection[Count]);
		}
		// 오리일 경우
		else if (m_PlayerState[Count] == eCharacter_State::eCharacter_Idle && DataManager->TaggerNum != Count)
		{
			DuckDirectionImageControl(Count, m_PlayerDirection[Count]);
		}
	}
}

//=================================================================
// DuckDirectionImageControl : 오리 애니메이션 제어
// PlayerCount - 플레이어의 인덱스
// Direction - 플레이어의 방향
VOID S_InGame::DuckDirectionImageControl(int PlayerCount, eCharacter_Direction Direction)
{
	string PlayerAnimationSpriteName[3];

	// 방향에 따라 애니메이션을 제어한다.
	switch (DataManager->PlayerDirection[PlayerCount])
	{
		// 왼쪽
	case eCharacter_Direction::eDirection_LEFT:

		PlayerAnimationSpriteName[0] = "Resource/InGame/Duck/Duck_Left1.png";
		PlayerAnimationSpriteName[1] = "Resource/InGame/Duck/Duck_Left2.png";
		PlayerAnimationSpriteName[2] = "Resource/InGame/Duck/Duck_Left3.png";

		m_Player[PlayerCount]->CreateSprite(PlayerAnimationSpriteName[0].c_str());
		m_PlayerAnimation[PlayerCount]->CreateAnimation(3, PlayerAnimationSpriteName);

		break;

		// 오른쪽
	case eCharacter_Direction::eDirection_RIGHT:

		PlayerAnimationSpriteName[0] = "Resource/InGame/Duck/Duck_Right1.png";
		PlayerAnimationSpriteName[1] = "Resource/InGame/Duck/Duck_Right2.png";
		PlayerAnimationSpriteName[2] = "Resource/InGame/Duck/Duck_Right3.png";

		m_Player[PlayerCount]->CreateSprite(PlayerAnimationSpriteName[0].c_str());
		m_PlayerAnimation[PlayerCount]->CreateAnimation(3, PlayerAnimationSpriteName);

		break;

		// 위쪽
	case eCharacter_Direction::eDirection_UP:

		PlayerAnimationSpriteName[0] = "Resource/InGame/Duck/Duck_Up1.png";
		PlayerAnimationSpriteName[1] = "Resource/InGame/Duck/Duck_Up2.png";

		m_Player[PlayerCount]->CreateSprite(PlayerAnimationSpriteName[0].c_str());
		m_PlayerAnimation[PlayerCount]->CreateAnimation(2, PlayerAnimationSpriteName);

		break;

		// 아래쪽
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
// SnowManDirectionImageControl : 눈사람 애니메이션 컨트롤
// PlayerCount - 플레이어의 인덱스
// Direction - 플레이어의 방향
VOID S_InGame::SnowManDirectionImageControl(int PlayerCount, eCharacter_Direction Direction)
{
	string PlayerAnimationSpriteName[3];

	// 방향에 따라 제어한다.
	switch (DataManager->PlayerDirection[PlayerCount])
	{
		// 왼쪽
	case eCharacter_Direction::eDirection_LEFT:

		PlayerAnimationSpriteName[0] = "Resource/InGame/SnowMan/SnowMan_Left1.png";
		PlayerAnimationSpriteName[1] = "Resource/InGame/SnowMan/SnowMan_Left2.png";

		m_Player[PlayerCount]->CreateSprite(PlayerAnimationSpriteName[0].c_str());
		m_PlayerAnimation[PlayerCount]->CreateAnimation(2, PlayerAnimationSpriteName);

		break;

		// 오른쪽
	case eCharacter_Direction::eDirection_RIGHT:

		PlayerAnimationSpriteName[0] = "Resource/InGame/SnowMan/SnowMan_Right1.png";
		PlayerAnimationSpriteName[1] = "Resource/InGame/SnowMan/SnowMan_Right2.png";

		m_Player[PlayerCount]->CreateSprite(PlayerAnimationSpriteName[0].c_str());
		m_PlayerAnimation[PlayerCount]->CreateAnimation(2, PlayerAnimationSpriteName);

		break;

		// 위쪽
	case eCharacter_Direction::eDirection_UP:

		PlayerAnimationSpriteName[0] = "Resource/InGame/SnowMan/SnowMan_Up1.png";
		PlayerAnimationSpriteName[1] = "Resource/InGame/SnowMan/SnowMan_Up2.png";
		PlayerAnimationSpriteName[2] = "Resource/InGame/SnowMan/SnowMan_Up3.png";

		m_Player[PlayerCount]->CreateSprite(PlayerAnimationSpriteName[0].c_str());
		m_PlayerAnimation[PlayerCount]->CreateAnimation(3, PlayerAnimationSpriteName);

		break;

		// 아래쪽
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
// TimeRender : 시간을 그린다.
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
// PlayertoTagger : 플레이어를 술래로 바꾼다.
VOID S_InGame::PlayertoTagger(VOID)
{
	// 술래는 이미지가 달라서 새로 애니메이션 이미지도 설정해주어야 한다.
	string PlayerAnimationSpriteName[3];
	PlayerAnimationSpriteName[0] = "Resource/InGame/SnowMan/SnowMan_Down1.png";
	PlayerAnimationSpriteName[1] = "Resource/InGame/SnowMan/SnowMan_Down2.png";
	PlayerAnimationSpriteName[2] = "Resource/InGame/SnowMan/SnowMan_Down3.png";

	m_PlayerState[DataManager->TaggerNum] = eCharacter_State::eCharacter_Tagger;
	m_OldPlayerState[DataManager->TaggerNum] = eCharacter_State::eCharacter_Tagger;

	// 애니메이션 생성
	m_PlayerAnimation[DataManager->TaggerNum]->CreateAnimation(3, PlayerAnimationSpriteName);
}