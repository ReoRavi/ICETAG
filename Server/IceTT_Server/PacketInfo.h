#pragma once 

enum ePacket_Protocol
{
	//==================================
	// NULL, �� ��Ŷ�� ���މ�ٸ� �и��� �����ϰ��̴�.
	ePacket_NULL,
	//==================================
	// ConnectRequest, ���� ��û�� ������.
	ePacket_ConnectRequest,
	//==================================
	// RoomDataUpdate, ���� ������ ������Ʈ�Ѵ�.
	ePacket_RoomDataUpdate,
	//===================================
	// �濡 ������ ���Դ�.
	ePacket_Room_UserAttend,
	//===================================
	// Ŭ���̾�Ʈ���� ���� ������ ��û�Ǿ���.
	ePacket_Room_GameStart,
	//==================================
	// �÷��̾���� ���� �غ���� �ʾ� ������ ������ �� ����.
	ePacket_Room_GameStartFailed,
	//==================================
	// ������ �����Ѵ�.
	ePacket_Room_GameQuit,
	//===================================
	// �÷��̾�鿡�� �ڽ��� �غ�Ǿ����� �˸���.
	ePacket_InGame_PlayerReady,
	//===================================
	// �ΰ��ӿ��� �ʿ��� �÷��̾��� ������ ��� �����Ѵ�.
	ePacket_InGame_All,
	//===================================
	// ������ ���� �κ�� �����Ѵ�.
	ePacket_InGame_ChangetoLobby,
	//===================================
	// Ŭ���̾�Ʈ�� ���� üũ
	ePacket_KeepAlive
};