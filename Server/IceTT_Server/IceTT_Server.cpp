// IceTT_Server.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "System.h"

int _tmain(int argc, _TCHAR* argv[])
{
	CSystem System;

	// �ý��� �ʱ�ȭ
	System.Initialize();

	// �ý��� ����
	while (System.bIsLoop)
	{
		System.Loop();
	}

	// �ý��� �޸� ����
	System.Release();

	return 0;
}

