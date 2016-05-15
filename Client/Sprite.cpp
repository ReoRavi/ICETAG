#include "stdafx.h"
#include "Sprite.h"
#include "WindowManager.h"
#include "TextureManager.h"


CSprite::CSprite(VOID)
{
	m_pd3dTexture = nullptr;
}

CSprite::~CSprite(VOID)
{
	// empty...
}

//==================================
// Render : 이미지 출력
VOID CSprite::Render(VOID)
{
	if (m_bIsVisible)
	{
		RECT size;
		size.top = 0;
		size.left = 0;
		size.right = GetSize().x;
		size.bottom = GetSize().y;

		float degree = D3DXToRadian(this->GetRotation());

		// 메트릭스 선언
		D3DXMATRIX matrix;

		// 회전, 이동, 센터, 역센터
		D3DXMATRIX matRotation;
		D3DXMATRIX matTransfer;
		D3DXMATRIX matCenter;
		D3DXMATRIX matCenterReverse;

		// 단위행렬로 초기화
		D3DXMatrixIdentity(&matrix);
		D3DXMatrixIdentity(&matRotation);
		D3DXMatrixIdentity(&matTransfer);
		D3DXMatrixIdentity(&matCenter);
		D3DXMatrixIdentity(&matCenterReverse);

		// Z축을 기준으로 Rotation값 만큼 회전
		D3DXMatrixRotationZ(&matRotation, degree);

		// 역행렬 적용
		D3DXMatrixInverse(&matCenterReverse, NULL, &matCenter);

		// 센터값과 위치값 적용
		D3DXMatrixTranslation(&matCenterReverse, -GetSize().x / 2, -GetSize().y / 2, 0);
		D3DXMatrixTranslation(&matTransfer, GetPosition().x, GetPosition().y, 0);
		
		//메트릭스 곱함
		matrix = matCenterReverse * matRotation * matCenter * matTransfer;
		
		WinMgr->m_pd3dSprite->SetTransform(&matrix);

		WinMgr->m_pd3dSprite->Begin(D3DXSPRITE_ALPHABLEND);

		// 출력
		WinMgr->m_pd3dSprite->Draw(m_pd3dTexture, &size, NULL, NULL, this->GetColor());

		WinMgr->m_pd3dSprite->End();
	}
}

//==================================
// Release : 메모리 해제
VOID CSprite::Release(VOID)
{
	if (m_pd3dTexture != nullptr)
	{
		m_pd3dTexture = nullptr;
	}
}

//==================================
// CreateSprite : 이미지 생성
VOID CSprite::CreateSprite(const char* _filename)
{
	m_pd3dTexture = TextureMgr->LoadTexture(_filename);
	// 원래 이미지 사이즈로 초기화
	this->SetSize(D3DXVECTOR2(TextureMgr->GetImageInfo(_filename).Width, TextureMgr->GetImageInfo(_filename).Height));
}