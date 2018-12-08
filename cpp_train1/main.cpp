#include <iostream>
#include "MemReader.h"

void main()
{
	const char* desiredProcess = "ProcessHacker.exe";
	MemReader* mem = new MemReader((char*)desiredProcess);
	mem->Open();
	printf("PID in hexadecimals is %X\n in decimals %d\n", mem->getPID());
	printf("Test string: %s\n", mem->Read(0x01E0A288, 32).toStringA());
	printf("Test float : %f\n", mem->Read(0x06F8E484, 4).toFloat());
	float health = 100.f;
	mem->Write(&health, 0x06F8E484, 4);
	system("PAUSE");
}