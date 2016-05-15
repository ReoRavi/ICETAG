#pragma once

class CSprite;
class CLable;
class CAnimation;

//=============================================
// S_Title : Ÿ��Ʋ ��
class S_Title :
	public CScene
{
public:
	S_Title();
	virtual ~S_Title();

	// �ʱ�ȭ
	VOID Init(VOID) override;
	// ����
	VOID Process(VOID) override;
	// �̹��� ���
	VOID Render(VOID) override;
	// �޸� ����
	VOID Release(VOID) override;

public  :
	// ���
	CSprite* m_BackGround;
	// �ΰ�
	CSprite* m_Logo;
	// ���� ���� ��ư
	CSprite* m_GameStartButton;
	// ���� ��� ��ư
	CSprite* m_HowtoPlayButton;
	// ������ ��ư
	CSprite* m_ExitButton;
};

