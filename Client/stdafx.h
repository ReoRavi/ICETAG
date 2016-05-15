// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"
using namespace std;

#define ENGINE_NAME "���� �� - 0.1"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// STL Header Files
#include <vector>

#define MAX_CLIENT	8
#define BUF_SIZE		1024

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

#pragma comment(lib, "ws2_32")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3d9.lib")

// TODO: reference additional headers your program requires here
#include <d3d9.h>
#include <d3dx9.h>
#include <mmsystem.h>

// Server Header Files
#include <winsock2.h>

#include "Singleton.h"

#include "PacketDefine.h"
#include "NetWork.h"
#include "Stream.h"

#include "Ingredient.h"

#include "Scene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "DataManager.h"
#include "Sprite.h"
#include "Lable.h"
#include "Animation.h"
#include "MakePacket.h"
#include "AnalysisPacket.h"