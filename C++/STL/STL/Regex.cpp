#include "stdafx.h"
#include <regex>
#include <iostream>
using namespace std;

void RegexTest1()
{
    vector<wstring> ss;
    ss.push_back(L"2008-12-09");
    ss.push_back(L"2008-12-09+01:00"); 
    ss.push_back(L"2008-12-09+01"); 
    ss.push_back(L"2008-12-09+0100"); 
    ss.push_back(L"2008-12-09-01:00"); 
    ss.push_back(L"2008-12-09-01"); 
    ss.push_back(L"2008-12-09-0100"); 

    // Note for + character in C++ regex, it need use \\+ to represent it since in C++ using \ fro its own escape sequence
    const wchar_t* const reDateOnly = L"\\d{4}-\\d{2}-\\d{2}((\\+|-)\\d{2}(:\\d{2}|\\d{2})?)?";
    // const wchar_t* const reDateOnly = L"\\d{4}-\\d{2}-\\d{2}\\+\\d{2}:\\d{2}";
    wcout << boolalpha; 

    // wsmatch	match_results<std::wstring::const_iterator>
    wsmatch mr;
    wcout << ss[1] << " "<< regex_match(ss[1], mr, wregex(reDateOnly)) << endl;
    wcout << mr[1] << endl;
    wcout << mr[2] << endl;
    wcout << mr[3] << endl;

    // NOTE we need add tr1 namespace to pass compile
    for_each(ss.begin(), ss.end(), [&](wstring s){
        wcout << s << "\t"<< tr1::regex_match(s, tr1::wregex(reDateOnly)) << endl;
    });

    static const wchar_t* fmtFull = L"%4d-%2d-%2dT%2d:%2d:%2d+%2d";
    tm t = { 0,0,0,0,0,0,0,0,0 };
    int offsetHours = 0;
    int offsetMinutes = 0;
    swscanf_s(ss[1].c_str(), fmtFull, &t.tm_year, &t.tm_mon, &t.tm_mday, 
        //&t.tm_hour, &t.tm_min, &t.tm_sec, 
        &offsetHours, &offsetMinutes);
    t.tm_year -= 1900; /* years since 1900 */
    t.tm_mon -= 1;  /* months since January - [0,11] */
    time_t time = _mkgmtime(&t);
    
}

void RegexTest2()
{
    // one typical case of IFC schema version is like: FILE_SCHEMA (('IFC2X3'));
    // note it could have space between the brackets, so the expression has some space escape sequence
    // note in c++ the escapse character need double back slash
    std::regex expression("FILE_SCHEMA\\s*\\(\\s*\\(\\s*'IFC(.+)'\\s*\\)\\s*\\)\\s*;", regex_constants::icase);  

    std::vector<std::string> testArrays = std::vector<std::string>();
    testArrays.push_back("FILE_SCHEMA(('ifc2X_PLATFORM'));");
    testArrays.push_back("FILE_SCHEMA (('IFC2X2_FINAL'));");
    testArrays.push_back("FILE_SCHEMA (('IFC2X_FINAL'));");
    testArrays.push_back("FILE_SCHEMA(('IFC2X3'));");
    testArrays.push_back("FILE_SCHEMA(('IFCinvalid'));");
    testArrays.push_back("FILE_SCHEMA (('IFC2X_final'));");
    testArrays.push_back("FILE_SCHEMA ((  'IFC2X2_final' )); ");
    testArrays.push_back("FILE_SCHEMA ((  'IFC4' )); ");

    // Currently Translation Engine(NavisWorks)supported those versions
    std::vector<std::string> supportedVersions;
    supportedVersions.push_back("2X_PLATFORM");
    supportedVersions.push_back("2X_FINAL");
    supportedVersions.push_back("2X2_FINAL");
    supportedVersions.push_back("2X3");

    for(auto it = testArrays.begin(); it != testArrays.end(); ++it)
    {
        std::string line = *it;
        std::smatch match;
        //boost::trim(line);
        if(std::regex_match(line, match, expression))
        {      
            // std::string schemaVersion = boost::to_upper_copy(match[1].str());
            std::string schemaVersion = match[1].str();
            cout << schemaVersion << ":";
            if(supportedVersions.cend() != std::find(supportedVersions.cbegin(), supportedVersions.cend(), schemaVersion))
            {
                // Find in default supported versions
                cout << "pass" << endl;
            }
            else
            {
                // let's check whether it's the latest supported version
                cout << "fail" << endl;
            }
        }
    }
}

void RegexTest()
{
    RegexTest1();
    RegexTest2();
}

