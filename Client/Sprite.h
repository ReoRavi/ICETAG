#pragma once

//=============================================
// CSprite : 이미지 객체
class CSprite :
	public CIngredient
{
public: // public 변수
	LPDIRECT3DTEXTURE9 m_pd3dTexture;
public: // public 함수
	CSprite(VOID);
	~CSprite(VOID);

	// 이미지 출력
	VOID Render(VOID);
	// 메모리 해제
	VOID Release(VOID);
	// 이미지 생성
	VOID CreateSprite(const char* _filename);
};

