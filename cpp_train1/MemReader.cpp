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

}

void MemReader::Open(DWORD accessRights)
{
}

void MemReader::Close()
{
}