// LongFilename.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
//#include <windef.h>   // why it has fatal error C1189: #error : "No Target Architecture"
#include <windows.h> // for MultiByteToWideChar && WCHAR
#pragma warning(disable : 4996)

int  UnicodeAPI()
{
FILE *from, *to;
char filename[1024];
strcpy(filename,"\\\\?\\G:\\Temp\\VerylongpathVerylongpathVerylongpathVerylongpathVerylongpathV\\VerylongpathVerylongpathVerylongpathVerylongpathVerylongpathV\\VerylongpathVerylongpathVerylongpathVerylongpathVerylongpathV\VerylongpathVerylongpathVerylongpathVerylongpathVeryl\\navis\Navis.log");
int iL1=MultiByteToWideChar(CP_ACP, 0, filename, strlen(filename), NULL, 0); 
WCHAR* wfilename=new WCHAR[iL1+1]; 
wfilename[iL1] = '\0';
int iL2=MultiByteToWideChar(CP_ACP, 0, filename, strlen(filename), wfilename, iL1); 
from = _wfopen( wfilename ,L"rb");
to = fopen(".\\longpath.txt", "wb");
if((from ==NULL)||(to==NULL))
    return -1;
char buffer[1024];
int count = 0;
while ( (count = fread(buffer, sizeof(char), 1024, from)) != 0)
    fwrite( buffer, sizeof(char), count, to);
delete []wfilename;
fclose (from); fclose(to);
return 0;
}

bool ShortPath()
{
    TCHAR pathName [1024];
    wcscpy(pathName,L"\\\\?\\E:\\VerylongpathVerylongpathVerylongpathVerylongpathVerylongpathVerylongpathVerylongpathVerylongpathVerylongpathVerylongpathVerylongpath\\VerylongpathVerylongpathVerylongpathVerylongpathVerylongpathVerylongpathVerylongpathVerylongpathVerylongpathVerylongpathVerylongpath.txt");

    const int MaxPathLength = 2048;
    TCHAR shortPath[MaxPathLength];

    if (wcslen(pathName) >= MAX_PATH)
    {
        char prePath[] = "\\\\?\\";
        if (wcslen(pathName) >= MaxPathLength - wcslen(pathName))
            return false;

        swprintf(shortPath, MaxPathLength, L"%s%s", prePath, pathName);

        for (int iPathIndex = 0; iPathIndex < wcslen(shortPath); iPathIndex++)
            if (shortPath[iPathIndex] == '/')
                shortPath[iPathIndex] = '\\';

        int dwlen = GetShortPathName(shortPath, shortPath, MaxPathLength);
        if (dwlen <= 0)
            return false;
    }
    return true;
}

int _tmain(int argc, _TCHAR* argv[])
{
    UnicodeAPI();
	return 0;
}

