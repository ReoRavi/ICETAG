#pragma once

//=============================================
// CLable : 화면에 출력할 텍스트.
class CLable :
	public CIngredient
{
public: // public 변수
	LPD3DXFONT m_pd3dFont;
public: // public 함수
	CLable(VOID);
	~CLable(VOID);

	// 텍스트를 그린다.
	VOID Render(const char* _text, float XSize, float YSize, int R, int G, int B);
	// 메모리 해제
	VOID Release(VOID);
	// 텍스트를 만든다.
	VOID CreateText(const char* _fontname, int Size);
};

