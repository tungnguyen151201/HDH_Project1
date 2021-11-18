#include "Attribute.h"
#include <Windows.h>
vector<Attribute> ReadAttributes(MFTEntry mftentry, int startAttr, LPCWSTR drive)
{
    vector<Attribute> attributes;
    BYTE entry[1024];
    for (int i = 0; i < 512; i++)
    {
        entry[i] = mftentry.sector1[i];
    }
    for (int i = 513; i < 1024; i++)
    {
        int j = i - 513;
        entry[i] = mftentry.sector2[j];
    }
    Attribute attribute;
    attribute.startIndex = startAttr;
    attribute.size = ReadAttributeBytes(startAttr + 4, 4, entry);//kích thước attribute đầu tiên (STANDARD_INFOMATION)
    while (startAttr + attribute.size < 1024)
    {
        if (attribute.size < 0) break;
        BYTE* array = new BYTE[attribute.size]; //khởi tạo 1 attribute
        for (int i = 0; i < attribute.size; i++)
        {
            array[i] = entry[startAttr + i];
        }
        attribute.type = ReadAttributeBytes(0, 3, array);
        attribute.startContentIndex = ReadAttributeBytes(20, 2, array);
        int residentFlag = ReadAttributeBytes(8, 1, array);
        if (attribute.type == 48) //FILE_NAME
        {
            int fileNameLength = ReadAttributeBytes(attribute.startContentIndex + 64, 1, array);
            attribute.FileName.parentFolderIndex = ReadAttributeBytes(attribute.startContentIndex, 8, array);
            attribute.FileName.filename = ReadFileName(attribute.startContentIndex + 66, fileNameLength, array);
        }
        else if (attribute.type == 128) //DATA
        {
            if (attribute.FileName.filename[0] != '$')
            {
                attribute.contentSize = ReadAttributeBytes(16, 4, array);
                if (residentFlag == 0)
                {
                    attribute.Data.content = ReadValueAttributeBytes(attribute.startContentIndex, attribute.contentSize, array);
                }
                else
                {
                    attribute.Data.content = ReadDataNonResident(startAttr, array, attribute.type, drive, attribute.contentSize);
                }
            }
        }
        else if (attribute.type == 176) //BITMAP
        {
            attribute.Bitmap.magicNumber = ReadBitmapNonResident(startAttr, array, attribute.type, drive);
        }
        else if (attribute.type == 16 || attribute.type == 32 || attribute.type == 64 || 
            attribute.type == 80 || attribute.type == 96 || attribute.type == 112 || attribute.type == 144 || 
            attribute.type == 160 || attribute.type == 192 || attribute.type == 208 || attribute.type == 224 || 
            attribute.type == 256)
        {
            startAttr += attribute.size;
            attribute.size = ReadAttributeBytes(startAttr + 4, 4, entry);
            continue;
        }
        else break;
        startAttr += attribute.size;
        attribute.size = ReadAttributeBytes(startAttr + 4, 4, entry);
        attributes.push_back(attribute);
    }
    return attributes;
}
string ReadDataNonResident(int startAttr, BYTE attribute[1024], int typeAttribute, LPCWSTR drive, int& fileSize)
{
    string s = "";
    BYTE sector[512];
    fileSize = ReadAttributeBytes(48, 8, attribute);
    int indexDataRun = ReadAttributeBytes(32, 2, attribute); //Data Run đầu tiên
    string firstByte = ReadHexAttributeBytes(indexDataRun, 1, attribute);
    int firstHaftByte = firstByte[0] - '0';
    int secondHaftByte = firstByte[1] - '0';
    while (firstByte != "00")
    {
        int sizeOfDataBlock = ReadAttributeBytes(indexDataRun + 1, secondHaftByte, attribute); //kích thước của data, đơn vị cluster
        __int64 readPointData = (__int64)ReadAttributeBytes(indexDataRun + secondHaftByte + 1, firstHaftByte, attribute) * (__int64)8 * (__int64)512; //Địa chỉ chứa data              
        if (typeAttribute == 128) //DATA
        {
            for (int i = 0; i < sizeOfDataBlock * 8; i++)
            {
                ReadSector(drive, readPointData + (__int64)i * (__int64)512, sector);
                s += ReadValueBytes("0", 512, sector);
            }
        }
        indexDataRun += firstHaftByte + secondHaftByte + 1;
        firstByte = ReadHexAttributeBytes(indexDataRun, 1, attribute);
        firstHaftByte = firstByte[0] - '0';
        secondHaftByte = firstByte[1] - '0';
    }
    return s;
}
int ReadBitmapNonResident(int startAttr, BYTE attribute[1024], int typeAttribute, LPCWSTR drive)
{
    string bitmap = "";
    BYTE sector[512];
    int indexDataRun = 64; //Data Run đầu tiên
    string firstByte = ReadHexAttributeBytes(indexDataRun, 1, attribute);
    int firstHaftByte = firstByte[0] - '0';
    int secondHaftByte = firstByte[1] - '0';
    while (firstByte != "00")
    {
        int sizeOfDataBlock = ReadAttributeBytes(indexDataRun + 1, secondHaftByte, attribute); //kích thước của data, đơn vị cluster
        __int64 readPointData = (__int64)ReadAttributeBytes(indexDataRun + secondHaftByte + 1, firstHaftByte, attribute) * (__int64)8 * (__int64)512; //Địa chỉ chứa data       
        if (typeAttribute == 176) //BITMAP
        {
            for (int i = 7; i >= 0; i--)
            {
                ReadSector(drive, readPointData + (__int64)i * (__int64)512, sector);
                bitmap += HexToBinary(ReadHexBytes("0", 512, sector));
            }
            int lastIndexUsed = 0;
            int n = bitmap.length();
            for (int i = n - 1; i >= 0; i--)
            {
                if (bitmap[i] == '1')
                {
                    lastIndexUsed = i;
                }
            }
            return n - lastIndexUsed;
            break;
        }
        indexDataRun += firstHaftByte + secondHaftByte + 1;
        firstByte = ReadHexAttributeBytes(indexDataRun, 1, attribute);
        firstHaftByte = firstByte[0] - '0';
        secondHaftByte = firstByte[1] - '0';
    }
    return 0;
}
void PrintAttributes(vector<Attribute> attributes, MFTEntry entry)
{
    for (int i = 0; i < attributes.size(); i++)
    {
        if (attributes[i].type == 48)
        {
            if (attributes[i].FileName.filename[0] != '$' && attributes[i].FileName.filename != "")
            {
                cout << "Type: " << entry.type << " | Name: " << attributes[i].FileName.filename
                    << " | Parent Folder: " << attributes[i].FileName.parentFolderIndex << endl;
            }
        }
        if (attributes[i].type == 128)
        {
            if (attributes[i].FileName.filename[0] != '$' && attributes[i].FileName.filename != "" && entry.type == 1)
            {
                SetConsoleOutputCP(65001);
                cout << "Data: " << attributes[i].Data.content << endl;
                cout << "File size: " << attributes[i].contentSize << endl;
            }
        }
    }
}