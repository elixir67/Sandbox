//
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
#include "ConvertUtil.h"
#include <fstream>


bool ConvertUtil::File_Exists(const std::wstring& filename)
{
    std::ifstream file(filename.c_str());
    if(!file)
        return false;
    else
        return true;
}

void ConvertUtil::CreateSQLiteFile(FdoIConnection *connection, FdoString *file)
{
    _wunlink(file);

    int    count = 0;
    wchar_t buffer[512];
    FdoString **names = NULL;
    
    swprintf(buffer, 512, L"File=%ls;UseFdoMetadata=TRUE", file);
    connection->SetConnectionString(buffer);

    FdoPtr<FdoICreateDataStore>    dataStore = static_cast<FdoICreateDataStore*>(connection->CreateCommand(FdoCommandType_CreateDataStore));
    FdoPtr<FdoIDataStorePropertyDictionary> dictionary = dataStore->GetDataStoreProperties();

    names = dictionary->GetPropertyNames(count);
    dictionary->SetProperty(names[0], file);

    dataStore->Execute();
}
