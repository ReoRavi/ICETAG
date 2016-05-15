// IceTT_Server.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "System.h"

int _tmain(int argc, _TCHAR* argv[])
{
	CSystem System;

	// 시스템 초기화
	System.Initialize();

	// 시스템 루프
	while (System.bIsLoop)
	{
		System.Loop();
	}

	// 시스템 메모리 해제
	System.Release();

	return 0;
}

