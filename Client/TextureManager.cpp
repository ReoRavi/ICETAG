#include "stdafx.h"
#include "TextureManager.h"
#include "WindowManager.h"


CTextureManager::CTextureManager(VOID)
{
	// empty...
}

CTextureManager::~CTextureManager(VOID)
{
	// empty...
}

//==================================
// Release : 메모리 해제
VOID CTextureManager::Release(VOID)
{
	for (int i = 0; i < m_vTextureInfo.size(); i++)
	{
		m_vTextureInfo[i].Texture->Release();
	}

	m_vTextureInfo.clear();
}

//==================================
// LoadTexture : 텍스쳐를 불러온다.
// _filename - 불러올 이미지의 이름
LPDIRECT3DTEXTURE9 CTextureManager::LoadTexture(const char* _filename)
{
	// 에러문구 생성
	string error;
	error.append("Imagefile '");
	error.append(_filename);
	error.append("' Load Failed!\nError::m_pd3dTexture == NULL");

	// 텍스쳐 중복 시 바로 리턴
	for (int i = 0; i < m_vTextureInfo.size(); i++)
	{
		if (m_vTextureInfo[i].Filename == _filename)
		{
			return m_vTextureInfo[i].Texture;
		}
	}

	// 중복이 아닐 시 새로 생성
	TextureInfo info;

	info.Filename = _filename;

	if (FAILED(D3DXCreateTextureFromFileEx(WinMgr->m_pd3dDevice,
											info.Filename.c_str(),
											D3DX_DEFAULT_NONPOW2,
											D3DX_DEFAULT_NONPOW2,
											1,
											0,
											D3DFMT_UNKNOWN,
											D3DPOOL_MANAGED,
											1,
											1,
											NULL,
											&info.ImageInfo,
											NULL,
											&info.Texture)))
	{
#if _DEBUG
		MessageBox(NULL, error.c_str(), "ERROR", MB_ICONERROR);
		return NULL;
#endif
	}

	// 벡터에 추가
	m_vTextureInfo.push_back(info);
	
	for (int i = 0; i < m_vTextureInfo.size(); i++)
	{
		if (m_vTextureInfo[i].Filename == _filename)
		{
			return m_vTextureInfo[i].Texture;
		}
	}
}

//==================================
// GetImageInfo : 이미지의 정보를 가져온다.
// _filename - 정보를 가져올 이미지의 이름
D3DXIMAGE_INFO CTextureManager::GetImageInfo(const char* _filename)
{
	// 이미지의 정보를 불러온다.
	for (int i = 0; i < m_vTextureInfo.size(); i++)
	{
		if (m_vTextureInfo[i].Filename == _filename)
		{
			return m_vTextureInfo[i].ImageInfo;
		}
	}
}