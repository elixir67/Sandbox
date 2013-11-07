#include "stdafx.h"

#ifdef _WIN32
#include <Windows.h>
#pragma comment(lib, "version.lib")
#endif

std::vector<int> GetVersion( const wchar_t* path )
{
    std::vector<int> versions(4, 0);

#ifdef _WIN32
    DWORD  verHandle = NULL;
    DWORD  verSize   = GetFileVersionInfoSize( path, &verHandle);

    if (verSize != NULL)
    {
        LPSTR verData = new char[verSize];

        if (GetFileVersionInfo( path, verHandle, verSize, verData))
        {
            UINT   size      = 0;
            LPBYTE lpBuffer  = NULL;

            if (VerQueryValue(verData, L"\\", (LPVOID *)&lpBuffer, &size))
            {
                if (size)
                {
                    VS_FIXEDFILEINFO *verInfo = (VS_FIXEDFILEINFO *)lpBuffer;
                    if (verInfo->dwSignature == 0xfeef04bd)
                    {
                        versions[0] = HIWORD(verInfo->dwFileVersionMS);
                        versions[1] = LOWORD(verInfo->dwFileVersionMS);
                        versions[2] = HIWORD(verInfo->dwFileVersionLS);
                        versions[3] = LOWORD(verInfo->dwFileVersionLS);
                    }
                }
            }
        }

        delete[] verData;
    }
#endif // _WIN32

    return versions;
}

std::wstring ToUnicode(const char* byteArray)
{
    std::wstring result;
#ifdef _WIN32
    UINT cp = GetConsoleOutputCP();
    int buffersize = MultiByteToWideChar(cp, 0, byteArray, -1, NULL, NULL);
    if (buffersize > 0)
    {
        wchar_t* buffer = new wchar_t[buffersize];
        MultiByteToWideChar(cp, 0, byteArray, -1, buffer, buffersize);
        result = buffer;
        delete[] buffer;
    }
#endif
    return result;        
}

bool Is64BitBinary(const wchar_t* path)
{
    // Check whether it is x64 version of Navisworks
    DWORD fileType;
    if (!GetBinaryType(path, &fileType) || fileType != SCS_64BIT_BINARY)
    {
        // 64-bit 
        return false;
    }
    return true;
}

void TestVersion()
{
    const wchar_t * notepad = L"c:\Windows\System32\notepad.exe";
    std::cout << Is64BitBinary(notepad) << std::endl;
}
