#pragma once
#include <Windows.h>
#include <TlHelp32.h>

// DEFINE CLASS FOR THE PROJECT
class MemReader
{
public:
	MemReader(char* procname, int buffersize = 32);
	~MemReader(void);
	void Open(DWORD accessRights = PROCESS_ALL_ACCESS);
	void Close();
	DWORD getPID();
private:
	void GetPid();
	char* m_pName;
	HANDLE m_hProc;
	DWORD m_pid;
	BYTE* m_buffer;
	int m_buffersize;
};