#pragma once

#include "NetWork.h"

class CStream;

//===================================================================
// 패킷을 만들어줄 함수들을 모아둔 클래스.
// 패킷은 기본적으로 0. Protocol, 1. PacketLength 가 들어간다.
// 이후 나머지 필요한 데이터를 넣는다.
class CMakePacket
{
public:
	CMakePacket();
	virtual ~CMakePacket();
public:
	//===============================================================
	// Packet_Send_Room_UserUpdate : 유저 정보가 업데이트되었다.
	// ClientNum - 클라이언트의 수
	// SerialNum - 클라이언트의 고유 번호
	// bIsMaster - 이 플레이어가 방의 방장인가
	// bIsPlayer - 플레이어들의 상태
	// bIsPlayerReady - 플레이어의 준비 상태
	// PlayerName - 플레이어들의 이름
	static VOID Packet_Send_Room_UserUpdate(CStream* Buf, int ClientNum, int SerialNum, bool bIsMaster, int MasterNum, bool bIsPlayer[8], bool bIsPlayerReady[8], std::string PlayerName[8]);
	//===============================================================
	// Packet_Send_Room_GameStart : 모든 클라이언트들에게 게임 플레이 씬으로 전환을 요청
	// PlayerNum : 플레이어의 수
	// SerialNum : 플레이어의 고유 번호
	// TaggerNum : 술래의 번호
	// PlayerState : 플레이어들의 상태
	static VOID Packet_Send_Room_GameStart(CStream* Buf, int PlayerNum, int SerialNum, int TaggerNum, eCharacter_State PlayerState[8]);
	//===============================================================
	// Packet_Send_Room_PlayerReady : 준비버튼을 누른 플레이어를 알린다.
	// SerialNum : 준비버튼을 누른 클라이언트의 번호
	static VOID Packet_Send_Room_PlayerReady(CStream* Buf, CNetWork* NetWork, int SerialNum);
	//===============================================================
	// Packet_Send_Room_GameStartFailed : 게임 시작이 원할하지 않다.
	static VOID Packet_Send_Room_GameStartFailed(CStream* Buf);
	//===============================================================
	// Packet_Send_All_PlayerExit : 플레이어가 종료했다.
	static VOID Packet_Send_Room_Exit(CStream* Buf, int SerialNum);
	//===============================================================
	// Packet_Send_InGame_All : 인게임에서 필요한 플레이어의 정보를 모두 전달한다.
	// PlayerXPos : 플레이어의 X 좌표
	// PlayerYPos : 플레이어의 Y 좌표
	// PlayerQuit : 플레이어가 종료했는가
	// Min : 게임내의 분
	// Sec : 게임내의 초
	// CharacterState : 캐릭터들의 상태
	static VOID Packet_Send_InGame_All(CStream* Buf, CNetWork* NetWork, int PlayerXPos[8], int PlayerYPos[8], bool PlayerQuit[8], int Min, int Sec, eCharacter_State CharacterState[8], bool bIsGameEnd, bool bIsPlayerWin, eCharacter_Direction Direction[8]);
	//===============================================================
	// Packet_Send_InGame_ChangetoLobby : 게임이 끝남, 로비로 전환 요청
	// bIsPlayer - 플레이어가 있는지
	// bIsPlayerReady - 플레이어의 준비 상태
	static VOID Packet_Send_InGame_ChangetoLobby(CStream* Buf, bool bIsPlayer[8], bool bIsPlayerReady[8]);
	//===============================================================
	// Packet_Send_KeepAlive : 클라이언트의 상태 체크
	static VOID Packet_Send_KeepAlive(CStream* Buf);
};

