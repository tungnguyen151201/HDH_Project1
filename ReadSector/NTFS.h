#pragma once
#include "Libraries.h"
#include "Struct.h"

void ReadNTFS(LPCWSTR drive, BYTE sector[512]);
void ReadAttributes(int startAtrr, BYTE sector[512], BYTE sector2[512]);
void ReadDataNonResident(int startAttr, BYTE attribute[1024], int typeAttribute);