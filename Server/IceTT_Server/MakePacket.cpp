#include "stdafx.h"
#include "MakePacket.h"

CMakePacket::CMakePacket()
{
}


CMakePacket::~CMakePacket()
{
}

//===============================================================
// Packet_Send_Room_UserUpdate : 유저 정보가 업데이트되었다.
// ClientNum - 클라이언트의 수
// SerialNum - 클라이언트의 고유 번호
// bIsMaster - 이 플레이어가 방의 방장인가
// bIsPlayer - 플레이어들의 상태
// bIsPlayerReady - 플레이어의 준비 상태
// PlayerName - 플레이어들의 이름
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
// Packet_Send_Room_GameStart : 모든 클라이언트들에게 게임 플레이 씬으로 전환을 요청
// PlayerNum : 플레이어의 수
// SerialNum : 플레이어의 고유 번호
// TaggerNum : 술래의 번호
// PlayerState : 플레이어들의 상태
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
// Packet_Send_Room_PlayerReady : 준비버튼을 누른 플레이어를 알린다.
// SerialNum : 준비버튼을 누른 클라이언트의 번호
VOID CMakePacket::Packet_Send_Room_PlayerReady(CStream* Buf, CNetWork* NetWork, int SerialNum)
{
	DWORD PacketLength = sizeof(ePacket_Protocol) + sizeof(DWORD) + sizeof(int);

	Buf->WriteProtocol(ePacket_Protocol::ePacket_InGame_PlayerReady);
	Buf->WriteDWORD(PacketLength);
	Buf->WriteInt(SerialNum);
}

//===============================================================
// Packet_Send_Room_GameStartFailed : 게임 시작이 원할하지 않다.
VOID CMakePacket::Packet_Send_Room_GameStartFailed(CStream* Buf)
{
	DWORD PacketLength = sizeof(ePacket_Protocol);

	Buf->WriteProtocol(ePacket_Protocol::ePacket_Room_GameStartFailed);
	Buf->WriteDWORD(PacketLength);
}

//===============================================================
// Packet_Send_All_PlayerExit : 플레이어가 종료했다.
VOID CMakePacket::Packet_Send_Room_Exit(CStream* Buf, int SerialNum)
{
	DWORD PacketLength = sizeof(ePacket_Protocol) + sizeof(int);

	Buf->WriteProtocol(ePacket_Protocol::ePacket_Room_GameQuit);
	Buf->WriteDWORD(PacketLength);
	Buf->WriteInt(SerialNum);
}

//===============================================================
// Packet_Send_InGame_All : 인게임에서 필요한 플레이어의 정보를 모두 전달한다.
// PlayerXPos : 플레이어의 X 좌표
// PlayerYPos : 플레이어의 Y 좌표
// PlayerQuit : 플레이어가 종료했는가
// Min : 게임내의 분
// Sec : 게임내의 초
// CharacterState : 캐릭터들의 상태
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
// Packet_Send_InGame_ChangetoLobby : 게임이 끝남, 로비로 전환 요청
// bIsPlayer - 플레이어가 있는지
// bIsPlayerReady - 플레이어의 준비 상태
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
// Packet_Send_KeepAlive : 클라이언트의 상태 체크
VOID CMakePacket::Packet_Send_KeepAlive(CStream* Buf)
{
	DWORD PacketLength = sizeof(ePacket_Protocol) + sizeof(DWORD);

	Buf->WriteProtocol(ePacket_Protocol::ePacket_KeepAlive);
	Buf->WriteDWORD(PacketLength);
}