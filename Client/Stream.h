#pragma once

//================================================
// CStream : 큰 버퍼 안에서 데이터를 편하게 넣고, 빼는것을 담당.
class CStream 
{
public:
	CStream();
	virtual ~CStream();

public :
	// 버퍼의 수신 메모리 위치
	int			m_BufferReadPoint;
	// 버퍼의 송신 메모리 위치
	int			m_BufferWritePoint;
	// 버퍼의 크기
	int			m_BufferSize;
	// 수신 버퍼
	char*	m_RecvBuffer;
	// 송신 버퍼
	char*	m_SendBuffer;
	
public :
	// 초기화
	VOID Init();

	// 버퍼를 세팅한다.
	VOID SetBuffer(int iBufferSize);
	// 버퍼를 해제한다.
	VOID ReleaseBuffer();

	// 버퍼 수신 메모리 위치 초기화
	VOID ResetSendPoint();
	// 버퍼 송신 메모리 위치 초기화
	VOID ResetRecvPoint();
	// 송신 버퍼 초기화
	VOID ClearSendBuffer();
	// 수신 버퍼 초기화
	VOID ClearRecvBuffer();
	// 버퍼의 사이즈를 얻는다.
	int GetBufferSize();

	// Write(자료형) - (자료형)변수를 버퍼에 넣는다.
	BOOL WriteChar(char Data);
	BOOL WriteChars(char* Data, int ValueSize);
	BOOL WriteString(std::string Data);
	BOOL WriteBool(bool Data);
	BOOL WriteShort(short Data);
	BOOL WriteInt(int Data);
	BOOL WriteDWORD(DWORD Data);
	BOOL WriteFloat(float Data);
	BOOL WriteLong(long Data);
	BOOL WriteDouble(double Data);
	BOOL WriteCharacterState(eCharacter_State Data);
	BOOL WriteProtocol(ePacket_Protocol Data);
	BOOL WriteCharacterDirection(eCharacter_Direction Data);

	// Read(자료형) - (자료형)변수를 버퍼로부터 읽는다.
	BOOL ReadChar(char* Data);
	BOOL ReadChars(char* Data, int ValueSize);
	BOOL ReadString(std::string* Data);
	BOOL ReadBool(bool* Data);
	BOOL ReadShort(short* Data);
	BOOL ReadInt(int* Data);
	BOOL ReadDWORD(DWORD* Data);
	BOOL ReadFloat(float* Data);
	BOOL ReadLong(long* Data);
	BOOL ReadDouble(double* Data);
	BOOL ReadCharacterState(eCharacter_State* Data);
	BOOL ReadProtocol(ePacket_Protocol* Data);
	BOOL ReadCharacterDirection(eCharacter_Direction* Data);
};