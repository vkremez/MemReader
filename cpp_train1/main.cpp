#include <iostream>
#include <Windows.h>
#include <Urlmon.h>
using namespace std;

LPCSTR url = "google.com";
LPCSTR  file = "file.exe";


int main()
{
	MessageBox(0, "Hi from the box", "Box Name", MB_OK);
	HRESULT res  = URLDownloadToFile(0, url, file, 0, 0);
	if (res == S_OK) {
		printf("Ok\n");
	}
	else if (res == E_OUTOFMEMORY) {
		printf("Buffer length invalid, or insufficient memory\n");
	}
	else if (res == INET_E_DOWNLOAD_FAILURE) {
		printf("URL is invalid\n");
	}
	else {
		printf("Other error: %d\n", res);
	}
	return 0;
}