// Copyright (C) 2013 by Autodesk, Inc. All Rights Reserved.
//
// The information contained herein is confidential, proprietary
// to Autodesk, Inc.,  and considered a trade  secret as defined
// in section 499C of the penal code of the State of California.
// Use  of  this  information  by  anyone other  than authorized
// employees of Autodesk, Inc.  is granted  only under a written
// non-disclosure  agreement,  expressly  prescribing  the scope
// and manner of such use.
//
// AUTODESK  MAKES  NO  WARRANTIES,  EXPRESS  OR  IMPLIED, AS  TO THE
// CORRECTNESS OF THIS CODE OR ANY DERIVATIVE WORKS WHICH INCORPORATE
// IT. AUTODESK PROVIDES THE CODE ON AN  "AS-IS" BASIS AND EXPLICITLY
// DISCLAIMS ANY  LIABILITY, INCLUDING  CONSEQUENTIAL AND  INCIDENTAL
// DAMAGES  FOR ERRORS,  OMISSIONS,  AND OTHER  PROBLEMS IN THE CODE.
//
// Use, duplication, or disclosure by the U.S. Government is subject
// to restrictions set forth in  FAR 52.227-19  (Commercial Computer
// Software  Restricted  Rights)  and  DFAR   252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software),  as applicable.
//

#pragma once
  
#include <sstream>
#include <fstream>
#include <iostream>
#include <ctime>

class ConvertLogger
{
public:
    ConvertLogger();
    ~ConvertLogger();

    bool Open(const std::wstring& strFileName);
    void Close();

    void Enable();
    void Disable();
  
    std::string GetTimeStr();
  
    template <typename T> void print(const T& value)  
    {  
        if (m_Enabled)
        {  
            std::cout << GetTimeStr() << ": " << value << std::endl;
        }  
    }  

    template <typename T> void log(const T& value)  
    {  
        if (m_Enabled)
        {
            m_logStream << GetTimeStr() << ": " << value << std::endl;
        }
    }
  
    template <typename T> ConvertLogger& operator<<(const T& value)  
    {  
        if (m_Enabled)
        {
            m_logStream << value;
            std::cout << value;
        }
        return (*this);
    }  
  
    ConvertLogger& operator<<(std::ostream& (*_Pfn)(std::ostream&))  
    {  
        if (m_Enabled)
        {
            (*_Pfn)(m_logStream);
        }
        return (*this);
    }  

private:
    std::ofstream m_logStream;
    bool m_Enabled;
};