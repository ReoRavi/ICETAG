#include "stdafx.h"
#include "Ingredient.h"


CIngredient::CIngredient(VOID)
{
	m_vecSize = D3DXVECTOR2(0, 0);
	m_vecPosition = D3DXVECTOR2(0, 0);
	m_fRotation = 0.0f;
	m_bIsVisible = true;
	m_d3dColor = D3DCOLOR_ARGB(255, 255, 255, 255);
}

CIngredient::~CIngredient(VOID)
{
	// empty...
}

D3DXVECTOR2 CIngredient::GetSize(VOID)
{
	return m_vecSize;
}

VOID CIngredient::SetSize(D3DXVECTOR2 _size)
{
	m_vecSize = _size;
}

VOID CIngredient::SetSize(int _width, int _height)
{
	m_vecSize.x = _width;
	m_vecSize.y = _height;
}

D3DXVECTOR2 CIngredient::GetPosition(VOID)
{
	return m_vecPosition;
}

VOID CIngredient::SetPosition(D3DXVECTOR2 _pos)
{
	m_vecPosition = _pos;
}

VOID CIngredient::SetPosition(int _x, int _y)
{
	m_vecPosition.x = _x;
	m_vecPosition.y = _y;
}

float CIngredient::GetRotation(VOID)
{
	return m_fRotation;
}

VOID CIngredient::SetRotation(float _rotation)
{
	m_fRotation = _rotation;
}

D3DCOLOR CIngredient::GetColor(VOID)
{
	return m_d3dColor;
}

VOID CIngredient::SetColor(int _alpha, int _r, int _g, int _b)
{
	m_d3dColor = D3DCOLOR_ARGB(_alpha, _r, _g, _b);
}