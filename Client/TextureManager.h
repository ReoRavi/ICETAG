#pragma once

// 텍스쳐 정보를 구성할 구조체
struct TextureInfo
{
	// 경로, 텍스쳐, 정보
	string Filename;
	LPDIRECT3DTEXTURE9 Texture;
	D3DXIMAGE_INFO ImageInfo;
};

//=============================================
// CTextureManager : 텍스쳐를 관리하는 매니저 객체
class CTextureManager :
	public ISingleton <CTextureManager>
{

public: // public 함수
	CTextureManager(VOID);
	~CTextureManager(VOID);

public :
	// 텍스쳐 객체
	vector<TextureInfo> m_vTextureInfo;

public :
	// 메모리 해제
	VOID Release(VOID);

	// 텍스쳐를 불러온다.
	LPDIRECT3DTEXTURE9 LoadTexture(const char* _filename);
	// 이미지의 정보를 불러온다.
	D3DXIMAGE_INFO GetImageInfo(const char* _filename);
};

#define TextureMgr CTextureManager::GetInstance()
