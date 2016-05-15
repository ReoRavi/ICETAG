#pragma once

#include "NetWork.h"


class CStream;

class CAnalysisPacket
{
public:
	CAnalysisPacket();
	virtual ~CAnalysisPacket();

	//===========================================================
	// Packet_Analysis_ConnectToRoom_ConnectAccept : 클라이언트에서 방에 접속 요청을 했다.
	static BOOL Packet_Analysis_ConnectToRoom_ConnectAccept(CStream* Buf, CNetWork* NetWork);
	//===========================================================
	// Packet_Analysis_Room_GameStart : 클라이언트에서 게임 시작을 요청했다.
	// 모든 클라이언트들에게 씬을 전환할것을 요청하는 패킷을 보낸다.
	static BOOL Packet_Analysis_Room_GameStart(CStream* Buf, CNetWork* NetWork);
	//===========================================================
	// Packet_Analysis_Room_DataUpdate : 방 데이터 업데이트
	static BOOL Packet_Analysis_Room_DataUpdate(CStream* Buf, CNetWork* NetWork);
	//===========================================================
	// Packet_Analysis_Room_PlayerReady : 클라이언트가 준비되었음을 알렸다.
	static BOOL Packet_Analysis_Room_PlayerReady(CStream* Buf, CNetWork* NetWork);
	//===========================================================
	// Packet_Analysis_Room_GameQuit : 방에서 클라이언트와의 접속을 끊는다.
	static BOOL Packet_Analysis_Room_GameQuit(CStream* Buf, CNetWork* NetWork);
	//===========================================================
	// Packet_Analysis_InGame_All : 인게임에서 필요한 모든 플레이어의 정보를 받는다.
	static BOOL Packet_Analysis_InGame_All(CStream* Buf, CNetWork* NetWork);
	//===========================================================
	// Packet_Analysis_InGame_ChangetoLobby : 클라이언트가 결과창을 확인하고 로비로 돌아간다.
	static BOOL Packet_Analysis_InGame_ChangetoLobby(CStream* Buf, CNetWork* NetWork);
	//===========================================================
	// Packet_Analysis_KeepAlive : 클라이언트가 살아있는지 체크한다.
	static BOOL Packet_Analysis_KeepAlive(CStream* Buf, CNetWork* NetWork);
};

