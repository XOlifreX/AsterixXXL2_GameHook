#include <stdio.h>
#include <cstdio>
#include <windows.h>
#include <tlhelp32.h>
#include <conio.h>
#include <string>
#include "PE.h"

#ifndef MAKEULONGLONG
#define MAKEULONGLONG(ldw, hdw) ((ULONGLONG(hdw) << 32) | ((ldw) & 0xFFFFFFFF))
#endif

#ifndef MAXULONGLONG
#define MAXULONGLONG ((ULONGLONG)~((ULONGLONG)0))
#endif

const char* target = "D:\\Games\\Atari\\Asterix & Obelix XXL 2\\Astérix & Obélix XXL2\\Asterix2.exe";
const char* target2 = "D:\\Games\\Atari\\Asterix & Obelix XXL 2\\Astérix & Obélix XXL2\\Gamemodule.elb";
char arg[] = "";
char buffer[4];

STARTUPINFO si;
PROCESS_INFORMATION pi;
_CONTEXT myContext;

HANDLE gmProcess;
HANDLE gmThread;

DWORD ObelixPosition = 0;
DWORD AsterixPosition = 0;
DWORD IdefixPosition = 0;

DWORD ObelixAltitude = 0;
DWORD AsterixAltitude = 0;
DWORD IdefixAltitude = 0;

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

bool runTo(DWORD address, bool rapidFire, DWORD EIP, HANDLE hProcess, HANDLE hThread)
{

	ResumeThread(gmThread);

	if (EIP != 0) {
		GetThreadContext(hThread ? hThread : pi.hThread, &myContext); // Get the context with the register values
		myContext.Eip = EIP;					  // Set one of the register values
		SetThreadContext(hThread ? hThread : pi.hThread, &myContext); // Set the new Context on the thread
	}

	ReadProcessMemory(hProcess ? hProcess : pi.hProcess, (LPVOID)address, buffer, 4, 0);

	if (!WriteProcessMemory(hProcess ? hProcess : pi.hProcess, (LPVOID)address, "\xEB\xFE", 2, 0))
	{
		printf("WriteProcessMemory failed: %08X \n", address);
		// TerminateProcess(pi.hProcess, 0);

		_getch();
		return false;
	}

	ResumeThread(hThread ? hThread : pi.hThread);

	while (GetThreadContext(hThread ? hThread : pi.hThread, &myContext))
	{
		if (rapidFire) {
			if (!WriteProcessMemory(hProcess ? hProcess : pi.hProcess, (LPVOID)address, "\xEB\xFE", 2, 0))
			{
				printf("WriteProcessMemory failed: %08X \n", address);
				// TerminateProcess(pi.hProcess, 0);

				_getch();
				return false;
			}
		}
		printf("0x%08X.\n", myContext.Eip);
		if (myContext.Eip == address)
			break;
	}

	SuspendThread(hThread ? hThread : pi.hThread);

	// Did we exit cause we crashed?
	if (!GetThreadContext(hThread ? hThread : pi.hThread, &myContext))
	{
		printf("Running to address failed...\n");
		// TerminateProcess(pi.hProcess, 0);

		_getch();
		return false;
	}

	WriteProcessMemory(hProcess ? hProcess : pi.hProcess, (LPVOID)address, buffer, 4, 0);

	return true;
}


bool GetGamemoduleProcessInfo() {

	bool found = false;
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	ULONGLONG ullMinCreateTime = MAXULONGLONG;
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	HANDLE hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, NULL);

	if (Process32First(snapshot, &entry) == TRUE)
	{
		while (Process32Next(snapshot, &entry) == TRUE)
		{
			if (_stricmp(entry.szExeFile, "gamemodule.elb") == 0)
			{

				gmProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);

				printf("Gamemodule process found.\n");

				THREADENTRY32 th32;
				th32.dwSize = sizeof(THREADENTRY32);
				BOOL bOK = TRUE;

				if (Thread32First(hThreadSnap, &th32) == TRUE) {

					while (Thread32Next(hThreadSnap, &th32) == TRUE)
					{
						// Is this thread from our Gamemodule process?
						if (th32.th32OwnerProcessID == entry.th32ProcessID) {

							HANDLE temp = OpenThread(THREAD_ALL_ACCESS | THREAD_GET_CONTEXT, TRUE, th32.th32ThreadID);

							if (temp) {
								FILETIME afTimes[4] = { 0 };
								if (GetThreadTimes(temp,
									&afTimes[0], &afTimes[1], &afTimes[2], &afTimes[3])) {
									ULONGLONG ullTest = MAKEULONGLONG(afTimes[0].dwLowDateTime,
										afTimes[0].dwHighDateTime);
									if (ullTest && ullTest < ullMinCreateTime) {
										ullMinCreateTime = ullTest;

										gmThread = temp;
										printf("Main thread found.\n");
										found = true;
									}
								}
							}
						}
					}
				}
			}
		}
	}

	CloseHandle(snapshot);

	return found;

}

void retrieveCharacterPositions(DWORD result) {

	result += 0x3D4;

	IdefixPosition = result;
	IdefixAltitude = result + 0x4;
	result += 0x968;
	ObelixPosition = result;
	ObelixAltitude = result + 0x4;
	result += 0x968;
	AsterixPosition = result;
	AsterixPosition = result + 0x4;

	printf("Asterix: +0x%08X, Obelix: +0x%08X, Idefix: +0x%08X\n", ObelixPosition, AsterixPosition, IdefixPosition);

}

