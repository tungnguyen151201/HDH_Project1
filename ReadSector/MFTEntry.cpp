#include "MFTEntry.h"

void ReadMFTEntry(MFTEntry& entry, int startSectorMFT, int i, LPCWSTR drive)
{
	ReadSector(drive, (startSectorMFT + (__int64)i * (__int64)2) * (__int64)512, entry.sector1);
	ReadSector(drive, (startSectorMFT + (__int64)i * (__int64)2 + (__int64)1) * (__int64)512, entry.sector2);
	entry.type = ReadBytes("16", 2, entry.sector1);
	int firstAttributeIndex = ReadBytes("14", 2, entry.sector1);
	entry.attributes = ReadAttributes(entry, firstAttributeIndex, drive);
}
void PrintMFTEntry(MFTEntry entry)
{
	PrintAttributes(entry.attributes, entry);	
}
