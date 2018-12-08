#pragma once
#include <Windows.h>
#include <TlHelp32.h>

// DEFINE CLASS FOR THE PROJECT
class MemReader
{
public:
	MemReader(char* procname, size_t buffersize = 32);
	~MemReader(void);
	
	void Open(DWORD accessRights = PROCESS_ALL_ACCESS);
	void Close();

	void Write(void* ptr, DWORD to, size_t size);
	void Write(void* ptr, DWORD to, size_t size, DWORD memprotect);
	MemReader& Read(DWORD from, size_t size);
	MemReader& Read(DWORD from, size_t size, DWORD memProtect);

	DWORD getPID();

	double		toDouble();
	float			toFloat();
	
	UINT64		toUINT64();
	INT64		toINT64();
	
	UINT32		toUINT32();
	INT32		toINT32();
	
	UINT16		toUINT16();
	short int	toINT16();

	UINT8		toUINT8();
	char			toINT8();

	char*			toStringA();
	wchar_t*	toStringW();


private:
	void GetPid();
	char* m_pName;
	HANDLE m_hProc;
	DWORD m_pid;
	BYTE* m_buffer;
	int m_buffersize;
};