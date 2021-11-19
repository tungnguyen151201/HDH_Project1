#include "NTFS.h"
#include "ReadBytes.h"
#include "ReadSecor.h"
#include "BPB.h"
#include "MFT.h"
#include "File.h"
#include "File.h"

void ReadNTFS(LPCWSTR drive, BYTE sector[512])
{
    BPB bpb;
    MFT mft;
    vector<MFTEntry> entries;

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
        bool check = ReadMFTEntry(entry, mft.startClusterMFT * bpb.sectorPerCluster, i, drive);
        if (check == true)
        {
            entry.id = i;
            entries.push_back(entry);
        }
        /*PrintMFTEntry(entry);
        cout << endl;*/
    }
    PrintFolderTree(entries);
}

