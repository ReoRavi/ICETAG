#include "stdafx.h"
#include "MakePacket.h"


CMakePacket::CMakePacket()
{
}


CMakePacket::~CMakePacket()
{
}

//===================================================
// Packet_Send_ConnectToRoom_ConnectRequest
// 방에 접속 요청을 한다.
// Length - 플레이어 이름의 길이
// NickName - 플레이어 이름
VOID CMakePacket::Packet_Send_ConnectToRoom_ConnectRequest(CStream* Buf, int Length, char* NickName)
{
	DWORD PacketLength = sizeof(ePacket_Protocol) + sizeof(DWORD) + sizeof(NickName);

	char* Nick = new char[Length];
	ZeroMemory(Nick, Length);
	Nick = NickName;

	Buf->WriteProtocol(ePacket_Protocol::ePacket_ConnectRequest);
	Buf->WriteDWORD(PacketLength);
	Buf->WriteInt(Length);
	Buf->WriteChars(Nick, Length);
}

//===================================================
// Packet_Send_Room_GameStart
// 게임 시작 요청을 한다.
VOID CMakePacket::Packet_Send_Room_GameStart(CStream* Buf)
{
	DWORD PacketLength = sizeof(ePacket_Protocol) + sizeof(DWORD) + sizeof(int);

	Buf->WriteProtocol(ePacket_Protocol::ePacket_Room_GameStart);
	Buf->WriteDWORD(PacketLength);
}

//===================================================
// Packet_Send_Room_UserDataUpdate
// 유저 데이터 업데이트를 요청한다.
VOID CMakePacket::Packet_Send_Room_UserDataUpdate(CStream* Buf)
{
	DWORD PacketLength = sizeof(ePacket_Protocol) + sizeof(DWORD) + sizeof(int);

	Buf->WriteProtocol(ePacket_Protocol::ePacket_RoomDataUpdate);
	Buf->WriteDWORD(PacketLength);
	Buf->WriteInt(DataManager->SerialNum);
}

//===================================================
// Packet_Send_Room_PlayerReady
// 플레이어 준비 상태를 갱신한다.
// SerialNum - 플레이어의 인덱스
// ClientNum - 클라이언트의 갯수
VOID CMakePacket::Packet_Send_Room_PlayerReady(CStream* Buf, int SerialNum, int ClientNum)
{
	DWORD PacketLength = sizeof(ePacket_Protocol) + sizeof(DWORD) + sizeof(int);

	Buf->WriteProtocol(ePacket_Protocol::ePacket_InGame_PlayerReady);
	Buf->WriteDWORD(PacketLength);
	Buf->WriteInt(SerialNum);
	Buf->WriteInt(ClientNum);
}

//===================================================
// Packet_Send_Room_Exit
// SerialNum - 플레이어의 인덱스
// 방에서 나감 요청을 보낸다.
VOID CMakePacket::Packet_Send_Room_Exit(CStream* Buf, int SerialNum)
{
	DWORD PacketLength = sizeof(ePacket_Protocol) + sizeof(DWORD) + sizeof(int);

	Buf->WriteProtocol(ePacket_Protocol::ePacket_Room_GameQuit);
	Buf->WriteDWORD(PacketLength);
	Buf->WriteInt(SerialNum);
}

//===================================================
// Packet_Send_InGame_All
// 인게임의 모든 요소들을 보낸다.
// SerialNum - 플레이어의 인덱스
// XPos - x좌표
// YPos - y좌표
// bIsQuit - 종료여부
// bIsFreeze - 얼음 상태 여부
// Direction - 방향
VOID CMakePacket::Packet_Send_InGame_All(CStream* Buf, int SerialNum, int XPos, int YPos, bool bIsQuit, eCharacter_State bIsFreeze,  eCharacter_Direction Direction)
{
	DWORD PacketLength = sizeof(ePacket_Protocol) + sizeof(DWORD) + sizeof(int) + sizeof(int) + sizeof(int) + sizeof(bool) + sizeof(eCharacter_State) + sizeof(eCharacter_Direction);

	Buf->WriteProtocol(ePacket_Protocol::ePacket_InGame_All);
	Buf->WriteDWORD(PacketLength);
	Buf->WriteInt(SerialNum);
	Buf->WriteInt(XPos);
	Buf->WriteInt(YPos);
	Buf->WriteBool(bIsQuit);
	Buf->WriteCharacterState(bIsFreeze);
	Buf->WriteCharacterDirection(Direction);
}

//===================================================
// Packet_Send_InGame_ChangetoLobby
// 게임이 끝나 로비로 전환했다.
// SerialNum - 플레이어의 인덱스
VOID CMakePacket::Packet_Send_InGame_ChangetoLobby(CStream* Buf, int SerialNum)
{
	DWORD PacketLength = sizeof(ePacket_Protocol) + sizeof(DWORD);

	Buf->WriteProtocol(ePacket_Protocol::ePacket_InGame_ChangetoLobby);
	Buf->WriteDWORD(PacketLength);
	Buf->WriteInt(SerialNum);
}

//===================================================
// Packet_Send_KeepAlive
// 클라이언트가 제데로 연결됬는지 체크한다.
VOID CMakePacket::Packet_Send_KeepAlive(CStream* Buf)
{
	DWORD PacketLength = sizeof(ePacket_Protocol) + sizeof(DWORD);

	Buf->WriteProtocol(ePacket_Protocol::ePacket_KeepAlive);
	Buf->WriteDWORD(PacketLength);
}