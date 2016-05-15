#pragma once

enum Scene_Info
{
	SceneInfo_EngineStart,
	SceneInfo_Title,
	SceneInfo_HowToPlay,
	SceneInfo_ConnectToRoom,
	SceneInfo_Room,
	SceneInfo_InGame
};

//=============================================
// CSceneManager : 씬들을 관리하는 매니저 객체
class CSceneManager :
	public ISingleton <CSceneManager>
{
public: // public 변수
	CScene* m_pScene;
	Scene_Info CurrentScene;

public: // public 함수
	CSceneManager(VOID);
	~CSceneManager(VOID);

	// 메모리 해제
	VOID Release(VOID);

	// 씬을 바꾼다.
	VOID ChangeScene(Scene_Info _index);
};

#define SceneMgr CSceneManager::GetInstance()
