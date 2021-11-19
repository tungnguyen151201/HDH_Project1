#include "MFTEntry.h"

bool ReadMFTEntry(MFTEntry& entry, int startSectorMFT, int i, LPCWSTR drive)
{
	entry.idSector = startSectorMFT + (__int64)i * (__int64)2;
	ReadSector(drive, entry.idSector * (__int64)512, entry.sector1);
	ReadSector(drive, (entry.idSector + (__int64)1) * (__int64)512, entry.sector2);	
	string signal = ReadValueBytes("0", 4, entry.sector1);
	if (signal != "FILE")
	{
		return false;
	}
	entry.type = ReadBytes("16", 2, entry.sector1);
	entry.sectors.push_back(entry.idSector);
	int firstAttributeIndex = ReadBytes("14", 2, entry.sector1);
	entry.attributes = ReadAttributes(entry, firstAttributeIndex, drive);
	return true;
}
void PrintMFTEntry(MFTEntry entry)
{
	PrintAttributes(entry.attributes, entry);	
}
