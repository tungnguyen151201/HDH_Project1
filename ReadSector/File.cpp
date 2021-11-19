#include "File.h"
string GetFileNameExtendsion(string filename)
{
    int index = filename.find_last_of('.');
    return filename.substr(index + 1);
}
void ReadFile(File& file, MFTEntry entry)
{
    file.id = entry.id;
    file.sectors = entry.sectors;
    for (int i = 0; i < entry.attributes.size(); i++)
    {
        if (entry.attributes[i].type == 48)
        {
            file.name = entry.attributes[i].FileName.filename;
            file.parentIndex = entry.attributes[i].FileName.parentFolderIndex;
        }
        if (entry.attributes[i].type == 128)
        {
            file.data += entry.attributes[i].Data.content;
            file.size = entry.attributes[i].contentSize;
        }
    }
}
string ToString(vector<__int64> sectors)
{
    string s = "";
    for (int i = 0; i < sectors.size(); i++)
    {
        s += to_string(sectors[i]);
        if (i != sectors.size() - 1) s += ", ";
    }
    return s;
}
void PrintFile(File file)
{
    cout << "Id: " << file.id << " | Ten tap tin: " << file.name << " | Kich thuoc: " << file.size << endl;
    cout << "Cac sector luu tru: " << ToString(file.sectors) << endl;
}
void ReadFolder(Folder& folder, MFTEntry entry)
{
    folder.id = entry.id;
    folder.sectors = entry.sectors;
    for (int i = 0; i < entry.attributes.size(); i++)
    {
        if (entry.attributes[i].type == 48)
        {
            folder.name = entry.attributes[i].FileName.filename;
            folder.parentIndex = entry.attributes[i].FileName.parentFolderIndex;
        }
    }
}
void ReadChildFolder(Folder& folder, vector<File> files) //đọc các tệp nằm trong thư mục
{   
    for (int i = 0; i < files.size(); i++)
    {
        if (files[i].parentIndex == folder.id)
        {
            folder.child.push_back(files[i]);
        }
    }
}
void ReadFolderChild(Folder& folder, vector<Folder> folders) //đọc các thư mục trong thư mục
{
    for (int i = 0; i < folders.size(); i++)
    {
        if (folders[i].parentIndex == folder.id && folders[i].name != ".")
        {
            folder.folderchild.push_back(folders[i]);
        }
    }
}
void PrintFolder(Folder folder)
{
    cout << "Id: " << folder.id << " | Ten thu muc: " << folder.name << " | Cac sector luu tru: " << ToString(folder.sectors) << endl;
    for (int i = 0; i < folder.folderchild.size(); i++)
    {
        PrintFolder(folder.folderchild[i]);
        cout << "-------------------------------------------------" << endl;
    }
    for (int i = 0; i < folder.child.size(); i++)
    {
        PrintFile(folder.child[i]);
        cout << "-------------------------------------------------" << endl;
    }   
}
void PrintRootFolder(vector<MFTEntry> entries, vector<File>& files, vector<Folder>& folders)
{
    for (int i = 0; i < entries.size(); i++)
    {  
        File file;
        Folder folder;
        if (entries[i].type == 1)
        {
            ReadFile(file, entries[i]);
            if (file.name[0] == '$' || file.name == "") continue;
            files.push_back(file);
        }
        if (entries[i].type == 3)
        {
            ReadFolder(folder, entries[i]);
            if (folder.name[0] == '$') continue;
            folders.push_back(folder);
        }
    }
    for (int i = 0; i < folders.size(); i++)
    {
        ReadChildFolder(folders[i], files);
        ReadFolderChild(folders[i], folders);       
    }
    PrintFolder(folders[0]);
    cout << "=================================================" << endl;
}
void AccessFolder(int id, vector<Folder> folders)
{
    for (int i = 0; i < folders.size(); i++)
    {
        if (folders[i].id == id)
        {
            PrintFolder(folders[i]);
            return;
        }
    }
    cout << "Khong tim thay thu muc" << endl;
}
void AccessFile(int id, vector<File> files)
{
    for (int i = 0; i < files.size(); i++)
    {
        if (files[i].id == id)
        {
            PrintFile(files[i]);
            cout << "Noi dung tap tin: ";
            if (GetFileNameExtendsion(files[i].name) == "txt") cout << files[i].data << endl;
            else cout << "Day khong phai file text.\n";
            cout << "-------------------------------------------------" << endl;
            return;
        }
    }
    cout << "Khong tim thay tap tin" << endl;
}