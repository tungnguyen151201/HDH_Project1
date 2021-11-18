#include "ReadSecor.h"

__int64 myFileSeek(HANDLE hf, __int64 distance, DWORD MoveMethod)
{
    LARGE_INTEGER li;

    li.QuadPart = distance;

    li.LowPart = SetFilePointer(hf,
        li.LowPart,
        &li.HighPart,
        MoveMethod);

    if (li.LowPart == INVALID_SET_FILE_POINTER && GetLastError()
        != NO_ERROR)
    {
        li.QuadPart = -1;
    }

    return li.QuadPart;
}

int ReadSector(LPCWSTR  drive, __int64 readPoint, BYTE sector[512])
{
    int retCode = 0;
    DWORD bytesRead;
    HANDLE device = NULL;

    device = CreateFile(drive,    // Drive to open
        GENERIC_READ,           // Access mode
        FILE_SHARE_READ | FILE_SHARE_WRITE,        // Share Mode
        NULL,                   // Security Descriptor
        OPEN_EXISTING,          // How to create
        0,                      // File attributes
        NULL);                  // Handle to template

    if (device == INVALID_HANDLE_VALUE) // Open Error
    {
        printf("CreateFile: %u\n", GetLastError());
        exit(1);
    }
    LARGE_INTEGER nFileSize;
    nFileSize.u.LowPart = readPoint & 0xFFFFFFFF;
    nFileSize.u.HighPart = readPoint >> 32;
    SetFilePointerEx(device, nFileSize, 0, FILE_BEGIN);

    if (!ReadFile(device, sector, 512, &bytesRead, NULL))
    {
        printf("ReadFile: %u\n", GetLastError());       
    }
    else
    {
        //cout << "Sector " << readPoint / 512 << ":\n";
    }
}

void PrintSector(BYTE sector[512])
{
    for (int i = 0; i < 512; i++)
    {
        printf("%02X ", sector[i]);
        if (i % 16 == 15)
        {           
            printf("\n");
        }
    }
}

void PrintValueSector(BYTE sector[512])
{
    for (int i = 0; i < 512; i++)
    {
        printf("%c", sector[i]);
        //if (i % 16 == 15)
        //{
        //    printf("\n");
        //}
    }
}