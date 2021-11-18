#pragma once
#include "Struct.h"
#include "ReadBytes.h"
#include "ReadSecor.h"
#include "Attribute.h"
void ReadMFTEntry(MFTEntry& entry, int startSectorMFT, int i, LPCWSTR drive);
void PrintMFTEntry(MFTEntry entry);