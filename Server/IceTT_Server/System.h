#pragma once

#include "NetWork.h"

//==================================================
// CSystem : 프로그램의 메인 루프를 담당한다.
class CSystem
{
public:
	CSystem();
	virtual ~CSystem();

public:
	// 네트워크 객체
	CNetWork* NetWork;
	// 실행중인가
	BOOL bIsLoop;

public:
	// 초기화
	BOOL Initialize(VOID);
	// 루프
	VOID	Loop(VOID);
	// 메모리 해제
	VOID	Release(VOID);
};

