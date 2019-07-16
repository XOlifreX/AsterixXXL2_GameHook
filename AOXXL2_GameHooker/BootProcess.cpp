/*#include <stdio.h>
#include <cstdio>
#include <windows.h>
#include <tlhelp32.h>
#include <conio.h>
#include <string>
#include "PE.h"

const char* target = "D:\\Games\\Atari\\Asterix & ObelixPosition XXL 2\\Astérix & Obélix XXL2\\Asterix2.exe";
const char* target2 = "D:\\Games\\Atari\\Asterix & ObelixPosition XXL 2\\Astérix & Obélix XXL2\\Gamemodule.elb";
char arg[] = "";
char buffer[4];

STARTUPINFO si;
PROCESS_INFORMATION pi;
_CONTEXT myContext;


bool LoadProcess(const char* Filename, char* args) {

	printf("Loading process...\n");
	if (!CreateProcess(Filename,						// No module name (use command line)
		args,											// Command line.
		NULL,											// Process handle not inheritable.
		NULL,											// Thread handle not inheritable.
		FALSE,											// Set hanle inheritance to FALSE.
		CREATE_SUSPENDED | CREATE_NEW_PROCESS_GROUP,	// Suspended creation flags.
		NULL,											// Use parent's environment block.
		NULL,											// Use parent's starting directory.
		&si,											// Pointer to STARTUPINFO struct.
		&pi												// Pointer to PROCESS_INFORMATION srtruct.
	))
	{
		printf("Loading process failed!\n");

		_getch();
		return false;
	}

	myContext.ContextFlags = CONTEXT_ALL; // 0x00010000 + 1 + 2 + 4 + 8 + 0x10;
	printf("Process loaded succesfully.\n\n");

	return true;

}


bool runTo(DWORD address, bool rapidFire, DWORD EIP)
{

	if (EIP != 0) {
		GetThreadContext(pi.hThread, &myContext); // Get the context with the register values
		myContext.Eip = EIP;					  // Set one of the register values
		SetThreadContext(pi.hThread, &myContext); // Set the new Context on the thread
	}

	ReadProcessMemory(pi.hProcess, (LPVOID)address, buffer, 4, 0);

	if (!WriteProcessMemory(pi.hProcess, (LPVOID)address, "\xEB\xFE", 2, 0))
	{
		printf("WriteProcessMemory failed: %08X \n", address);
		// TerminateProcess(pi.hProcess, 0);

		_getch();
		return false;
	}

	ResumeThread(pi.hThread);

	while (GetThreadContext(pi.hThread, &myContext))
	{
		if (rapidFire) {
			if (!WriteProcessMemory(pi.hProcess, (LPVOID)address, "\xEB\xFE", 2, 0))
			{
				printf("WriteProcessMemory failed: %08X \n", address);
				// TerminateProcess(pi.hProcess, 0);

				_getch();
				return false;
			}
		}
		if (myContext.Eip == address)
			break;
	}

	SuspendThread(pi.hThread);

	// Did we exit cause we crashed?
	if (!GetThreadContext(pi.hThread, &myContext))
	{
		printf("Running to address failed...\n");
		// TerminateProcess(pi.hProcess, 0);

		_getch();
		return false;
	}

	WriteProcessMemory(pi.hProcess, (LPVOID)address, buffer, 4, 0);

	return true;
}

int main_t() {

	if (!LoadProcess(target, arg))
	{
		_getch();
		return 0;
	}

	PEStruct PEFile = getPEFileInformation(target);

	// Get the entrypoint.
	DWORD OEP = PEFile.image_nt_headers.OptionalHeader.AddressOfEntryPoint + PEFile.image_nt_headers.OptionalHeader.ImageBase;

	if (!runTo(OEP, true, 0)) {
		printf("Failed to run to the entry point.\n");
		// TerminateThread(pi.hThread, 0);

		_getch();
		return 0;
	}

	ResumeThread(pi.hThread);

	DWORD exitCode = STILL_ACTIVE;

	// Main loop
	do {
		GetExitCodeProcess(pi.hProcess, &exitCode);
	} while (exitCode == STILL_ACTIVE);

	printf("Process exited with Exit code: %d\n\n", exitCode);

	_getch();

	return 0;

}*/