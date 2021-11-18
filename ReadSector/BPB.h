#pragma once
#include "Libraries.h"
#include "Struct.h"
#include "ReadBytes.h"
void ReadBPB(BPB& bpb, BYTE sector[512]);
void PrintBPB(BPB bpb);