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
// �濡 ���� ��û�� �Ѵ�.
// Length - �÷��̾� �̸��� ����
// NickName - �÷��̾� �̸�
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
// ���� ���� ��û�� �Ѵ�.
VOID CMakePacket::Packet_Send_Room_GameStart(CStream* Buf)
{
	DWORD PacketLength = sizeof(ePacket_Protocol) + sizeof(DWORD) + sizeof(int);

	Buf->WriteProtocol(ePacket_Protocol::ePacket_Room_GameStart);
	Buf->WriteDWORD(PacketLength);
}

//===================================================
// Packet_Send_Room_UserDataUpdate
// ���� ������ ������Ʈ�� ��û�Ѵ�.
VOID CMakePacket::Packet_Send_Room_UserDataUpdate(CStream* Buf)
{
	DWORD PacketLength = sizeof(ePacket_Protocol) + sizeof(DWORD) + sizeof(int);

	Buf->WriteProtocol(ePacket_Protocol::ePacket_RoomDataUpdate);
	Buf->WriteDWORD(PacketLength);
	Buf->WriteInt(DataManager->SerialNum);
}

//===================================================
// Packet_Send_Room_PlayerReady
// �÷��̾� �غ� ���¸� �����Ѵ�.
// SerialNum - �÷��̾��� �ε���
// ClientNum - Ŭ���̾�Ʈ�� ����
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
// SerialNum - �÷��̾��� �ε���
// �濡�� ���� ��û�� ������.
VOID CMakePacket::Packet_Send_Room_Exit(CStream* Buf, int SerialNum)
{
	DWORD PacketLength = sizeof(ePacket_Protocol) + sizeof(DWORD) + sizeof(int);

	Buf->WriteProtocol(ePacket_Protocol::ePacket_Room_GameQuit);
	Buf->WriteDWORD(PacketLength);
	Buf->WriteInt(SerialNum);
}

//===================================================
// Packet_Send_InGame_All
// �ΰ����� ��� ��ҵ��� ������.
// SerialNum - �÷��̾��� �ε���
// XPos - x��ǥ
// YPos - y��ǥ
// bIsQuit - ���Ῡ��
// bIsFreeze - ���� ���� ����
// Direction - ����
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
// ������ ���� �κ�� ��ȯ�ߴ�.
// SerialNum - �÷��̾��� �ε���
VOID CMakePacket::Packet_Send_InGame_ChangetoLobby(CStream* Buf, int SerialNum)
{
	DWORD PacketLength = sizeof(ePacket_Protocol) + sizeof(DWORD);

	Buf->WriteProtocol(ePacket_Protocol::ePacket_InGame_ChangetoLobby);
	Buf->WriteDWORD(PacketLength);
	Buf->WriteInt(SerialNum);
}

//===================================================
// Packet_Send_KeepAlive
// Ŭ���̾�Ʈ�� ������ �������� üũ�Ѵ�.
VOID CMakePacket::Packet_Send_KeepAlive(CStream* Buf)
{
	DWORD PacketLength = sizeof(ePacket_Protocol) + sizeof(DWORD);

	Buf->WriteProtocol(ePacket_Protocol::ePacket_KeepAlive);
	Buf->WriteDWORD(PacketLength);
}