#pragma once

#include "Scene.h"

class CSprite;
class CLable;

class S_GameLoad :
	public CScene
{
public:
	S_GameLoad();
	virtual ~S_GameLoad();

public :
	CSprite*	m_BackGround;
	CLable*		m_LoadMessage;

	void Init(void) override;
	void Process(void) override;
	void Render(void) override;
	void Release(void) override;
};

