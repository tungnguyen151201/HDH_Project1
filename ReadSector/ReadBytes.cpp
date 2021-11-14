#include "ReadBytes.h"

int HexToDecimal(string hex)
{
    int length = hex.size();
    int base = 1;

    int dec = 0;

    for (int i = length - 1; i >= 0; i--) {
        if (hex[i] >= '0' && hex[i] <= '9') {
            dec += (int(hex[i]) - 48) * base;
            base = base * 16;
        }
        else if (hex[i] >= 'A' && hex[i] <= 'F') {
            dec += (int(hex[i]) - 55) * base;
            base = base * 16;
        }
    }
    return dec;
}
string Uppercase(string s)
{
    string result = "";
    for (int i = 0; i < s.length(); i++)
    {
        result += toupper(s[i]);
    }
    return result;
}
int ReadBytes(string offset, int numByte, BYTE sector[512])
{
    int start = HexToDecimal(offset);
    string s;
    for (int i = start + numByte - 1; i >= start; i--)
    {
        stringstream ss;
        ss << setfill('0') << setw(2) << hex << (0xff & (unsigned int)sector[i]);
        s += ss.str();
    }
    cout << Uppercase(s) << endl;    
	return HexToDecimal(Uppercase(s));
}