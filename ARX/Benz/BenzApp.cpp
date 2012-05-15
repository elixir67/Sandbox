#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "aced.h"
#include "dbsymtb.h"
#include "dbapserv.h"
#include "acgi.h"
#include "tchar.h"

#include "BenzEntity.h"
#include "ControlLine.h"
#include "ControlNotify.h"

void addToModelSpace(AcDbObjectId &objId, AcDbEntity* pEntity);

//void
//addBenz()
//{
//	AcDbObjectId bId;
//	ControlLine *pLine = new ControlLine(AcGePoint3d(-10, 10, 0),AcGePoint3d(10, 10, 0));
//	addToModelSpace(bId, pLine);
//	pLine->close();
//}

void
addBenz()
{
	AcDbObjectId aId, bId;

	BenzEntity *pBenz = new BenzEntity(AcGePoint3d(0,0,0),10.0);
	addToModelSpace(aId, pBenz);
	pBenz->close();

	ControlLine *pLine = new ControlLine(AcGePoint3d(-10, 10, 0),AcGePoint3d(10, 10, 0));
	addToModelSpace(bId, pLine);
	//pLine->close();

	// Create the ControlNotify for BenzEntity
	//
	ControlNotify *pObj = new ControlNotify();
	pObj->eLinkage(aId);

	// Open the named object dictionary, check if there is
	// an entry with the key "ASDK_DICT".  If not, create a
	// dictionary and add it.
	// 
	AcDbDictionary *pNamedObj;
	AcDbDictionary *pNameList;
	acdbHostApplicationServices()->workingDatabase()->getNamedObjectsDictionary(pNamedObj,
		AcDb::kForWrite);
	if (pNamedObj->getAt(_T("ASDK_DICT"),
		(AcDbObject*&)pNameList, AcDb::kForWrite)
		== Acad::eKeyNotFound)
	{
		pNameList = new AcDbDictionary;
		AcDbObjectId DictId;
		pNamedObj->setAt(_T("ASDK_DICT"), pNameList, DictId);
	}
	pNamedObj->close();

	AcDbObjectId objId;
	if ((pNameList->getAt(_T("object_to_notify_Benz"), objId))
		== Acad::eKeyNotFound)
	{
		pNameList->setAt(_T("object_to_notify_Benz"), pObj, objId);
		pObj->close();
	} else {
		delete pObj;
		ads_printf(_T("object_to_notify_Benz already exists\n"));
	}
	pNameList->close();

	// Set up persistent reactor link between ControlLine
	// and BenzEntity
	//
	pLine->addPersistentReactor(objId);
	pLine->close();

}

// Adds an entity to Model Space, but does not close
// the entity.
//
void
addToModelSpace(AcDbObjectId &objId, AcDbEntity* pEntity)
{
	AcDbBlockTable *pBlockTable;
	AcDbBlockTableRecord *pSpaceRecord;

	acdbHostApplicationServices()->workingDatabase()
		->getSymbolTable(pBlockTable, AcDb::kForRead);

	pBlockTable->getAt(ACDB_MODEL_SPACE, pSpaceRecord,
		AcDb::kForWrite);
	pBlockTable->close();

	pSpaceRecord->appendAcDbEntity(objId, pEntity);
	pSpaceRecord->close();

	return;
}


void
initAsdkBenz()
{
	BenzEntity::rxInit();
	ControlLine::rxInit();
	ControlNotify::rxInit();
    acrxBuildClassHierarchy();

	acedRegCmds->addCommand(_T("ASDK_BENZ"),
		_T("ASDKBENZ"),
		_T("BENZ"),
		ACRX_CMD_TRANSPARENT,
		addBenz);
	addBenz();
}

extern "C" AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* appId) 
{
    switch(msg) {
	case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(appId);
		acrxDynamicLinker->registerAppMDIAware(appId);
	    initAsdkBenz();
	    break;
	case AcRx::kUnloadAppMsg:
		acedRegCmds->removeGroup(_T("ASDK_BENZ"));
		//deleteAcRxClass(BenzEntity::desc());
		deleteAcRxClass(ControlLine::desc());
		//deleteAcRxClass(ControlNotify::desc());
    }
    return AcRx::kRetOK;
}
