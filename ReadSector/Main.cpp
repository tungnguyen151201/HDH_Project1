#include "ReadSecor.h"
#include "ReadBytes.h"
#include "NTFS.h"

int main(int argc, char** argv)
{
    BYTE sector[512]; //1 sector (thường) có 512 byte
    LPCWSTR drive = L"\\\\.\\F:"; //ổ cứng
    SetConsoleOutputCP(65001);
    ReadNTFS(drive, sector);
    return 0;
}