// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
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

// 최대 클라이언트 수
#define MAX_CLIENT	8
// 버퍼 크기
#define BUF_SIZE		256
// 최대 게임 시간
#define MAXTIME			190

#include "Singleton.h"

#include "PacketInfo.h"
#include "EnumDefine.h"
#include "Stream.h"

#include "MakePacket.h"
#include "AnalysisPacket.h"

#include "NetWork.h"

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.