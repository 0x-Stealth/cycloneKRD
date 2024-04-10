#pragma once
#include<windows.h>
#include<TlHelp32.h>
#include<vector>
#include "./Syscalls/Syscalls.h"
#include<optional>

#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)

using std::vector;

namespace engine {

	namespace proc {
		class ModuleExport {
		public:
			LPCSTR name;
			WORD ordinal;
			DWORD functionRVA; // NWORD functionRVA; 
		};


		vector<RTL_PROCESS_MODULE_INFORMATION> getKernelModulesInfo();
		
		vector<proc::ModuleExport> getModuleExports(PVOID moduleBase);
	}
	
}
