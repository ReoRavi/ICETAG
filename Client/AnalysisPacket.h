#pragma once

class CStream;

//=============================================
// CAnalysisPacket : ���� ��Ŷ�� �м��Ѵ�.
class CAnalysisPacket
{
public :
	//==================================================
	// Packet_Analysis_Room_UserUpdate 
	// ������ ������ ������Ʈ�Ǿ���.
	static BOOL Packet_Analysis_Room_UserUpdate(CStream* Buf);
	//==================================================
	// Packet_Analysis_Room_GameStart 
	// ������ �����Ѵ�.
	static BOOL Packet_Analysis_Room_GameStart(CStream* Buf);
	//==================================================
	// Packet_Analysis_Room_DataUpdate 
	// ���� ������ ������Ʈ �Ǿ���.
	static BOOL Packet_Analysis_Room_DataUpdate(CStream* Buf);
	//==================================================
	// Packet_Analysis_Room_PlayerReady 
	// �÷��̾� �غ���°� ���ŵǾ���.
	static BOOL Packet_Analysis_Room_PlayerReady(CStream* Buf);
	//==================================================
	// Packet_Analysis_Room_GameStartFailed 
	// ���� ���ۿ� �����ߴ�.
	static BOOL Packet_Analysis_Room_GameStartFailed(CStream* Buf);
	//==================================================
	// Packet_Analysis_Room_PlayerQuit 
	// �濡�� ������ �����ߴ�.
	static BOOL Packet_Analysis_Room_PlayerQuit(CStream* Buf);
	//==================================================
	// Packet_Analysis_InGame_All 
	// �ΰ����� ��� ������ ������Ʈ�Ѵ�.
	static BOOL Packet_Analysis_InGame_All(CStream* Buf);
	//==================================================
	// Packet_Analysis_InGame_ChangetoLobby 
	// �ΰ��ӿ��� ������ ���� �κ�� �̵��Ѵ�.
	static BOOL Packet_Analysis_InGame_ChangetoLobby(CStream* Buf);
	//==================================================
	// Packet_Analysis_KeepAlive 
	// Ŭ���̾�Ʈ�� ������ ����Ǿ� �ִ��� üũ�Ѵ�.
	static BOOL Packet_Analysis_KeepAlive(CStream* Buf);
};