#pragma once

// 캐릭터의 상태
enum eCharacter_State
{
	eCharacter_NULL,
	// 술래
	eCharacter_Tagger,
	// 평소 상태
	eCharacter_Idle,
	// 얼음 상태
	eCharacter_Freeze,
	// 죽은 상태
	eCharacter_Dead
};

// 캐릭터의 방향
enum eCharacter_Direction
{
	// 왼쪽
	eDirection_LEFT,
	// 오른쪽
	eDirection_RIGHT,
	// 밑쪽
	eDirection_DOWN,
	// 위쪽
	eDirection_UP
};