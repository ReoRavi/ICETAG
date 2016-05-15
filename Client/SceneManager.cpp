#include "stdafx.h"
#include "SceneManager.h"
// Scenes
#include "S_Title.h"
#include "S_Room.h"
#include "S_InGame.h"
#include "S_GameLoad.h"
#include "S_HowtoPlay.h"
#include "S_ConnectToRoom.h"

CSceneManager::CSceneManager(VOID)
{
	m_pScene = nullptr;
}

CSceneManager::~CSceneManager(VOID)
{
	// empty...
}

//==================================
// Release : �޸� ����
VOID CSceneManager::Release(VOID)
{
	if (m_pScene != nullptr)
	{
		m_pScene->Release();
		delete m_pScene;
		m_pScene = nullptr;
	}
}

//==================================
// ChangeScene : ���� �ٲ۴�.
// _index - �ٲ� ���� Ÿ��
VOID CSceneManager::ChangeScene(Scene_Info _index)
{
	// ���� ������ ���� �ִٸ� �����Ѵ�.
	this->Release();

	// Ÿ�Կ� ���� ���� �ٲ۴�.
	switch (_index)
	{
	case SceneInfo_Title:
		m_pScene = new S_Title();
		CurrentScene = SceneInfo_Title;

		break;

	case SceneInfo_HowToPlay:
		m_pScene = new S_HowtoPlay();
		CurrentScene = SceneInfo_HowToPlay;
		
		break;

	case SceneInfo_ConnectToRoom:
		m_pScene = new S_ConnectToRoom();
		CurrentScene = SceneInfo_ConnectToRoom;

		break;

	case SceneInfo_Room :
		m_pScene = new S_Room();
		CurrentScene = SceneInfo_Room;

		break;

	case SceneInfo_InGame:
		m_pScene = new S_InGame();
		CurrentScene = SceneInfo_InGame;

		break;
	}
	
	// ���� �ʱ�ȭ�Ѵ�.
	m_pScene->Init();
}