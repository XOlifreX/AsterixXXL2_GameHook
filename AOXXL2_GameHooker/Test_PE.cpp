#include <iostream> // Standard C++ library for console I/O
#include <fstream>
#include <string> // Standard C++ Library for string manip
#include <conio.h>

#include <Windows.h> // WinAPI Header
#include <TlHelp32.h> //WinAPI Process API
#include "PE.h"


// use this if you want to read the executable from disk
HANDLE MapFileToMemory(LPCSTR filename)
{
	std::streampos size;
	std::fstream file(filename, std::ios::in | std::ios::binary | std::ios::ate);
	if (file.is_open())
	{
		size = file.tellg();

		char* Memblock = new char[size]();

		file.seekg(0, std::ios::beg);
		file.read(Memblock, size);
		file.close();

		return Memblock;
	}
	return 0;
}

int RunPortableExecutable(const char* CurrentFilePath)
{
	IMAGE_DOS_HEADER* DOSHeader; // For Nt DOS Header symbols
	IMAGE_NT_HEADERS* NtHeader; // For Nt PE Header objects & symbols
	IMAGE_SECTION_HEADER* SectionHeader;

	PROCESS_INFORMATION PI;
	STARTUPINFOA SI;

	CONTEXT* CTX;

	DWORD* ImageBase; //Base address of the image
	void* pImageBase; // Pointer to the image base

	int count;
	ZeroMemory(&PI, sizeof(PI)); // Null the memory
	ZeroMemory(&SI, sizeof(SI)); // Null the memory

	if (CreateProcessA(CurrentFilePath, NULL, NULL, NULL, FALSE,
		CREATE_SUSPENDED, NULL, NULL, &SI, &PI)) // Create a new instance of current
												 //process in suspended state, for the new image.
	{
		PEStruct PEFile = getPEFileInformation(CurrentFilePath);
		DOSHeader = &PEFile.image_dos_header; // Initialize Variable
		NtHeader = &PEFile.image_nt_headers; // Initialize
		// Allocate memory for the context.
		CTX = LPCONTEXT(VirtualAlloc(NULL, sizeof(CTX), MEM_COMMIT, PAGE_READWRITE));
		CTX->ContextFlags = CONTEXT_FULL; // Context is allocated

		if (GetThreadContext(PI.hThread, LPCONTEXT(CTX))) //if context is in thread
		{
			// Read instructions
			ReadProcessMemory(PI.hProcess, LPCVOID(CTX->Ebx + 8), LPVOID(&ImageBase), 4, 0);

			pImageBase = VirtualAllocEx(PI.hProcess, LPVOID(NtHeader->OptionalHeader.ImageBase),
				NtHeader->OptionalHeader.SizeOfImage, 0x3000, PAGE_EXECUTE_READWRITE);

			// Write the image to the process
			// WriteProcessMemory(PI.hProcess, pImageBase, Image, NtHeader->OptionalHeader.SizeOfHeaders, NULL);

			for (count = 0; count < NtHeader->FileHeader.NumberOfSections; count++)
			{
				SectionHeader = PEFile.image_section_header;// PIMAGE_SECTION_HEADER(DWORD(Image) + DOSHeader->e_lfanew + 248 + (count * 40));

				WriteProcessMemory(PI.hProcess, LPVOID(DWORD(pImageBase) + SectionHeader->VirtualAddress),
					LPVOID(PEFile.fileSize + SectionHeader->PointerToRawData), SectionHeader->SizeOfRawData, 0);
			}
			WriteProcessMemory(PI.hProcess, LPVOID(CTX->Ebx + 8),
				LPVOID(&NtHeader->OptionalHeader.ImageBase), 4, 0);

			// Move address of entry point to the eax register
			CTX->Eax = DWORD(pImageBase) + NtHeader->OptionalHeader.AddressOfEntryPoint;
			SetThreadContext(PI.hThread, LPCONTEXT(CTX)); // Set the context
			ResumeThread(PI.hThread); //´Start the process/call main()

			DWORD exitCode = STILL_ACTIVE;

			// Main loop
			do {
				GetExitCodeProcess(PI.hProcess, &exitCode);
				printf("%d\n", exitCode);
			} while (exitCode == STILL_ACTIVE);


			printf("Format message failed with 0x%x\n", GetLastError());
			return 0; // Operation was successful.
		}
	}
}

int main_t()
{
	const char* CurrentFilePath = "D:\\Games\\Atari\\Asterix & Obelix XXL 2\\Astérix & Obélix XXL2\\Asterix2.exe";
	RunPortableExecutable(CurrentFilePath); // run executable from the array

	_getch();

	return 0;
}