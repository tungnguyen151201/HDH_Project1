#pragma once
#include "Libraries.h"
#include "MFTEntry.h"
void ReadFile(File& file, MFTEntry entry);
void PrintFile(File file);
void ReadFolder(Folder& folder, MFTEntry entry);
void ReadChildFolder(Folder& folder, vector<File> files);
void PrintFolder(Folder folder);
void PrintRootFolder(vector<MFTEntry> entries, vector<File>& files, vector<Folder>& folders);
void AccessFolder(int id, vector<Folder> folders);
void AccessFile(int id, vector<File> files);