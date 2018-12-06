#include <iostream>
#include "MemReader.h"

void main()
{
	const char* desiredProcess = "notepad.exe";
	MemReader* mem = new MemReader((char*)desiredProcess);
	mem->Open();
	printf("PID in hexadecimal: %X\n", mem->getPID());
	system("PAUSE");
}
