#pragma once

//================================================
// CStream : ū ���� �ȿ��� �����͸� ���ϰ� �ְ�, ���°��� ���.
class CStream 
{
public:
	CStream();
	virtual ~CStream();

public :
	// ������ ���� �޸� ��ġ
	int			m_BufferReadPoint;
	// ������ �۽� �޸� ��ġ
	int			m_BufferWritePoint;
	// ������ ũ��
	int			m_BufferSize;
	// ���� ����
	char*	m_RecvBuffer;
	// �۽� ����
	char*	m_SendBuffer;
	
public :
	// �ʱ�ȭ
	VOID Init();

	// ���۸� �����Ѵ�.
	VOID SetBuffer(int iBufferSize);
	// ���۸� �����Ѵ�.
	VOID ReleaseBuffer();

	// ���� ���� �޸� ��ġ �ʱ�ȭ
	VOID ResetSendPoint();
	// ���� �۽� �޸� ��ġ �ʱ�ȭ
	VOID ResetRecvPoint();
	// �۽� ���� �ʱ�ȭ
	VOID ClearSendBuffer();
	// ���� ���� �ʱ�ȭ
	VOID ClearRecvBuffer();
	// ������ ����� ��´�.
	int GetBufferSize();

	// Write(�ڷ���) - (�ڷ���)������ ���ۿ� �ִ´�.
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

	// Read(�ڷ���) - (�ڷ���)������ ���۷κ��� �д´�.
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