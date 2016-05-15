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
// Release : 메모리 해제
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
// ChangeScene : 씬을 바꾼다.
// _index - 바꿀 씬의 타입
VOID CSceneManager::ChangeScene(Scene_Info _index)
{
	// 만약 이전에 씬이 있다면 해제한다.
	this->Release();

	// 타입에 따라 씬을 바꾼다.
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
	
	// 씬을 초기화한다.
	m_pScene->Init();
}