#include "ReadSecor.h"
#include "ReadBytes.h"

int main(int argc, char** argv)
{
    BYTE sector[512]; //1 sector (thường) có 512 byte
    LPCWSTR drive = L"\\\\.\\C:"; //ổ cứng
    ReadSector(drive, 0, sector); //đọc sector đầu tiên
    //ReadSector(drive, x*512, sector); //đọc sector thứ x
    //PrintSector(sector);
    cout << "Kich thuoc mot sector: " << ReadBytes("B", 2, sector) << endl;
    cout << "So sector trong mot cluster: " << ReadBytes("D", 1, sector) << endl;
    cout << "Cluster bat dau cua MFT: " << ReadBytes("30", 8, sector) << endl;
    cout << "MFT:" << endl;
    ReadSector(drive, ReadBytes("30", 8, sector) * 512, sector); //đọc sector thứ x
    PrintSector(sector);
    return 0;
}