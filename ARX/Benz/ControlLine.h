#pragma once
#include "dbmain.h"
#include "gemat3d.h"


class ControlLine :	public AcDbEntity
{
public:
	ACRX_DECLARE_MEMBERS(ControlLine);
	ControlLine(void);
	ControlLine(AcGePoint3d start, AcGePoint3d end);
	~ControlLine(void);

	enum ActionType{kMove=0,kRotate};

	virtual Adesk::Boolean      subWorldDraw(AcGiWorldDraw* pWd);
	virtual Acad::ErrorStatus subGetGripPoints(AcGePoint3dArray &gripPoints, AcDbIntArray &osnapModes, AcDbIntArray &geomIds)const;
	virtual Acad::ErrorStatus subMoveGripPointsAt (const AcDbIntArray &indices, const AcGeVector3d &offset);

	virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* pFiler);
	virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler)const;

private:
	AcGePoint3d m_start;
	AcGePoint3d m_end;
	AcGePoint3d m_middle;

	double m_angleOffset;
	AcGeMatrix3d m_angleMatrix;
	AcGeVector3d m_positionOffset;
	ActionType m_actionType;
public:
	double GetAngleOffset(void);
	AcGeMatrix3d GetAngleMatrix(void);

	AcGeVector3d GetPositionOffset();
	ActionType GetActionType();
};
