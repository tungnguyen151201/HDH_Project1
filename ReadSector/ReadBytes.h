#pragma once
#include "Libraries.h"
#include "Struct.h"

string HexToBinary(string hex);
int BinaryToDecimal(string binary);
string DecimalToBinary(int decimal);
int HexToDecimal(string hex);
int ReadSignedBytes(string offset, int numByte, BYTE sector[512]);
int ReadBytes(string offset, int numByte, BYTE sector[512]);
string ReadValueBytes(string offset, int numByte, BYTE sector[512]);
string ReadHexBytes(string offset, int numByte, BYTE sector[512]);
int ReadAttributeBytes(int offset, int numByte, BYTE sector[1024]);
string ReadHexAttributeBytes(int offset, int numByte, BYTE sector[1024]);
string ReadValueAttributeBytes(int offset, int numByte, BYTE sector[1024]);
string ReadHexDataBytes(string offset, int numByte, BYTE sector[512]);
string ReadFileName(int offset, int numByte, BYTE sector[1024]);