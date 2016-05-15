#pragma once

//=============================================
// CScene : �� ��ü
class CScene
{
public:
	CScene(VOID);
	~CScene(VOID);

	// ���� �����Լ�
	// �ʱ�ȭ
	virtual VOID Init(VOID)		= 0;
	// ����
	virtual VOID Process(VOID)	= 0;
	// �̹��� ���
	virtual VOID Render(VOID)	= 0;
	// �޸� ����
	virtual VOID Release(VOID)	= 0;
	
	// �׸��� ����
	VOID PreRender(VOID);
	// �׸��� ��
	VOID PostRender(VOID);
};

