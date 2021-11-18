#pragma once
#include "Libraries.h"

int ReadSector(LPCWSTR  drive, __int64 readPoint, BYTE sector[512]);
void PrintSector(BYTE sector[512]);
void PrintValueSector(BYTE sector[512]);
