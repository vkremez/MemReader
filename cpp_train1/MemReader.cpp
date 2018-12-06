#include "MemReader.h"
//. 
MemReader::MemReader(char * procname, int buffersize)
{
	int len = strlen(procname) + 1;
	m_pName = new char[len];
	strcpy_s(m_pName, len, procname);
	m_buffer = new byte[buffersize];
}

MemReader::~MemReader()
{
	delete[] m_pName;
	delete[] m_buffer;
}

void MemReader::GetPid()
{
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 pInfo;
	pInfo.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(snapshot, &pInfo))
	{
		while (Process32Next(snapshot, &pInfo))
		{
			if (_stricmp(m_pName, pInfo.szExeFile) == 0)
			{
				m_pid = pInfo.th32ProcessID;
				CloseHandle(snapshot);
				return;
			}

		}

	}
	CloseHandle(snapshot);
	m_pid = 0;
	return;
}

void MemReader::Open(DWORD accessRights)
{
	GetPid();
	m_hProc = OpenProcess(accessRights, false, m_pid);
}

void MemReader::Close()
{
	CloseHandle(m_hProc);
}

DWORD MemReader::getPID()
{
	return m_pid;

}