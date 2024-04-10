#include "engine.h"
using namespace engine;

vector<RTL_PROCESS_MODULE_INFORMATION> proc::getKernelModulesInfo() {
	vector<RTL_PROCESS_MODULE_INFORMATION> kernelModules;
	ULONG infoSize = 0;
	Sw3NtQuerySystemInformation(SystemModuleInformation, NULL, 0, &infoSize);
	LPVOID pProcessInfo = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, infoSize);

	Sw3NtQuerySystemInformation(SystemModuleInformation, pProcessInfo, infoSize, &infoSize);
	auto modulesInfo = (PRTL_PROCESS_MODULES)pProcessInfo;

	for (size_t i = 0; i < modulesInfo->NumberOfModules; i++)
	{
		RTL_PROCESS_MODULE_INFORMATION moduleInfo = modulesInfo->Modules[i];
		kernelModules.push_back(moduleInfo);
	}

	return kernelModules;
}


vector<proc::ModuleExport> proc::getModuleExports(PVOID moduleBase) {
	vector<proc::ModuleExport> moduleExports;

	auto dosHeader = (PIMAGE_DOS_HEADER)moduleBase;
	auto ntHeader = (PIMAGE_NT_HEADERS)((DWORD_PTR)moduleBase + dosHeader->e_lfanew);
	auto optHeader = ntHeader->OptionalHeader;
	auto eatDir = optHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
	auto eat = (PIMAGE_EXPORT_DIRECTORY)((DWORD_PTR)moduleBase + eatDir.VirtualAddress);
	auto names = (PDWORD)((DWORD_PTR)moduleBase + eat->AddressOfNames);
	auto ordinals = (PWORD)((DWORD_PTR)moduleBase + eat->AddressOfNameOrdinals);
	auto functions = (PDWORD)((DWORD_PTR)moduleBase + eat->AddressOfFunctions);
	
	for (size_t i = 0; i < eat->NumberOfNames; i++)
	{
		LPCSTR name = (LPCSTR)((DWORD_PTR)moduleBase + names[i]);	
		WORD ordinal = (WORD)(ordinals[i]);
		DWORD RVA = functions[ordinal];

		moduleExports.push_back(
			proc::ModuleExport{
				name,
				ordinal,
				RVA
			}
		);
		

	}

	return moduleExports;
}
