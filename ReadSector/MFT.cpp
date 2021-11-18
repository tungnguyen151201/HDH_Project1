#include "MFT.h"

void ReadMFT(MFT& mft, BPB bpb, BYTE sector[512], LPCWSTR drive)
{
	mft.startClusterMFT = ReadBytes("30", 8, sector);
	mft.bytePerMFTEntry = pow(2, abs(ReadSignedBytes("40", 1, sector)));

	MFTEntry entry;
	ReadMFTEntry(entry, mft.startClusterMFT * bpb.sectorPerCluster, 0, drive);
	mft.lastMFTEntry = GetLastMFTEntry(entry);
}
int GetLastMFTEntry(MFTEntry entry)
{
	for (int i = 0; i < entry.attributes.size(); i++)
	{
		Attribute attribute = entry.attributes[i];
		if (attribute.type == 176) return attribute.Bitmap.magicNumber;
	}
	return 0;
}
void PrintMFT(MFT mft)
{
	cout << "Cluster bat dau cua MFT: " << mft.startClusterMFT << endl;
	cout << "Kich thuoc cua MFT entry: " << mft.bytePerMFTEntry << " byte" << endl;	
}
