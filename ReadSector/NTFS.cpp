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
    vector<File> files;
    vector<Folder> folders;
    PrintRootFolder(entries, files, folders);
    char c;
    while (1)
    {
        cout << "Truy xuat thu muc (0), truy xuat tap tin (1), thoat (ESC):\n";
        c = _getch();
        int n = c;
        if (c == '1')
        {
            int id;
            cout << "Nhap id tap tin muon truy xuat: ";
            cin >> id;
            AccessFile(id, files);
        }
        else if (c == '0')
        {
            int id;
            cout << "Nhap id thu muc muon truy xuat: ";
            cin >> id;
            AccessFolder(id, folders);
        }
        else if (n == 27) break;
        else
        {
            cout << "Chon sai chuc nang!\n";
        }
    }
}

