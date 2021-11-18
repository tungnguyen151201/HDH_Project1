#include "BPB.h"

void ReadBPB(BPB& bpb, BYTE sector[512])
{
	bpb.bytePerSector = ReadBytes("B", 2, sector);
	bpb.sectorPerCluster = ReadBytes("D", 1, sector);
	bpb.sectorPerTrack = ReadBytes("18", 2, sector);
	bpb.numHead = ReadBytes("1A", 2, sector);
	bpb.numSectorOfDisk = ReadBytes("28", 8, sector);
}
void PrintBPB(BPB bpb)
{
    cout << "So byte cho 1 sector: " << bpb.bytePerSector << " byte" << endl;
    cout << "So sector cho 1 cluster: " << bpb.sectorPerCluster << " sector" << endl;
    cout << "So sector cho 1 track: " << bpb.sectorPerTrack << " sector" << endl;
    cout << "So mat dia (head): " << bpb.numHead << " head" << endl;
    cout << "So sector cua o dia: " << bpb.numSectorOfDisk << " sector" << endl;
}
