#pragma once
#include "Struct.h"
#include "ReadBytes.h"
#include "ReadSecor.h"
#include "Attribute.h"
bool ReadMFTEntry(MFTEntry& entry, int startSectorMFT, int i, LPCWSTR drive);
void PrintMFTEntry(MFTEntry entry);