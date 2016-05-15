#pragma once

//=============================================
// CWindowManager : ������ �κ� ó���� ����ϴ� �Ŵ���
class CWindowManager :
	public ISingleton <CWindowManager>
{
public: // public ����
	// ��������
	HINSTANCE	m_hInst;
	HWND		m_hWnd;
	POINT		m_ptWindowSize;
	BOOL		m_bIsWindowMode;

	// ���̷�Ʈ X
	LPDIRECT3D9			m_pD3D;
	LPDIRECT3DDEVICE9	m_pd3dDevice;
	LPD3DXSPRITE		m_pd3dSprite;

public: // public �Լ�
	CWindowManager(VOID);
	~CWindowManager(VOID);

	// �ʱ�ȭ
	VOID Init(VOID);
	// ������ �ʱ�ȭ
	VOID InitWindow(VOID);
	// DirectX �ʱ�ȭ
	VOID InitDirectX(VOID);
	// �޸� ����
	VOID Release(VOID);
};

#define WinMgr CWindowManager::GetInstance()
