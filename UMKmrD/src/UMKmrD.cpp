#include <iostream>
#include <fstream>
#include "engine.h"

PVOID getNtOsKrnlBase() {
    auto kernelModules = engine::proc::getKernelModulesInfo();

    for (auto& kModule : kernelModules) {
        char* moduleName = (char*)kModule.FullPathName + kModule.OffsetToFileName;

        if (strcmp(moduleName, "ntoskrnl.exe") == 0) {
            return kModule.ImageBase;
        }

    }
    return NULL;
}

PVOID readNtOsKrnlImage() {
    return (PVOID)LoadLibraryA("ntoskrnl.exe");
}

int main(int argc, char* argv[])
{   
    auto output = argv[1];
    auto option = argv[2];
    
    if (!output) {
        printf("Please Provide An Output File Path.");
        return -1;
    }
    std::ofstream outputFile { output };

    auto ntoskrnlBase = getNtOsKrnlBase();

    if (ntoskrnlBase == NULL) {
        return -1;
    }
    
    auto ntoskrnlImage = readNtOsKrnlImage();

    if (ntoskrnlImage == NULL) {
        return -1;
    }
    auto ntoskrnlExports = engine::proc::getModuleExports(ntoskrnlImage);
    if (!option) {

        for (auto& kExport : ntoskrnlExports) {
            auto name = kExport.name;
            auto functionVA = (PVOID)((DWORD_PTR)ntoskrnlBase + kExport.functionRVA);

            char buff[100];

            sprintf_s(buff, "%s -> 0x%p\n", name, functionVA);
            outputFile << buff;

        }

        printf("Dumped %zu Kernel Routines Addresses.", ntoskrnlExports.size());
    }

    else {
        for (auto& kExport : ntoskrnlExports) {
            auto name = kExport.name;
            auto functionVA = (PVOID)((DWORD_PTR)ntoskrnlBase + kExport.functionRVA);

            if (strcmp(kExport.name, option) == 0) {

                char buff[100];
                sprintf_s(buff, "%s -> 0x%p\n", name, functionVA);

                printf(buff);
                outputFile << buff;
            }
            
        }
    }
    
    outputFile.close();
    
}
