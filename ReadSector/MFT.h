#pragma once
#include "Struct.h"
#include "Libraries.h"
#include "ReadBytes.h"
#include "MFTEntry.h"
void ReadMFT(MFT& mft, BPB bpb, BYTE sector[512], LPCWSTR drive);
void PrintMFT(MFT mft);
int GetLastMFTEntry(MFTEntry entry);