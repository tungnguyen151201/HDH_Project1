#include "ReadBytes.h"
string HexToBinary(string hex)
{
    stringstream bin;
    long int i = 0;

    while (hex[i]) {

        switch (hex[i]) {
        case '0':
            bin << "0000";
            break;
        case '1':
            bin << "0001";
            break;
        case '2':
            bin << "0010";
            break;
        case '3':
            bin << "0011";
            break;
        case '4':
            bin << "0100";
            break;
        case '5':
            bin << "0101";
            break;
        case '6':
            bin << "0110";
            break;
        case '7':
            bin << "0111";
            break;
        case '8':
            bin << "1000";
            break;
        case '9':
            bin << "1001";
            break;
        case 'A':
        case 'a':
            bin << "1010";
            break;
        case 'B':
        case 'b':
            bin << "1011";
            break;
        case 'C':
        case 'c':
            bin << "1100";
            break;
        case 'D':
        case 'd':
            bin << "1101";
            break;
        case 'E':
        case 'e':
            bin << "1110";
            break;
        case 'F':
        case 'f':
            bin << "1111";
            break;
        default:
            bin << "\nInvalid hexadecimal digit "
                << hex[i];
        }
        i++;
    }
    return bin.str();
}
int BinaryToDecimal(string binary)
{
    int n = 0;
    try
    {
        n = stoi(binary);
    }
    catch (exception e)
    {
        return 0;
    }
    int num = n;
    int dec_value = 0;
    int base = 1;

    int temp = num;
    while (temp) {
        int last_digit = temp % 10;
        temp = temp / 10;

        dec_value += last_digit * base;

        base = base * 2;
    }
    return dec_value;
}
string DecimalToBinary(int decimal)
{
    stringstream re_bin;
    while (decimal > 0) {
        int temp = decimal % 2;
        re_bin << temp;
        decimal = decimal / 2;       
    }
    stringstream bin;
    for (int i = re_bin.str().length() - 1; i >= 0; i--)
    {
        bin << re_bin.str()[i];
    }
    return bin.str();
}
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
int ReadBytes(string offset, int numByte, BYTE sector[512]) //Đọc ngược byte, trả về dec
{
    int start = HexToDecimal(offset);
    string s;
    for (int i = start + numByte - 1; i >= start; i--)
    {
        stringstream ss;
        ss << setfill('0') << setw(2) << hex << (0xff & (unsigned int)sector[i]);
        s += ss.str();
    }
    //cout << s << endl;
	return HexToDecimal(Uppercase(s));
}
int ReadSignedBytes(string offset, int numByte, BYTE sector[512]) //Đọc ngược byte, trả về dec nhưng là số có dấu
{
    int start = HexToDecimal(offset);
    string s;
    for (int i = start + numByte - 1; i >= start; i--)
    {
        stringstream ss;
        ss << setfill('0') << setw(2) << hex << (0xff & (unsigned int)sector[i]);
        s += ss.str();
    }
    string binary = DecimalToBinary(BinaryToDecimal(HexToBinary(s)) - 1);
    char sign = binary[0];
    for (int i = 0; i < binary.length(); i++)
    {
        binary[i] = (binary[i] == '1') ? '0' : '1';
    }
    int result = BinaryToDecimal(binary);
    return (sign == '1') ? result - 2 * result : result;
}
string ReadValueBytes(string offset, int numByte, BYTE sector[512]) //Đọc byte theo thứ tự, trả về string
{
    int start = HexToDecimal(offset);
    stringstream ss;
    for (int i = start; i < start + numByte; i++)
    {
        stringstream temp;
        temp << setfill('0') << setw(2) << hex << (0xff & (unsigned int)sector[i]);
        if (temp.str() != "00") ss << sector[i];
    }
    return ss.str();
}
string ReadHexBytes(string offset, int numByte, BYTE sector[512]) //Đọc ngược byte trả về hex
{
    int start = HexToDecimal(offset);
    string s;
    for (int i = start + numByte - 1; i >= start; i--)
    {
        stringstream ss;
        ss << setfill('0') << setw(2) << hex << (0xff & (unsigned int)sector[i]);
        s += ss.str();
    }
    return Uppercase(s);
}
string ReadHexDataBytes(string offset, int numByte, BYTE sector[512]) //Đọc xuôi byte trả về hex
{
    int start = HexToDecimal(offset);
    string s;
    for (int i = start; i < start + numByte; i++)
    {
        stringstream ss;
        ss << setfill('0') << setw(2) << hex << (0xff & (unsigned int)sector[i]);
        s += " " + ss.str();
    }
    return Uppercase(s);
}
int ReadAttributeBytes(int offset, int numByte, BYTE sector[1024]) //Đọc ngược byte, trả về dec, đầu vào offset là số
{
    int start = offset;
    string s;
    for (int i = start + numByte - 1; i >= start; i--)
    {
        stringstream ss;
        ss << setfill('0') << setw(2) << hex << (0xff & (unsigned int)sector[i]);
        s += ss.str();
    }
    //cout << s << endl;
    return HexToDecimal(Uppercase(s));
}
string ReadHexAttributeBytes(int offset, int numByte, BYTE sector[1024]) //Đọc ngược byte, trả về hex, đầu vào offset là số
{
    int start = offset;
    string s;
    for (int i = start + numByte - 1; i >= start; i--)
    {
        stringstream ss;
        ss << setfill('0') << setw(2) << hex << (0xff & (unsigned int)sector[i]);
        s += ss.str();
    }
    return Uppercase(s);
}
string ReadValueAttributeBytes(int offset, int numByte, BYTE sector[1024]) //Đọc byte theo thứ tự, trả về string
{
    int start = offset;
    stringstream ss;
    for (int i = start; i < start + numByte; i++)
    {
        stringstream temp;
        temp << setfill('0') << setw(2) << hex << (0xff & (unsigned int)sector[i]);
        if (temp.str() != "00") ss << sector[i];
    }
    return ss.str();
}
string ReadFileName(int offset, int numByte, BYTE sector[1024]) //Đọc filename
{
    int start = offset;
    stringstream ss;
    for (int i = start; i < start + numByte; i++)
    {
        stringstream temp;
        temp << setfill('0') << setw(2) << hex << (0xff & (unsigned int)sector[i]);
        if (temp.str() != "00") ss << sector[i];
        else numByte++;
    }
    return ss.str();
}
int GetSizeBitMap(string bitmap)
{
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
}