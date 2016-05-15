#pragma once

//=============================================
// CWindowManager : 윈도우 부분 처리를 담당하는 매니저
class CWindowManager :
	public ISingleton <CWindowManager>
{
public: // public 변수
	// 윈도우즈
	HINSTANCE	m_hInst;
	HWND		m_hWnd;
	POINT		m_ptWindowSize;
	BOOL		m_bIsWindowMode;

	// 다이렉트 X
	LPDIRECT3D9			m_pD3D;
	LPDIRECT3DDEVICE9	m_pd3dDevice;
	LPD3DXSPRITE		m_pd3dSprite;

public: // public 함수
	CWindowManager(VOID);
	~CWindowManager(VOID);

	// 초기화
	VOID Init(VOID);
	// 윈도우 초기화
	VOID InitWindow(VOID);
	// DirectX 초기화
	VOID InitDirectX(VOID);
	// 메모리 해제
	VOID Release(VOID);
};

#define WinMgr CWindowManager::GetInstance()
