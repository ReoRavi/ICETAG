#pragma once

// ĳ������ ����
enum eCharacter_State
{
	eCharacter_NULL,
	// ����
	eCharacter_Tagger,
	// ��� ����
	eCharacter_Idle,
	// ���� ����
	eCharacter_Freeze,
	// ���� ����
	eCharacter_Dead
};

// ĳ������ ����
enum eCharacter_Direction
{
	// ����
	eDirection_LEFT,
	// ������
	eDirection_RIGHT,
	// ����
	eDirection_DOWN,
	// ����
	eDirection_UP
};