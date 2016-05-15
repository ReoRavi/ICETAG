#pragma once

#include "NetWork.h"

class CStream;

//===================================================================
// ��Ŷ�� ������� �Լ����� ��Ƶ� Ŭ����.
// ��Ŷ�� �⺻������ 0. Protocol, 1. PacketLength �� ����.
// ���� ������ �ʿ��� �����͸� �ִ´�.
class CMakePacket
{
public:
	CMakePacket();
	virtual ~CMakePacket();
public:
	//===============================================================
	// Packet_Send_Room_UserUpdate : ���� ������ ������Ʈ�Ǿ���.
	// ClientNum - Ŭ���̾�Ʈ�� ��
	// SerialNum - Ŭ���̾�Ʈ�� ���� ��ȣ
	// bIsMaster - �� �÷��̾ ���� �����ΰ�
	// bIsPlayer - �÷��̾���� ����
	// bIsPlayerReady - �÷��̾��� �غ� ����
	// PlayerName - �÷��̾���� �̸�
	static VOID Packet_Send_Room_UserUpdate(CStream* Buf, int ClientNum, int SerialNum, bool bIsMaster, int MasterNum, bool bIsPlayer[8], bool bIsPlayerReady[8], std::string PlayerName[8]);
	//===============================================================
	// Packet_Send_Room_GameStart : ��� Ŭ���̾�Ʈ�鿡�� ���� �÷��� ������ ��ȯ�� ��û
	// PlayerNum : �÷��̾��� ��
	// SerialNum : �÷��̾��� ���� ��ȣ
	// TaggerNum : ������ ��ȣ
	// PlayerState : �÷��̾���� ����
	static VOID Packet_Send_Room_GameStart(CStream* Buf, int PlayerNum, int SerialNum, int TaggerNum, eCharacter_State PlayerState[8]);
	//===============================================================
	// Packet_Send_Room_PlayerReady : �غ��ư�� ���� �÷��̾ �˸���.
	// SerialNum : �غ��ư�� ���� Ŭ���̾�Ʈ�� ��ȣ
	static VOID Packet_Send_Room_PlayerReady(CStream* Buf, CNetWork* NetWork, int SerialNum);
	//===============================================================
	// Packet_Send_Room_GameStartFailed : ���� ������ �������� �ʴ�.
	static VOID Packet_Send_Room_GameStartFailed(CStream* Buf);
	//===============================================================
	// Packet_Send_All_PlayerExit : �÷��̾ �����ߴ�.
	static VOID Packet_Send_Room_Exit(CStream* Buf, int SerialNum);
	//===============================================================
	// Packet_Send_InGame_All : �ΰ��ӿ��� �ʿ��� �÷��̾��� ������ ��� �����Ѵ�.
	// PlayerXPos : �÷��̾��� X ��ǥ
	// PlayerYPos : �÷��̾��� Y ��ǥ
	// PlayerQuit : �÷��̾ �����ߴ°�
	// Min : ���ӳ��� ��
	// Sec : ���ӳ��� ��
	// CharacterState : ĳ���͵��� ����
	static VOID Packet_Send_InGame_All(CStream* Buf, CNetWork* NetWork, int PlayerXPos[8], int PlayerYPos[8], bool PlayerQuit[8], int Min, int Sec, eCharacter_State CharacterState[8], bool bIsGameEnd, bool bIsPlayerWin, eCharacter_Direction Direction[8]);
	//===============================================================
	// Packet_Send_InGame_ChangetoLobby : ������ ����, �κ�� ��ȯ ��û
	// bIsPlayer - �÷��̾ �ִ���
	// bIsPlayerReady - �÷��̾��� �غ� ����
	static VOID Packet_Send_InGame_ChangetoLobby(CStream* Buf, bool bIsPlayer[8], bool bIsPlayerReady[8]);
	//===============================================================
	// Packet_Send_KeepAlive : Ŭ���̾�Ʈ�� ���� üũ
	static VOID Packet_Send_KeepAlive(CStream* Buf);
};

