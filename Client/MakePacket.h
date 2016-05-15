#pragma once

//=============================================
// CMakePacket : 패킷을 만든다.
class CMakePacket
{
public:
	CMakePacket();
	virtual ~CMakePacket();

public :
	//===================================================
	// Packet_Send_ConnectToRoom_ConnectRequest
	// 방에 접속 요청을 한다.
	// Length - 플레이어 이름의 길이
	// NickName - 플레이어 이름
	static VOID Packet_Send_ConnectToRoom_ConnectRequest(CStream* Buf, int Length, char* NickName);
	//===================================================
	// Packet_Send_Room_GameStart
	// 게임 시작 요청을 한다.
	static VOID Packet_Send_Room_GameStart(CStream* Buf);
	//===================================================
	// Packet_Send_Room_UserDataUpdate
	// 유저 데이터 업데이트를 요청한다.
	static VOID Packet_Send_Room_UserDataUpdate(CStream* Buf);
	//===================================================
	// Packet_Send_Room_PlayerReady
	// 플레이어 준비 상태를 갱신한다.
	// SerialNum - 플레이어의 인덱스
	// ClientNum - 클라이언트의 갯수
	static VOID Packet_Send_Room_PlayerReady(CStream* Buf, int SerialNum, int ClientNum);
	//===================================================
	// Packet_Send_Room_Exit
	// SerialNum - 플레이어의 인덱스
	// 방에서 나감 요청을 보낸다.
	static VOID Packet_Send_Room_Exit(CStream* Buf, int SerialNum);
	//===================================================
	// Packet_Send_InGame_All
	// 인게임의 모든 요소들을 보낸다.
	// SerialNum - 플레이어의 인덱스
	// XPos - x좌표
	// YPos - y좌표
	// bIsQuit - 종료여부
	// bIsFreeze - 얼음 상태 여부
	// Direction - 방향
	static VOID Packet_Send_InGame_All(CStream* Buf, int SerialNum, int XPos, int YPos, bool bIsQuit, eCharacter_State bIsFreeze, eCharacter_Direction Direction);
	//===================================================
	// Packet_Send_InGame_ChangetoLobby
	// 게임이 끝나 로비로 전환했다.
	// SerialNum - 플레이어의 인덱스
	static VOID Packet_Send_InGame_ChangetoLobby(CStream* Buf, int SerialNum);
	//===================================================
	// Packet_Send_KeepAlive
	// 클라이언트가 제데로 연결됬는지 체크한다.
	static VOID Packet_Send_KeepAlive(CStream* Buf);
};

