#pragma once

#include "NetWork.h"

//==================================================
// CSystem : ���α׷��� ���� ������ ����Ѵ�.
class CSystem
{
public:
	CSystem();
	virtual ~CSystem();

public:
	// ��Ʈ��ũ ��ü
	CNetWork* NetWork;
	// �������ΰ�
	BOOL bIsLoop;

public:
	// �ʱ�ȭ
	BOOL Initialize(VOID);
	// ����
	VOID	Loop(VOID);
	// �޸� ����
	VOID	Release(VOID);
};

