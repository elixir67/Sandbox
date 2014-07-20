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
#include "DWGConvertor.h"
#include "ConvertUtil.h"
#include "ConvertLogger.h"
#include "ConvertProgress.h"
#include <string>


DWGConvertor::DWGConvertor()
{
}

DWGConvertor::~DWGConvertor()
{
}

int DWGConvertor::ConvertToSqlite(const std::wstring& dwgPath, const std::wstring& sqlitePath, ConvertLogger& ErrorLogger, const std::wstring& progressLogPath)
{
    int number = 0;
    try 
    {
        FdoPtr<IConnectionManager> manager = FdoFeatureAccessManager::GetConnectionManager ();

        FdoPtr<FdoBulkCopy> bulkCopy = FdoBulkCopy::Create();
        bulkCopy->SetLogFile(L"BulkCopy.log");
        bulkCopy->SetOptions(FdoBulkCopyOptions_IgnoreErrors | FdoBulkCopyOptions_IgnoreUnsupportedData | FdoBulkCopyOptions_IgnoreUnknownCoordSysMismatch); 

        const wchar_t* fdoProviderName = L"Autodesk.DesignService";
        FdoPtr<FdoIConnection> sourceConnection = manager->CreateConnection (L"Autodesk.DesignService");
        FdoPtr<FdoIConnection> targetConnection = manager->CreateConnection (L"OSGeo.SQLite");

        ConvertUtil::CreateSQLiteFile(targetConnection, sqlitePath.c_str());

        std::wstring targetConnectString = L"File=" + sqlitePath + L";ReadOnly=FALSE";
        targetConnection->SetConnectionString(targetConnectString.c_str());
        targetConnection->Open();

        std::wstring sourceConnectionString = L"File=" + dwgPath + L";ReadOnly=TRUE";
        sourceConnection->SetConnectionString(sourceConnectionString.c_str());
        sourceConnection->Open();
        
        ////setup the mapping between Source and Target
        FdoPtr<FdoBulkCopyMappingSchemaCollection> bulkCopyschemas = bulkCopy->GetMappingSchemas();
        FdoPtr<FdoBulkCopyMappingSchema> bulkCopyschema = FdoBulkCopyMappingSchema::Create();
        bulkCopyschema->SetSourceSchemaName(L"Acad");
        bulkCopyschemas->Add(bulkCopyschema);

        FdoPtr<FdoBulkCopyMappingClassCollection> bulkCopyclasses = bulkCopyschema->GetMappingClasses();

        FdoPtr<FdoIDescribeSchema> cmd = (FdoIDescribeSchema*) sourceConnection->CreateCommand(FdoCommandType_DescribeSchema);
        FdoFeatureSchemasP schemas = cmd->Execute();

        FdoFeatureSchemaP schema = schemas->FindItem(L"Acad");
        FdoClassesP classes = schema->GetClasses();

        for (FdoInt32 j = 0; j < classes->GetCount(); j++) 
        {
            FdoClassDefinitionP classDef = classes->GetItem(j);
            FdoString* className = classDef->GetName();

            FdoPtr<FdoBulkCopyMappingClass> cls = FdoBulkCopyMappingClass::Create();
            cls->SetSourceClassName(className);
            bulkCopyclasses->Add(cls);
        }

        long totalCount = QueryGeometryCount(sourceConnection, schema);

        bulkCopy->SetSourceConnection(sourceConnection);
        bulkCopy->SetTargetConnection(targetConnection);
        bulkCopy->WriteXml(L"BulkCopy.xml");

        FdoBulkCopyProgress *progress = new ConvertProgess(totalCount, progressLogPath);

        number = bulkCopy->Execute(progress);

        sourceConnection->Close();
        targetConnection->Close();
    }
    catch(FdoException *ex)
    {
        char errStr[1024];

        size_t len = wcslen(ex->GetExceptionMessage()) + 1;
        size_t converted = 0;
        char *exStr;
        exStr=(char*)malloc(len*sizeof(char));
        wcstombs_s(&converted, exStr, len, ex->GetExceptionMessage(), _TRUNCATE);

        sprintf(errStr, "FdoException interrupt the Bulkcopy processing, Exception: %s", exStr);
        ErrorLogger.log(errStr);
    }
    catch(...)
    {
        ErrorLogger.log("Unknown exception interrupt the Bulkcopy processing");
    }

    return number;
}

long DWGConvertor::QueryGeometryCount(FdoIConnection* connection, FdoFeatureSchemaP schema)
{
    long Count = 0;

    FdoPtr<FdoIDescribeSchema> cmd = (FdoIDescribeSchema*) connection->CreateCommand(FdoCommandType_DescribeSchema);
    FdoFeatureSchemasP schemas = cmd->Execute();

    FdoClassesP classes = schema->GetClasses();

    for (FdoInt32 j = 0; j < classes->GetCount(); j++) 
    {
        FdoClassDefinitionP classDef = classes->GetItem(j);
        FdoString* className = classDef->GetName();

        FdoPtr<FdoISelect> selCmd = (FdoISelect*)(connection->CreateCommand(FdoCommandType_Select));
        selCmd->SetFeatureClassName( className );
        FdoPtr<FdoIFeatureReader> reader = selCmd->Execute();
        while (reader->ReadNext()) 
            Count++;
    }
    return Count;
}

