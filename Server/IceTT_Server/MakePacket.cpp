#include "stdafx.h"
#include "MakePacket.h"

CMakePacket::CMakePacket()
{
}


CMakePacket::~CMakePacket()
{
}

//===============================================================
// Packet_Send_Room_UserUpdate : ���� ������ ������Ʈ�Ǿ���.
// ClientNum - Ŭ���̾�Ʈ�� ��
// SerialNum - Ŭ���̾�Ʈ�� ���� ��ȣ
// bIsMaster - �� �÷��̾ ���� �����ΰ�
// bIsPlayer - �÷��̾���� ����
// bIsPlayerReady - �÷��̾��� �غ� ����
// PlayerName - �÷��̾���� �̸�
VOID CMakePacket::Packet_Send_Room_UserUpdate(CStream* Buf, int ClientNum, int SerialNum, bool bIsMaster, int MasterNum, bool bIsPlayer[8], bool bIsPlayerReady[8], std::string PlayerName[8])
{
	DWORD PacketLength = sizeof(ePacket_Protocol) + sizeof(DWORD) + sizeof(int) + sizeof(int) + sizeof(bool);

	Buf->WriteProtocol(ePacket_Protocol::ePacket_RoomDataUpdate);
	Buf->WriteDWORD(PacketLength);
	Buf->WriteInt(ClientNum);
	Buf->WriteInt(SerialNum);
	Buf->WriteBool(bIsMaster);
	Buf->WriteInt(MasterNum);

	for (int i = 0; i < 8; i++)
	{
		Buf->WriteBool(bIsPlayer[i]);
	}

	for (int i = 0; i < 8; i++)
	{
		Buf->WriteBool(bIsPlayerReady[i]);
	}

	for (int i = 0; i < 8; i++)
	{
		Buf->WriteInt(PlayerName[i].length());
	}

	for (int i = 0; i < 8; i++)
	{
		Buf->WriteChars((char*)PlayerName[i].c_str(), PlayerName[i].length());
	}
}

//===============================================================
// Packet_Send_Room_GameStart : ��� Ŭ���̾�Ʈ�鿡�� ���� �÷��� ������ ��ȯ�� ��û
// PlayerNum : �÷��̾��� ��
// SerialNum : �÷��̾��� ���� ��ȣ
// TaggerNum : ������ ��ȣ
// PlayerState : �÷��̾���� ����
VOID CMakePacket::Packet_Send_Room_GameStart(CStream* Buf, int PlayerNum, int SerialNum, int TaggerNum, eCharacter_State PlayerState[8])
{
	DWORD PacketLength = sizeof(ePacket_Protocol) + sizeof(DWORD) + sizeof(int) + sizeof(int) + sizeof(int);

	Buf->WriteProtocol(ePacket_Protocol::ePacket_Room_GameStart);
	Buf->WriteDWORD(PacketLength);
	Buf->WriteInt(PlayerNum);
	Buf->WriteInt(SerialNum);
	Buf->WriteInt(TaggerNum);

	for (int i = 0; i < 8; i++)
	{
		Buf->WriteCharacterState(PlayerState[i]);
	}
}

//===============================================================
// Packet_Send_Room_PlayerReady : �غ��ư�� ���� �÷��̾ �˸���.
// SerialNum : �غ��ư�� ���� Ŭ���̾�Ʈ�� ��ȣ
VOID CMakePacket::Packet_Send_Room_PlayerReady(CStream* Buf, CNetWork* NetWork, int SerialNum)
{
	DWORD PacketLength = sizeof(ePacket_Protocol) + sizeof(DWORD) + sizeof(int);

	Buf->WriteProtocol(ePacket_Protocol::ePacket_InGame_PlayerReady);
	Buf->WriteDWORD(PacketLength);
	Buf->WriteInt(SerialNum);
}

//===============================================================
// Packet_Send_Room_GameStartFailed : ���� ������ �������� �ʴ�.
VOID CMakePacket::Packet_Send_Room_GameStartFailed(CStream* Buf)
{
	DWORD PacketLength = sizeof(ePacket_Protocol);

	Buf->WriteProtocol(ePacket_Protocol::ePacket_Room_GameStartFailed);
	Buf->WriteDWORD(PacketLength);
}

