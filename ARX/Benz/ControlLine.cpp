#include "ControlLine.h"
#include "dbproxy.h"
#include "acgi.h"

ACRX_DXF_DEFINE_MEMBERS(ControlLine,\
						AcDbEntity,AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, 
						AcDbProxyEntity::kDisableProxyWarning,CONTROLLINE,cntLine);

ControlLine::ControlLine(void)
{
}

ControlLine::ControlLine(AcGePoint3d start, AcGePoint3d end)
{
	m_start = start;
	m_end = end;
	m_middle = AcGePoint3d((start.x+end.x)/2,(start.y+end.y)/2, 0);
}

ControlLine::~ControlLine(void)
{
}

Adesk::Boolean ControlLine::subWorldDraw(AcGiWorldDraw* pWd)
{
	assertReadEnabled();

	AcGePoint3d pts[2] = {m_start, m_end};
	pWd->geometry().worldLine(pts);

	return Adesk::kTrue;
}

Acad::ErrorStatus ControlLine::subGetGripPoints(AcGePoint3dArray &gripPoints, AcDbIntArray &osnapModes, AcDbIntArray &geomIds)const
{
	assertReadEnabled();

	gripPoints.append(m_start);
	gripPoints.append(m_end);
	gripPoints.append(m_middle);

	return Acad::eOk;
}

Acad::ErrorStatus ControlLine::subMoveGripPointsAt (const AcDbIntArray &indices, const AcGeVector3d &offset)
{
	assertWriteEnabled () ;

	int gripUsed = indices[0]; // We're only interested in the first grip point...

	switch (gripUsed)
	{
	// Choose m_start, Rotate around m_end
	case 0:
	{
		m_actionType = ControlLine::kRotate;
		AcGeVector3d oldVec = m_start - m_end;
		m_start += offset;
		m_middle = AcGePoint3d((m_start.x+ m_end.x)/2,(m_start.y+ m_end.y)/2,0);
		AcGeVector3d newVec = m_start - m_end;
		m_angleOffset = newVec.angleTo(oldVec,AcGeVector3d(1,0,0));
		m_angleMatrix = oldVec.rotateTo(newVec);
		break;
	}
	// Choose m_end, Rotate around m_start
	case 1:
	{
		m_actionType = ControlLine::kRotate;
		AcGeVector3d oldVec = m_end - m_start;
		m_end += offset;
		m_middle = AcGePoint3d((m_start.x+ m_end.x)/2,(m_start.y+ m_end.y)/2,0);		
		AcGeVector3d newVec = m_end - m_start;
		m_angleOffset = newVec.angleTo(oldVec,AcGeVector3d(0,0,1));
		m_angleMatrix = newVec.rotateTo(oldVec);
		break;
	}
	// Move Middle Pointq
	case 2:
		m_actionType = ControlLine::kMove;

		m_positionOffset = offset;
		m_middle += offset;
		m_start += offset;
		m_end += offset;

		break;	
	}

	return Acad::eOk;
}

double ControlLine::GetAngleOffset(void)
{
	return m_angleOffset;
}

AcGeMatrix3d ControlLine::GetAngleMatrix(void)
{
	return m_angleMatrix;
}

AcGeVector3d ControlLine::GetPositionOffset()
{
	return m_positionOffset;
}

ControlLine::ActionType ControlLine::GetActionType()
{
	return m_actionType;
}

Acad::ErrorStatus ControlLine::dwgInFields(AcDbDwgFiler* pFiler)
{
	assertWriteEnabled();
	AcDbEntity::dwgInFields(pFiler);
	pFiler->readPoint3d(&m_start);
	pFiler->readPoint3d(&m_end);
	pFiler->readPoint3d(&m_middle);
	return pFiler->filerStatus();
}

Acad::ErrorStatus ControlLine::dwgOutFields(AcDbDwgFiler* pFiler)const
{
	assertReadEnabled();
	AcDbEntity::dwgOutFields(pFiler);
	pFiler->writePoint3d(m_start);
	pFiler->writePoint3d(m_end);
	pFiler->writePoint3d(m_middle);
	return pFiler->filerStatus();
}