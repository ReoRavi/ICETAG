#pragma once

#include "NetWork.h"


class CStream;

class CAnalysisPacket
{
public:
	CAnalysisPacket();
	virtual ~CAnalysisPacket();

	//===========================================================
	// Packet_Analysis_ConnectToRoom_ConnectAccept : Ŭ���̾�Ʈ���� �濡 ���� ��û�� �ߴ�.
	static BOOL Packet_Analysis_ConnectToRoom_ConnectAccept(CStream* Buf, CNetWork* NetWork);
	//===========================================================
	// Packet_Analysis_Room_GameStart : Ŭ���̾�Ʈ���� ���� ������ ��û�ߴ�.
	// ��� Ŭ���̾�Ʈ�鿡�� ���� ��ȯ�Ұ��� ��û�ϴ� ��Ŷ�� ������.
	static BOOL Packet_Analysis_Room_GameStart(CStream* Buf, CNetWork* NetWork);
	//===========================================================
	// Packet_Analysis_Room_DataUpdate : �� ������ ������Ʈ
	static BOOL Packet_Analysis_Room_DataUpdate(CStream* Buf, CNetWork* NetWork);
	//===========================================================
	// Packet_Analysis_Room_PlayerReady : Ŭ���̾�Ʈ�� �غ�Ǿ����� �˷ȴ�.
	static BOOL Packet_Analysis_Room_PlayerReady(CStream* Buf, CNetWork* NetWork);
	//===========================================================
	// Packet_Analysis_Room_GameQuit : �濡�� Ŭ���̾�Ʈ���� ������ ���´�.
	static BOOL Packet_Analysis_Room_GameQuit(CStream* Buf, CNetWork* NetWork);
	//===========================================================
	// Packet_Analysis_InGame_All : �ΰ��ӿ��� �ʿ��� ��� �÷��̾��� ������ �޴´�.
	static BOOL Packet_Analysis_InGame_All(CStream* Buf, CNetWork* NetWork);
	//===========================================================
	// Packet_Analysis_InGame_ChangetoLobby : Ŭ���̾�Ʈ�� ���â�� Ȯ���ϰ� �κ�� ���ư���.
	static BOOL Packet_Analysis_InGame_ChangetoLobby(CStream* Buf, CNetWork* NetWork);
	//===========================================================
	// Packet_Analysis_KeepAlive : Ŭ���̾�Ʈ�� ����ִ��� üũ�Ѵ�.
	static BOOL Packet_Analysis_KeepAlive(CStream* Buf, CNetWork* NetWork);
};

