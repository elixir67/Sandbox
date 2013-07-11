#include "stdafx.h"
#include <regex>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

bool isASCIIContent(const std::wstring & filename)
{
    int c;
    // Find out if the file has character which is not ASCII
    // Reference:
    // http://en.wikipedia.org/wiki/ASCII
    // http://stackoverflow.com/questions/277521/how-to-identify-the-file-content-as-ascii-or-binary
    std::ifstream fin(filename);
    bool rtn = true;
    if((c = fin.get()) != EOF && c <= 127)
        rtn = true;
    else
        rtn = false;

    fin.close();

    return rtn;
}

bool isASCIIContentByBOM(const std::wstring & filename)
{
    std::ifstream bin(filename, std::ios::in | std::ios::binary);
    int buffer[100];
    bool isASCII = false; 
    if (bin.is_open())
    {
        bin.read((char *)&buffer, 3);
        char c = buffer[0];
        if (c >= 0xEF)
        {
            if (buffer[0] == 0xEF && buffer[1] == 0xBB)
            {
                cout << "Encoding.UTF8" << endl;
            }
            else if (buffer[0] == 0xFE && buffer[1] == 0xFF)
            {
                cout << "Encoding.BigEndianUnicode" << endl;
            }
            else if (buffer[0] == 0xFF && buffer[1] == 0xFE)
            {
                cout << "Encoding.Unicode" << endl;

            }
            else
            {
                cout << "unicode ascii" << endl;
            }
            isASCII = false;   // Unicode
        }
        else
        {
            isASCII = true;
        }
    }
    bin.close();
    return isASCII;
}

void test(const std::wstring & filename)
{
    if(isASCIIContentByBOM(filename))
        wcout << filename << L":ASCII content" << endl;
    else
        wcout << filename << L":Unicode content" << endl;
}

void IOTest()
{
    std::wstring filename1 = L"g:\\p4root\\S_Volans\\Desktop\\Source\\alx\\UnitTestingCatch\\TestData\\AIM_DataTranslation\\IFC\\unicode.IFC";
    std::wstring filename2 = L"g:\\p4root\\S_Volans\\Desktop\\Source\\alx\\UnitTestingCatch\\TestData\\AIM_DataTranslation\\IFC\\z_beam_test_6.IFC";


    test(filename1);
    test(filename2);
}

