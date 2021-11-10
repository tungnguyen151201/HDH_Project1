#include "ReadSecor.h"
#include "ReadBytes.h"

int main(int argc, char** argv)
{
    BYTE sector[512]; //1 sector (thường) có 512 byte
    LPCWSTR drive = L"\\\\.\\F:"; //ổ cứng
    ReadSector(drive, 0, sector); //đọc sector đầu tiên
    //ReadSector(drive, x*512, sector); //đọc sector thứ x
    PrintSector(sector);
    cout << "Offset B, 2 byte: " << ReadBytes("B", 2, sector);
    return 0;
}