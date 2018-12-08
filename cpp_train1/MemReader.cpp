#include "MemReader.h"
//. 
MemReader::MemReader(char * procname, size_t buffersize) : m_pid(0), m_buffersize(buffersize)
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

void MemReader::Write(void * ptr, DWORD to, size_t size)
{
	WriteProcessMemory(m_hProc, (LPVOID)to, ptr, size, NULL);
}

void MemReader::Write(void * ptr, DWORD to, size_t size, DWORD memprotect)
{
	DWORD oldMemProtect = 0;
	VirtualProtectEx(m_hProc, (LPVOID)to, size, memprotect, &oldMemProtect);
	WriteProcessMemory(m_hProc, (LPVOID)to, ptr, size, NULL);
	VirtualProtectEx(m_hProc, (LPVOID)to, size, oldMemProtect, &oldMemProtect);
}

MemReader& MemReader::Read(DWORD from, size_t size)
{
	memset(m_buffer, 0, m_buffersize);
	ReadProcessMemory(m_hProc, (LPCVOID)from, m_buffer, size, NULL);
	return *this;
}
MemReader& MemReader::Read(DWORD from, size_t size, DWORD memProtect)
{
	DWORD oldMemProtect = 0;

	memset(m_buffer, 0, m_buffersize);
	VirtualProtectEx(m_hProc, (LPVOID)from, size, memProtect, &oldMemProtect);
	ReadProcessMemory(m_hProc, (LPCVOID)from, m_buffer, size, NULL);
	VirtualProtectEx(m_hProc, (LPVOID)from, size, oldMemProtect, &oldMemProtect);
	return *this;
}

DWORD MemReader::getPID()
{
	return m_pid;

}

double MemReader::toDouble()
{
	double v = 0;
	memcpy(&v, m_buffer, sizeof(double));
	return v;
}
float	MemReader::toFloat()
{
	float v = 0;
	memcpy(&v, m_buffer, sizeof(float));
	return v;
}
UINT64	MemReader::toUINT64()
{
	UINT64 v = 0;
	memcpy(&v, m_buffer, sizeof(UINT64));
	return v;
}
INT64 MemReader::toINT64()
{
	INT64 v = 0;
	memcpy(&v, m_buffer, sizeof(INT64));
	return v;
}
UINT32	MemReader::toUINT32()
{
	UINT32 v = 0;
	memcpy(&v, m_buffer, sizeof(UINT32));
	return v;
}
INT32 MemReader::toINT32()
{
	INT32 v = 0;
	memcpy(&v, m_buffer, sizeof(INT32));
	return v;
}
UINT16	MemReader::toUINT16()
{
	UINT16 v = 0;
	memcpy(&v, m_buffer, sizeof(UINT16));
	return v;
}
short int MemReader::toINT16()
{
	short int v = 0;
	memcpy(&v, m_buffer, sizeof(short int));
	return v;
}
UINT8 MemReader::toUINT8()
{
	UINT8 v = 0;
	memcpy(&v, m_buffer, sizeof(UINT8));
	return v;
}
char	MemReader::toINT8()
{
	char v = 0;
	memcpy(&v, m_buffer, sizeof(char));
	return v;
}
char* MemReader::toStringA()
{
	return (char*)m_buffer;
}
wchar_t* MemReader::toStringW()
{
	return (wchar_t*)m_buffer;
}
