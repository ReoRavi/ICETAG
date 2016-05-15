#pragma once

class CStream;

//=============================================
// CAnalysisPacket : 받은 패킷을 분석한다.
class CAnalysisPacket
{
public :
	//==================================================
	// Packet_Analysis_Room_UserUpdate 
	// 유저의 정보가 업데이트되었다.
	static BOOL Packet_Analysis_Room_UserUpdate(CStream* Buf);
	//==================================================
	// Packet_Analysis_Room_GameStart 
	// 게임을 시작한다.
	static BOOL Packet_Analysis_Room_GameStart(CStream* Buf);
	//==================================================
	// Packet_Analysis_Room_DataUpdate 
	// 방의 정보가 업데이트 되었다.
	static BOOL Packet_Analysis_Room_DataUpdate(CStream* Buf);
	//==================================================
	// Packet_Analysis_Room_PlayerReady 
	// 플레이어 준비상태가 갱신되었다.
	static BOOL Packet_Analysis_Room_PlayerReady(CStream* Buf);
	//==================================================
	// Packet_Analysis_Room_GameStartFailed 
	// 게임 시작에 실패했다.
	static BOOL Packet_Analysis_Room_GameStartFailed(CStream* Buf);
	//==================================================
	// Packet_Analysis_Room_PlayerQuit 
	// 방에서 유저가 종료했다.
	static BOOL Packet_Analysis_Room_PlayerQuit(CStream* Buf);
	//==================================================
	// Packet_Analysis_InGame_All 
	// 인게임의 모든 정보를 업데이트한다.
	static BOOL Packet_Analysis_InGame_All(CStream* Buf);
	//==================================================
	// Packet_Analysis_InGame_ChangetoLobby 
	// 인게임에서 게임이 끝나 로비로 이동한다.
	static BOOL Packet_Analysis_InGame_ChangetoLobby(CStream* Buf);
	//==================================================
	// Packet_Analysis_KeepAlive 
	// 클라이언트가 제데로 연결되어 있는지 체크한다.
	static BOOL Packet_Analysis_KeepAlive(CStream* Buf);
};