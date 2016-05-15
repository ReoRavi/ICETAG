#pragma once

// �ؽ��� ������ ������ ����ü
struct TextureInfo
{
	// ���, �ؽ���, ����
	string Filename;
	LPDIRECT3DTEXTURE9 Texture;
	D3DXIMAGE_INFO ImageInfo;
};

//=============================================
// CTextureManager : �ؽ��ĸ� �����ϴ� �Ŵ��� ��ü
class CTextureManager :
	public ISingleton <CTextureManager>
{

public: // public �Լ�
	CTextureManager(VOID);
	~CTextureManager(VOID);

public :
	// �ؽ��� ��ü
	vector<TextureInfo> m_vTextureInfo;

public :
	// �޸� ����
	VOID Release(VOID);

	// �ؽ��ĸ� �ҷ��´�.
	LPDIRECT3DTEXTURE9 LoadTexture(const char* _filename);
	// �̹����� ������ �ҷ��´�.
	D3DXIMAGE_INFO GetImageInfo(const char* _filename);
};

#define TextureMgr CTextureManager::GetInstance()
