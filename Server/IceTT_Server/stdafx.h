// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#pragma comment(lib, "ws2_32")

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include <conio.h>
#include <iostream>
#include <time.h>
#include <WinSock2.h>
#include <process.h>

// �ִ� Ŭ���̾�Ʈ ��
#define MAX_CLIENT	8
// ���� ũ��
#define BUF_SIZE		256
// �ִ� ���� �ð�
#define MAXTIME			190

#include "Singleton.h"

#include "PacketInfo.h"
#include "EnumDefine.h"
#include "Stream.h"

#include "MakePacket.h"
#include "AnalysisPacket.h"

#include "NetWork.h"

// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.