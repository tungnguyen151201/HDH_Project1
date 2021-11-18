#include "NTFS.h"
#include "ReadBytes.h"
#include "ReadSecor.h"
#include "BPB.h"
#include "MFT.h"

void ReadNTFS(LPCWSTR drive, BYTE sector[512])
{
    BPB bpb;
    MFT mft;
    //Partition boot sector (VBR)
    ReadSector(drive, 0, sector);    
    ReadBPB(bpb, sector);
    ReadMFT(mft, bpb, sector, drive);
    PrintBPB(bpb);
    PrintMFT(mft);
    cout << "-------------------------------------------------" << endl;
    
    //MFT
    for (int i = 0; i < mft.lastMFTEntry; i++)
    {
        MFTEntry entry;
        ReadMFTEntry(entry, mft.startClusterMFT * bpb.sectorPerCluster, i, drive);
        cout << i << " | ";
        PrintMFTEntry(entry);
        cout << endl;
    }
}
