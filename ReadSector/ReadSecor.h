#pragma once
#include "Libraries.h"

int ReadSector(LPCWSTR  drive, int readPoint, BYTE sector[512]);
void PrintSector(BYTE sector[512]);
