#pragma once

class CSprite;

//=============================================
// S_HowtoPlay : �÷��� ��� ��
class S_HowtoPlay :
	public CScene
{
public:
	S_HowtoPlay();
	virtual ~S_HowtoPlay();

	// �ʱ�ȭ
	VOID Init(VOID) override;
	// ����
	VOID Process(VOID) override;
	// �̹��� ���
	VOID Render(VOID) override;
	// �޸� ����
	VOID Release(VOID) override;

public :
	// ���
	CSprite*	m_BackGround;
	// ���ư��� ��ư
	CSprite*	m_BackButton;
};

