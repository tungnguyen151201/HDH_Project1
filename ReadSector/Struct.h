#pragma once
#include "Libraries.h"
struct BPB
{
	int bytePerSector; //Số byte cho 1 sector
	int sectorPerCluster; //Số sector cho 1 cluster
	int sectorPerTrack; //Số sector cho 1 track
	int numHead; //Số head
	__int64 numSectorOfDisk; //Số sector của ổ đĩa	
};
struct MFT
{
	int startClusterMFT; //Cluster bắt đầu MFT
	double bytePerMFTEntry; //Số byte cho 1 MFT Entry
	int lastMFTEntry; //MFT Entry cuối cùng
};
struct AttributeData
{
	string content;	
};
struct AttributeFileName
{
	string filename;
	int parentFolderIndex; //địa chỉ thư mục cha (MFT entry)
};
struct AttributeBitmap
{
	int magicNumber;
};
struct Attribute
{
	int type; //loại Attribute
	int startIndex; //vị trí bắt đầu Attribute
	int size; //kích thước Attribute
	int startContentIndex; //vị trí bắt đầu phần nội dung Attribute
	int contentSize; //kích thước phần nội dung Attribute
	AttributeBitmap Bitmap;
	AttributeData Data;
	AttributeFileName FileName;
};
struct MFTEntry
{
	int id;
	__int64 idSector; //sector bắt đầu MFT entry
	int type; //0: tập tin đã xóa, 1: tập tin được cấp phát, 2: thư mục đã xóa, 3: thư mục được cấp phát
	BYTE sector1[512]; //nửa entry đầu
	BYTE sector2[512]; //nửa entry cuối
	vector<Attribute> attributes; //danh sách các Attribute
	vector<__int64> sectors; //các sector mà data được lưu trữ
};
struct File
{
	int id;
	string name;
	int size;
	string data;
	int parentIndex;
	vector<__int64> sectors; //các sector lưu trữ
};
struct Folder
{
	int id;
	string name;
	vector<File> child;
	vector<Folder> folderchild;
	int parentIndex;
	vector<__int64> sectors; //các sector lưu trữ
};