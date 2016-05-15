#pragma once

class CSystem
{
public: // public ÇÔ¼ö
	CSystem(VOID);
	~CSystem(VOID);

	BOOL Init(VOID);
	VOID MessageLoop(VOID);
	VOID Process(VOID);
	VOID Render(VOID);
	VOID Release(VOID);
};

