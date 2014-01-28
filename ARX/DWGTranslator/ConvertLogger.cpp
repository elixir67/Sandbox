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
#include "stdafx.h"
#include "ConvertLogger.h"

ConvertLogger::ConvertLogger()
    :m_Enabled(true)
{
}

ConvertLogger::~ConvertLogger()
{
}

bool ConvertLogger::Open(const std::wstring& fileName)
{  
    m_logStream.open(fileName.c_str(), std::ios_base::out);

    if(!m_logStream)
    {
       return false;
    }
  
    return true;
}

void ConvertLogger::Close()
{
    if(m_logStream.is_open())
    {
        m_logStream.close();
    }
}

void ConvertLogger::Enable()
{  
    m_Enabled = true;
}  
  
void ConvertLogger::Disable()
{  
    m_Enabled = false;
}  
  
std::string ConvertLogger::GetTimeStr()
{  
    time_t nowTime;  
    time(&nowTime);  
  
    tm* localTime = localtime(&nowTime);
  
    //"2011-07-18 23:03:01 ";
    std::string strFormat = "%Y-%m-%d %H:%M:%S ";
  
    char strDateTime[30] = {'\0'};
    strftime(strDateTime, 30, strFormat.c_str(), localTime);
  
    std::string strRes = strDateTime;  
  
    return strRes;
}  