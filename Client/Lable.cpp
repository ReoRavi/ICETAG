#include "stdafx.h"
#include "Lable.h"
#include "WindowManager.h"


CLable::CLable(VOID)
{
	m_pd3dFont = nullptr;
}

CLable::~CLable(VOID)
{
	// empty...
}

//==================================
// Render : 텍스트를 그린다.
// _text - 출력할 텍스트
// XSize - X좌표
// YSize - Y좌표
// R - RGB에서의 R
// G- RGB에서의 G
// B- RGB에서의 B
VOID CLable::Render(const char* _text, float XSize, float YSize, int R, int G, int B)
{
	RECT size;
	size.top = XSize;
	size.left = YSize;
	size.right = 0;
	size.bottom = 0;

	D3DXVECTOR3 pos;

	WinMgr->m_pd3dSprite->Begin(D3DXSPRITE_ALPHABLEND);

	SetRect(&size, this->GetPosition().x, this->GetPosition().y, 0, 0);
	// 텍스트를 그린다.
	m_pd3dFont->DrawTextA(NULL, _text, -1, &size, DT_NOCLIP, D3DCOLOR_XRGB(R, G, B, 0));

	WinMgr->m_pd3dSprite->End();
}

//==================================
// Release : 메모리 해제 
VOID CLable::Release(VOID)
{
	if (m_pd3dFont != nullptr)
	{
		m_pd3dFont->Release();
		m_pd3dFont = nullptr;
	}
}

//==================================
// CreateText : 텍스트를 만든다.
// _fontname - 폰트의 이름
// Size - 폰트의 크기
VOID CLable::CreateText(const char* _fontname, int Size)
{
	D3DXCreateFont(WinMgr->m_pd3dDevice,
		Size,
		0,
		NULL,
		1,
		false,
		DEFAULT_CHARSET,
		NULL,
		NULL,
		NULL,
		_fontname,
		&m_pd3dFont);
}