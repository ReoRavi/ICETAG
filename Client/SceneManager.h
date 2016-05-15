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
// CSceneManager : ������ �����ϴ� �Ŵ��� ��ü
class CSceneManager :
	public ISingleton <CSceneManager>
{
public: // public ����
	CScene* m_pScene;
	Scene_Info CurrentScene;

public: // public �Լ�
	CSceneManager(VOID);
	~CSceneManager(VOID);

	// �޸� ����
	VOID Release(VOID);

	// ���� �ٲ۴�.
	VOID ChangeScene(Scene_Info _index);
};

#define SceneMgr CSceneManager::GetInstance()
