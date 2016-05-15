#pragma once

//=============================================
// CMakePacket : ��Ŷ�� �����.
class CMakePacket
{
public:
	CMakePacket();
	virtual ~CMakePacket();

public :
	//===================================================
	// Packet_Send_ConnectToRoom_ConnectRequest
	// �濡 ���� ��û�� �Ѵ�.
	// Length - �÷��̾� �̸��� ����
	// NickName - �÷��̾� �̸�
	static VOID Packet_Send_ConnectToRoom_ConnectRequest(CStream* Buf, int Length, char* NickName);
	//===================================================
	// Packet_Send_Room_GameStart
	// ���� ���� ��û�� �Ѵ�.
	static VOID Packet_Send_Room_GameStart(CStream* Buf);
	//===================================================
	// Packet_Send_Room_UserDataUpdate
	// ���� ������ ������Ʈ�� ��û�Ѵ�.
	static VOID Packet_Send_Room_UserDataUpdate(CStream* Buf);
	//===================================================
	// Packet_Send_Room_PlayerReady
	// �÷��̾� �غ� ���¸� �����Ѵ�.
	// SerialNum - �÷��̾��� �ε���
	// ClientNum - Ŭ���̾�Ʈ�� ����
	static VOID Packet_Send_Room_PlayerReady(CStream* Buf, int SerialNum, int ClientNum);
	//===================================================
	// Packet_Send_Room_Exit
	// SerialNum - �÷��̾��� �ε���
	// �濡�� ���� ��û�� ������.
	static VOID Packet_Send_Room_Exit(CStream* Buf, int SerialNum);
	//===================================================
	// Packet_Send_InGame_All
	// �ΰ����� ��� ��ҵ��� ������.
	// SerialNum - �÷��̾��� �ε���
	// XPos - x��ǥ
	// YPos - y��ǥ
	// bIsQuit - ���Ῡ��
	// bIsFreeze - ���� ���� ����
	// Direction - ����
	static VOID Packet_Send_InGame_All(CStream* Buf, int SerialNum, int XPos, int YPos, bool bIsQuit, eCharacter_State bIsFreeze, eCharacter_Direction Direction);
	//===================================================
	// Packet_Send_InGame_ChangetoLobby
	// ������ ���� �κ�� ��ȯ�ߴ�.
	// SerialNum - �÷��̾��� �ε���
	static VOID Packet_Send_InGame_ChangetoLobby(CStream* Buf, int SerialNum);
	//===================================================
	// Packet_Send_KeepAlive
	// Ŭ���̾�Ʈ�� ������ �������� üũ�Ѵ�.
	static VOID Packet_Send_KeepAlive(CStream* Buf);
};

