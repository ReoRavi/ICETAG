#include "stdafx.h"
#include "S_ConnectToRoom.h"

S_ConnectToRoom::S_ConnectToRoom()
{
}


S_ConnectToRoom::~S_ConnectToRoom()
{
}

//=================================================================
// Init : �ʱ�ȭ
VOID S_ConnectToRoom::Init(VOID)
{
	// ���
	m_BackGround = new CSprite();
	m_BackGround->CreateSprite("Resource/ConnectToRoom/BackGround.png");
	m_BackGround->SetPosition(512, 383);

	// IP �Է� ��
	m_IPBar = new CSprite();
	m_IPBar->CreateSprite("Resource/ConnectToRoom/IPBar.png");
	m_IPBar->SetPosition(625, 325);

	//�̸� �Է� ��
	m_NickNameBar = new CSprite();
	m_NickNameBar->CreateSprite("Resource/ConnectToRoom/IPBar.png");
	m_NickNameBar->SetPosition(625, 425);

	// IP �ؽ�Ʈ
	m_IPLable = new CLable();
	m_IPLable->CreateText("����", 30);
	m_IPLable->SetPosition(380, 310);

	// �̸� �ؽ�Ʈ
	m_NickNameLable = new CLable();
	m_NickNameLable->CreateText("����", 30);
	m_NickNameLable->SetPosition(380, 405);

	// �ڷΰ��� ��ư
	m_BackButton = new CSprite();
	m_BackButton->CreateSprite("Resource/ConnectToRoom/BackButton.png");
	m_BackButton->SetPosition(950, 700);

	// ���� ��ư
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
// Process : ����
VOID S_ConnectToRoom::Process(VOID)
{
	if (SceneMgr->CurrentScene == Scene_Info::SceneInfo_ConnectToRoom)
	{
		// ��� Ŭ�� �� ó��
		if (LBUTTON_CLICK_SPRITE(m_BackGround))
		{
			// �Է��� �ʱ�ȭ�Ѵ�.
			printf("BackGround\n");
			m_bIsIPInput = false;
			m_bIsNickNameInput = false;
		}

		// IP�� Ŭ�� ��
		if (LBUTTON_CLICK_SPRITE(m_IPBar))
		{
			// IP�� �Է�
			printf("IPBar\n");
			m_bIsIPInput = true;
			m_bIsNickNameInput = false;
		}

		// �̸� �� Ŭ�� ��
		if (LBUTTON_CLICK_SPRITE(m_NickNameBar))
		{
			// �̸� �� �Է�
			printf("NickNameBar\n");
			m_bIsIPInput = false;
			m_bIsNickNameInput = true;
		}

		// IP�� �Է¹ް�������, ���ڸ� �Է¹޴´�.
		if (m_bIsIPInput)
		{
			NumpadInputCheck(true);
		}

		// �̸��� �Է¹ް� ������, Ű����� ���� �Ѵ� �Է¹޴´�.
		if (m_bIsNickNameInput)
		{
			KeyBoardInputCheck(false);
			NumpadInputCheck(false);
		}

		// ���ư Ŭ�� ��
		if (LBUTTON_CLICK_SPRITE(m_BackButton))
		{
			// Ÿ��Ʋ�� �ǵ��ư���.
			SceneMgr->ChangeScene(Scene_Info::SceneInfo_Title);
		}

		// ���� ��ư Ŭ�� ��
		if (LBUTTON_CLICK_SPRITE(m_ConnectButton))
		{
			// ������ ���� ��û
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
// Render : �̹��� ���
VOID S_ConnectToRoom::Render(VOID)
{
	// ���
	m_BackGround->Render();
	// IP ��
	m_IPBar->Render();
	// �̸� ��
	m_NickNameBar->Render();
	// IP �ؽ�Ʈ
	m_IPLable->Render(m_IP.c_str(), 1, 1, 0, 0, 0);
	// �̸� �ؽ�Ʈ
	m_NickNameLable->Render(m_NickName.c_str(), 1, 1, 0, 0, 0);
	// ���ư
	m_BackButton->Render();
	// ���� ��ư
	m_ConnectButton->Render();
	
}

//=================================================================
// Release : �޸� ����
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
// KeyBoardInputCheck : Ű������ �Է��� ó���Ѵ�. 
// bIsIP - IP �Է��� ����
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

	// Ű������ Ű
	char Alpabet[26] = { 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',
		'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l',
		'z', 'x', 'c', 'v', 'b', 'n', 'm' };

	// Ű�� �ԷµǾ����� �˻��Ѵ�.
	for (int i = 0; i < 26; i++)
	{
		if (KEYDOWN(VkKeyScan(Alpabet[i])))
		{
			m_bIsKeyBoardDown[i] = true;
		}
	}

	// Ű�� ��ȴ��� �˻��Ѵ�.
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
// NumpadInputCheck : ���� �е� �Է��� ó���Ѵ�..
// bIsIP - IP �Է��� ����
VOID S_ConnectToRoom::NumpadInputCheck(bool bIsIP)
{
	string str;

	DWORD NumberVKCode[22] = { VK_NUMPAD0, VK_NUMPAD1, VK_NUMPAD2,
		VK_NUMPAD3, VK_NUMPAD4, VK_NUMPAD5,
		VK_NUMPAD6, VK_NUMPAD7, VK_NUMPAD8,
		VK_NUMPAD9, 0x30, 0x31, 0x32, 0x33, 0x34,
		0x35, 0x36, 0x37, 0x38, 0x39, VK_OEM_PERIOD, VK_BACK };

	// ���� �ڵ�
	char NumberCode[22] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.' };

	if (bIsIP)
	{
		str = m_IP;
	}
	else
	{
		str = m_NickName;
	}

	// ���� �е� Ű�� �ԷµǾ��ٸ�
	for (int i = 0; i < 22; i++)
	{
		if (KEYDOWN(NumberVKCode[i]))
		{
			m_bIsNumberKeyDown[i] = true;
		}
	}

	// ���� �е� Ű�� ��ȴٸ�
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