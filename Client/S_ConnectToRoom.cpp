#include "stdafx.h"
#include "S_ConnectToRoom.h"

S_ConnectToRoom::S_ConnectToRoom()
{
}


S_ConnectToRoom::~S_ConnectToRoom()
{
}

//=================================================================
// Init : 초기화
VOID S_ConnectToRoom::Init(VOID)
{
	// 배경
	m_BackGround = new CSprite();
	m_BackGround->CreateSprite("Resource/ConnectToRoom/BackGround.png");
	m_BackGround->SetPosition(512, 383);

	// IP 입력 바
	m_IPBar = new CSprite();
	m_IPBar->CreateSprite("Resource/ConnectToRoom/IPBar.png");
	m_IPBar->SetPosition(625, 325);

	//이름 입력 바
	m_NickNameBar = new CSprite();
	m_NickNameBar->CreateSprite("Resource/ConnectToRoom/IPBar.png");
	m_NickNameBar->SetPosition(625, 425);

	// IP 텍스트
	m_IPLable = new CLable();
	m_IPLable->CreateText("돋음", 30);
	m_IPLable->SetPosition(380, 310);

	// 이름 텍스트
	m_NickNameLable = new CLable();
	m_NickNameLable->CreateText("돋음", 30);
	m_NickNameLable->SetPosition(380, 405);

	// 뒤로가기 버튼
	m_BackButton = new CSprite();
	m_BackButton->CreateSprite("Resource/ConnectToRoom/BackButton.png");
	m_BackButton->SetPosition(950, 700);

	// 접속 버튼
	m_ConnectButton = new CSprite();
	m_ConnectButton->CreateSprite("Resource/ConnectToRoom/ConnectButton.png");
	m_ConnectButton->SetPosition(530, 625);

	m_IP = "";
	m_NickName = "";

	m_bIsIPInput = false;
	m_bIsNickNameInput = false;
	ZeroMemory(m_bIsNumberKeyDown, sizeof(m_bIsNumberKeyDown));
	ZeroMemory(m_bIsKeyBoardDown, sizeof(m_bIsKeyBoardDown));
}

//=================================================================
// Process : 루프
VOID S_ConnectToRoom::Process(VOID)
{
	if (SceneMgr->CurrentScene == Scene_Info::SceneInfo_ConnectToRoom)
	{
		// 배경 클릭 시 처리
		if (LBUTTON_CLICK_SPRITE(m_BackGround))
		{
			// 입력을 초기화한다.
			printf("BackGround\n");
			m_bIsIPInput = false;
			m_bIsNickNameInput = false;
		}

		// IP바 클릭 시
		if (LBUTTON_CLICK_SPRITE(m_IPBar))
		{
			// IP바 입력
			printf("IPBar\n");
			m_bIsIPInput = true;
			m_bIsNickNameInput = false;
		}

		// 이름 바 클릭 시
		if (LBUTTON_CLICK_SPRITE(m_NickNameBar))
		{
			// 이름 바 입력
			printf("NickNameBar\n");
			m_bIsIPInput = false;
			m_bIsNickNameInput = true;
		}

		// IP를 입력받고있으면, 숫자만 입력받는다.
		if (m_bIsIPInput)
		{
			NumpadInputCheck(true);
		}

		// 이름을 입력받고 있으면, 키보드와 숫자 둘다 입력받는다.
		if (m_bIsNickNameInput)
		{
			KeyBoardInputCheck(false);
			NumpadInputCheck(false);
		}

		// 백버튼 클릭 시
		if (LBUTTON_CLICK_SPRITE(m_BackButton))
		{
			// 타이틀로 되돌아간다.
			SceneMgr->ChangeScene(Scene_Info::SceneInfo_Title);
		}

		// 접속 버튼 클릭 시
		if (LBUTTON_CLICK_SPRITE(m_ConnectButton))
		{
			// 서버에 접속 요청
			if (Network->Initialize(m_IP))
			{
				DataManager->t_PlayerName = m_NickName;

				CStream* Buf = new CStream();
				CMakePacket::Packet_Send_ConnectToRoom_ConnectRequest(Buf, DataManager->t_PlayerName.length(), (char*)DataManager->t_PlayerName.c_str());
				send(Network->hSocket, Buf->m_SendBuffer, Buf->m_BufferWritePoint, 0);

				SceneMgr->ChangeScene(Scene_Info::SceneInfo_Room);
			}
		}
	}
}

