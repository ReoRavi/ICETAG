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
// Render : �ؽ�Ʈ�� �׸���.
// _text - ����� �ؽ�Ʈ
// XSize - X��ǥ
// YSize - Y��ǥ
// R - RGB������ R
// G- RGB������ G
// B- RGB������ B
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
	// �ؽ�Ʈ�� �׸���.
	m_pd3dFont->DrawTextA(NULL, _text, -1, &size, DT_NOCLIP, D3DCOLOR_XRGB(R, G, B, 0));

	WinMgr->m_pd3dSprite->End();
}

//==================================
// Release : �޸� ���� 
VOID CLable::Release(VOID)
{
	if (m_pd3dFont != nullptr)
	{
		m_pd3dFont->Release();
		m_pd3dFont = nullptr;
	}
}

//==================================
// CreateText : �ؽ�Ʈ�� �����.
// _fontname - ��Ʈ�� �̸�
// Size - ��Ʈ�� ũ��
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