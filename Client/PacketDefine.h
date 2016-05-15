#pragma once 

enum ePacket_Protocol
{
	//==================================
	// NULL, 이 패킷이 전달됬다면 분명히 오류일것이다.
	ePacket_NULL,
	//==================================
	// ConnectRequest, 접속 요청을 보낸다.
	ePacket_ConnectRequest,
	//==================================
	// RoomDataUpdate, 방의 정보를 업데이트한다.
	ePacket_RoomDataUpdate,
	//===================================
	// 방에 유저가 들어왔다.
	ePacket_Room_UserAttend,
	//===================================
	// 클라이언트에서 게임 시작이 요청되었다.
	ePacket_Room_GameStart,
	//==================================
	// 플레이어들이 전부 준비되지 않아 게임을 시작할 수 없다.
	ePacket_Room_GameStartFailed,
	//==================================
	// 게임을 종료한다.
	ePacket_Room_GameQuit,
	//===================================
	// 플레이어들에게 자신이 준비되었음을 알린다.
	ePacket_InGame_PlayerReady,
	//===================================
	// 인게임에서 필요한 플레이어의 정보를 모두 전송한다.
	ePacket_InGame_All,
	//===================================
	// 게임이 끝나 로비로 복귀한다.
	ePacket_InGame_ChangetoLobby,
	//===================================
	// 클라이언트의 상태 체크
	ePacket_KeepAlive
};