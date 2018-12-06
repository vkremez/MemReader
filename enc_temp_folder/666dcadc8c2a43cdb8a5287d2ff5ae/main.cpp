#include <iostream>
#include "MemReader.h"

void main()
{
	const char* desiredProcess = "notepad.exe";
	MemReader* mem = new MemReader((char*)desiredProcess);
	mem->Open();
	printf("PID in hexadecimals is %X\n in decimals %d\n", mem->getPID());
	system("PAUSE");
}
