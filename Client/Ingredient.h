#pragma once

//=============================================
// CIngredient : 화면에 출력하는 오브젝트들의 상위 클래스.
class CIngredient
{
public: // public 변수
	D3DXVECTOR2 m_vecSize;			// 크기
	D3DXVECTOR2 m_vecPosition;		// 위치
	float		m_fRotation;		// 각도
	bool		m_bIsVisible;		// Visible
	D3DCOLOR	m_d3dColor;			// 색깔
public: // public 함수
	CIngredient(VOID);
	~CIngredient(VOID);

	VOID Release(VOID);

	D3DXVECTOR2 GetSize(VOID);
	VOID SetSize(D3DXVECTOR2 _size);
	VOID SetSize(int _width, int _height);

	D3DXVECTOR2 GetPosition(VOID);
	VOID SetPosition(D3DXVECTOR2 _pos);
	VOID SetPosition(int _x, int _y);

	float GetRotation(VOID);
	VOID SetRotation(float _rotation);

	D3DCOLOR GetColor(VOID);
	VOID SetColor(int _alpha = 255, int _r = 255, int _g = 255, int _b = 255);

	// Render함수에 사용할 것.
	VOID ActionFadeIn(float _time, float _startAlpha = 0.0f, float _endAlpha = 255.0f);
	// Render함수에 사용할 것.
	VOID ActionFadeOut(float _time, float _startAlpha = 255.0f, float _endAlpha = 0.0f);
};

