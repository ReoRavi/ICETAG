#pragma once

//=============================================
// CSprite : �̹��� ��ü
class CSprite :
	public CIngredient
{
public: // public ����
	LPDIRECT3DTEXTURE9 m_pd3dTexture;
public: // public �Լ�
	CSprite(VOID);
	~CSprite(VOID);

	// �̹��� ���
	VOID Render(VOID);
	// �޸� ����
	VOID Release(VOID);
	// �̹��� ����
	VOID CreateSprite(const char* _filename);
};