//===============================================================
// Packet_Send_All_PlayerExit : �÷��̾ �����ߴ�.
VOID CMakePacket::Packet_Send_Room_Exit(CStream* Buf, int SerialNum)
{
	DWORD PacketLength = sizeof(ePacket_Protocol) + sizeof(int);

	Buf->WriteProtocol(ePacket_Protocol::ePacket_Room_GameQuit);
	Buf->WriteDWORD(PacketLength);
	Buf->WriteInt(SerialNum);
}

//===============================================================
// Packet_Send_InGame_All : �ΰ��ӿ��� �ʿ��� �÷��̾��� ������ ��� �����Ѵ�.
// PlayerXPos : �÷��̾��� X ��ǥ
// PlayerYPos : �÷��̾��� Y ��ǥ
// PlayerQuit : �÷��̾ �����ߴ°�
// Min : ���ӳ��� ��
// Sec : ���ӳ��� ��
// CharacterState : ĳ���͵��� ����
VOID CMakePacket::Packet_Send_InGame_All(CStream* Buf, CNetWork* NetWork, int PlayerXPos[8], int PlayerYPos[8], bool PlayerQuit[8], int Min, int Sec, eCharacter_State CharacterState[8], bool bIsGameEnd, bool bIsPlayerWin, eCharacter_Direction Direction[8])
{
	DWORD PacketLength = sizeof(ePacket_Protocol) + sizeof(DWORD) + sizeof(NetWork->PlayerXPos) + sizeof(NetWork->PlayerYPos) + sizeof(NetWork->bIsPlayerQuit);

	Buf->WriteProtocol(ePacket_Protocol::ePacket_InGame_All);
	Buf->WriteDWORD(PacketLength);

	for (int i = 0; i < 8; i++)
	{
		Buf->WriteInt(PlayerXPos[i]);
	}

	for (int i = 0; i < 8; i++)
	{
		Buf->WriteInt(PlayerYPos[i]);
	}

	for (int i = 0; i < 8; i++)
	{
		Buf->WriteBool(PlayerQuit[i]);
	}

	Buf->WriteInt(Min);
	Buf->WriteInt(Sec);

	for (int i = 0; i < 8; i++)
	{
		Buf->WriteCharacterState(CharacterState[i]);
	}

	Buf->WriteBool(bIsGameEnd);
	Buf->WriteBool(bIsPlayerWin);

	for (int i = 0; i < 8; i++)
	{
		Buf->WriteCharacterDirection(Direction[i]);
	}

	for (int i = 0; i < 8; i++)
	{
		Buf->WriteBool(NetWork->bIsPlayer[i]);
	}
}

//===============================================================
// Packet_Send_InGame_ChangetoLobby : ������ ����, �κ�� ��ȯ ��û
// bIsPlayer - �÷��̾ �ִ���
// bIsPlayerReady - �÷��̾��� �غ� ����
VOID CMakePacket::Packet_Send_InGame_ChangetoLobby(CStream* Buf, bool bIsPlayer[8], bool bIsPlayerReady[8])
{
	DWORD PacketLength = sizeof(ePacket_Protocol) + sizeof(DWORD);

	Buf->WriteProtocol(ePacket_Protocol::ePacket_InGame_ChangetoLobby);
	Buf->WriteDWORD(PacketLength);

	for (int i = 0; i < 8; i++)
	{
		Buf->WriteBool(bIsPlayer[i]);
	}

	for (int i = 0; i < 8; i++)
	{
		Buf->WriteBool(bIsPlayerReady[i]);
	}
}

//===============================================================
// Packet_Send_KeepAlive : Ŭ���̾�Ʈ�� ���� üũ
VOID CMakePacket::Packet_Send_KeepAlive(CStream* Buf)
{
	DWORD PacketLength = sizeof(ePacket_Protocol) + sizeof(DWORD);

	Buf->WriteProtocol(ePacket_Protocol::ePacket_KeepAlive);
	Buf->WriteDWORD(PacketLength);
}