//=================================================================
// Render : 이미지 출력
VOID S_ConnectToRoom::Render(VOID)
{
	// 배경
	m_BackGround->Render();
	// IP 바
	m_IPBar->Render();
	// 이름 바
	m_NickNameBar->Render();
	// IP 텍스트
	m_IPLable->Render(m_IP.c_str(), 1, 1, 0, 0, 0);
	// 이름 텍스트
	m_NickNameLable->Render(m_NickName.c_str(), 1, 1, 0, 0, 0);
	// 백버튼
	m_BackButton->Render();
	// 접속 버튼
	m_ConnectButton->Render();
	
}

//=================================================================
// Release : 메모리 해제
VOID S_ConnectToRoom::Release(VOID)
{
	m_BackGround->Release();
	m_IPBar->Release();
	m_NickNameBar->Release();
	m_IPLable->Release();
	m_BackButton->Release();
	m_ConnectButton->Release();
}

//=================================================================
// KeyBoardInputCheck : 키보드의 입력을 처리한다. 
// bIsIP - IP 입력의 여부
VOID S_ConnectToRoom::KeyBoardInputCheck(bool bIsIP)
{
	string str;

	if (bIsIP)
	{
		str = m_IP;
	}
	else
	{
		str = m_NickName;
	}

	// 키보드의 키
	char Alpabet[26] = { 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',
		'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l',
		'z', 'x', 'c', 'v', 'b', 'n', 'm' };

	// 키가 입력되었는지 검사한다.
	for (int i = 0; i < 26; i++)
	{
		if (KEYDOWN(VkKeyScan(Alpabet[i])))
		{
			m_bIsKeyBoardDown[i] = true;
		}
	}

	// 키가 들렸는지 검사한다.
	for (int i = 0; i < 26; i++)
	{
		if (m_bIsKeyBoardDown[i])
		{
			if (KEYUP(VkKeyScan(Alpabet[i])))
			{
				if (str.length() < 9)
				{
					str = str + Alpabet[i];
				}

				m_bIsKeyBoardDown[i] = false;
			}
		}
	}

	if (bIsIP)
	{
		m_IP = str;
	}
	else
	{
		m_NickName = str;
	}
}

//=================================================================
// NumpadInputCheck : 숫자 패드 입력을 처리한다..
// bIsIP - IP 입력의 여부
VOID S_ConnectToRoom::NumpadInputCheck(bool bIsIP)
{
	string str;

	DWORD NumberVKCode[22] = { VK_NUMPAD0, VK_NUMPAD1, VK_NUMPAD2,
		VK_NUMPAD3, VK_NUMPAD4, VK_NUMPAD5,
		VK_NUMPAD6, VK_NUMPAD7, VK_NUMPAD8,
		VK_NUMPAD9, 0x30, 0x31, 0x32, 0x33, 0x34,
		0x35, 0x36, 0x37, 0x38, 0x39, VK_OEM_PERIOD, VK_BACK };

	// 숫자 코드
	char NumberCode[22] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.' };

	if (bIsIP)
	{
		str = m_IP;
	}
	else
	{
		str = m_NickName;
	}

	// 숫자 패드 키가 입력되었다면
	for (int i = 0; i < 22; i++)
	{
		if (KEYDOWN(NumberVKCode[i]))
		{
			m_bIsNumberKeyDown[i] = true;
		}
	}

	// 숫자 패드 키가 들렸다면
	for (int i = 0; i < 22; i++)
	{
		if (m_bIsNumberKeyDown[i])
		{
			if (KEYUP(NumberVKCode[i]))
			{
				if (i == 21)
				{
					if (!(str.empty()))
					{
						str.pop_back();
						m_bIsNumberKeyDown[i] = false;
					}
				}
				else
				{
					if (str.length() < 20)
					{
						str = str + NumberCode[i];
					}

					m_bIsNumberKeyDown[i] = false;
				}
			}
		}
	}

	if (bIsIP)
	{
		m_IP = str;
	}
	else
	{
		m_NickName = str;
	}
}