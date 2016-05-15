#pragma once

//=============================================
// CIngredient : ȭ�鿡 ����ϴ� ������Ʈ���� ���� Ŭ����.
class CIngredient
{
public: // public ����
	D3DXVECTOR2 m_vecSize;			// ũ��
	D3DXVECTOR2 m_vecPosition;		// ��ġ
	float		m_fRotation;		// ����
	bool		m_bIsVisible;		// Visible
	D3DCOLOR	m_d3dColor;			// ����
public: // public �Լ�
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

	// Render�Լ��� ����� ��.
	VOID ActionFadeIn(float _time, float _startAlpha = 0.0f, float _endAlpha = 255.0f);
	// Render�Լ��� ����� ��.
	VOID ActionFadeOut(float _time, float _startAlpha = 255.0f, float _endAlpha = 0.0f);
};

