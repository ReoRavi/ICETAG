#pragma once

//=============================================
// CLable : ȭ�鿡 ����� �ؽ�Ʈ.
class CLable :
	public CIngredient
{
public: // public ����
	LPD3DXFONT m_pd3dFont;
public: // public �Լ�
	CLable(VOID);
	~CLable(VOID);

	// �ؽ�Ʈ�� �׸���.
	VOID Render(const char* _text, float XSize, float YSize, int R, int G, int B);
	// �޸� ����
	VOID Release(VOID);
	// �ؽ�Ʈ�� �����.
	VOID CreateText(const char* _fontname, int Size);
};

