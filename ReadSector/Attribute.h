#pragma once
#include "Struct.h"
#include "ReadBytes.h"
#include "ReadSecor.h"
vector<Attribute> ReadAttributes(MFTEntry& mftentry, int startAttr, LPCWSTR drive);
string ReadDataNonResident(MFTEntry& mftentry, int startAttr, BYTE attribute[1024], int typeAttribute, LPCWSTR drive, int& fileSize);
int ReadBitmapNonResident(int startAttr, BYTE attribute[1024], int typeAttribute, LPCWSTR drive);
void PrintAttributes(vector<Attribute> attributes, MFTEntry entry);