void checkKeyEvents() {

	DWORD newPosition;
	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		printf("Key UP.\n");

		SuspendThread(gmThread);
		ReadProcessMemory(gmProcess, (void*)(AsterixPosition), &newPosition, sizeof(DWORD), NULL);

		printf("Origional: %08X", newPosition);
		if (newPosition + 1000 <= 0xFFFFFFFF)
			newPosition += 1000;
		printf("Edited: %08X", newPosition);

		WriteProcessMemory(gmProcess, (void*)(AsterixPosition), &newPosition, sizeof(DWORD), NULL);
		ResumeThread(gmThread);
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		printf("Key DOWN.\n");

		SuspendThread(gmThread);
		ReadProcessMemory(gmProcess, (void*)(AsterixPosition), &newPosition, sizeof(DWORD), NULL);

		printf("Origional: %08X", newPosition);
		if (newPosition - 1000 >= 0x0)
			newPosition -= 1000;
		printf("Edited: %08X", newPosition);

		WriteProcessMemory(gmProcess, (void*)(AsterixPosition), &newPosition, sizeof(DWORD), NULL);
		ResumeThread(gmThread);
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		printf("Key LEFT.\n");

		SuspendThread(gmThread);
		ReadProcessMemory(gmProcess, (void*)(AsterixPosition), &newPosition, sizeof(DWORD), NULL);

		printf("Origional: %08X", newPosition);
		if (newPosition + 300 <= 0xFFFFFFFF)
			newPosition += 300;
		printf("Edited: %08X", newPosition);

		WriteProcessMemory(gmProcess, (void*)(AsterixPosition), &newPosition, sizeof(DWORD), NULL);
		ResumeThread(gmThread);
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		printf("Key RIGHT.\n");

		SuspendThread(gmThread);
		ReadProcessMemory(gmProcess, (void*)(AsterixPosition), &newPosition, sizeof(DWORD), NULL);

		printf("Origional: %08X", newPosition);
		if (newPosition - 300 >= 0x0)
			newPosition -= 300;
		printf("Edited: %08X", newPosition);

		WriteProcessMemory(gmProcess, (void*)(AsterixPosition), &newPosition, sizeof(DWORD), NULL);
		ResumeThread(gmThread);
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
		printf("Key RIGHT.\n");

		SuspendThread(gmThread);
		ReadProcessMemory(gmProcess, (void*)(AsterixPosition), &newPosition, sizeof(DWORD), NULL);

		printf("Origional: %08X", newPosition);
		if (newPosition - 300 >= 0x0)
			newPosition -= 300;
		printf("Edited: %08X", newPosition);

		WriteProcessMemory(gmProcess, (void*)(AsterixPosition), &newPosition, sizeof(DWORD), NULL);
		ResumeThread(gmThread);
	}

}

bool lookForCharacterPositionsMemLocation() {

	DWORD result;
	if (!runTo(0x004E3600, true, 0, gmProcess, gmThread)) {
		printf("Failed to run to 0x004E3600.\n");
		// TerminateThread(pi.hThread, 0);

		_getch();
		return false;
	}

	if (myContext.Eax == 0x006118E8) {
		printf("Address found: +x%08X\n", myContext.Esi);
		result = myContext.Esi;
	}
	else {
		printf("Did not find 0x006118E8. Found 0x%08X instead.\n", myContext.Eax);
	}

	if ((result & 0xFFFFF000) != ((IdefixPosition - 0x3D4) & 0xFFFFF000)) {
		printf("New character mem position found!\n");
		retrieveCharacterPositions(result);
	}

	ResumeThread(gmThread);

	return true;

}


int main() {

	if (!LoadProcess(target, arg))
	{
		_getch();
		return 0;
	}

	PEStruct PEFile = getPEFileInformation(target);

	// Get the entrypoint.
	DWORD OEP = PEFile.image_nt_headers.OptionalHeader.AddressOfEntryPoint + PEFile.image_nt_headers.OptionalHeader.ImageBase;

	// Run to the entry point
	if (!runTo(OEP, true, 0, NULL, NULL)) {
		printf("Failed to run to the entry point.\n");

		_getch();
		return 0;
	}

	ResumeThread(pi.hThread);

	DWORD exitCode;
	// Wait till Asterix2.exe has exited.
	do {
		GetExitCodeProcess(pi.hProcess, &exitCode);
	} while (exitCode == STILL_ACTIVE);
	printf("Process exited with Exit code: %d\n\n", exitCode);

	// Get process info of the Asterix2 Gamemodule process.
	if (!GetGamemoduleProcessInfo()) {
		printf("Could not find Gamemodule process main thread. Check if the gamemodule process is running and run again.\n");
		_getch();

		return -1;
	}

	// Wait and retrieve the character positions once available.
	if (!lookForCharacterPositionsMemLocation())
		return 0;

	// Main loop
	do {
		GetExitCodeProcess(gmProcess, &exitCode);
		if (exitCode != STILL_ACTIVE)
			break;

		if (!lookForCharacterPositionsMemLocation())
			return 0;

		checkKeyEvents();
	} while (exitCode == STILL_ACTIVE);

	return 0;

}