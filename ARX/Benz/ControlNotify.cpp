#include "ControlNotify.h"
#include "ControlLine.h"
#include "BenzEntity.h"
#include <tchar.h>


ACRX_DXF_DEFINE_MEMBERS(ControlNotify,AcDbObject,
						AcDb::kDHL_CURRENT,AcDb::kMReleaseCurrent,
						0,CONTROLNOTIFY, persreact);

ControlNotify::ControlNotify(void)
{
}

ControlNotify::~ControlNotify(void)
{
}


Acad::ErrorStatus
ControlNotify::dwgInFields(AcDbDwgFiler* pFiler)
{
	assertWriteEnabled();
	AcDbObject::dwgInFields(pFiler);
	pFiler->readItem((AcDbSoftPointerId*) &m_Id);
	return pFiler->filerStatus();
}

Acad::ErrorStatus
ControlNotify::dwgOutFields(AcDbDwgFiler* pFiler) const
{
	assertReadEnabled();
	AcDbObject::dwgOutFields(pFiler);
	pFiler->writeItem((AcDbSoftPointerId&)m_Id);
	return pFiler->filerStatus();
}

void ControlNotify::modified (const AcDbObject* dbObj)
{
	ControlLine *pLine = ControlLine::cast(dbObj);

	BenzEntity *pBenz;
	if (acdbOpenObject(pBenz, m_Id,
		AcDb::kForWrite) == Acad::eOk)
	{
		if(ControlLine::kRotate == pLine->GetActionType())
		{
			double angle = pLine->GetAngleOffset();
			pBenz->doRotation(angle);

			// Try use matrix to do it again.
			////pBenz->doRotation(pLine->GetAngleMatrix());
		}
		else if(ControlLine::kMove == pLine->GetActionType())
		{
			pBenz->doMove(pLine->GetPositionOffset());
		}
		pBenz->close();
	}
	//pLine->close();
}
