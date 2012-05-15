#pragma once
#include "dbmain.h"
#include "dbents.h"
#include "acgi.h"
#include "gemat3d.h"

class BenzEntity :
	public AcDbEntity
{
public:
	ACRX_DECLARE_MEMBERS(BenzEntity);
	BenzEntity(void);
	BenzEntity(AcGePoint3d center, double radius);
	~BenzEntity(void);
	virtual Adesk::Boolean subWorldDraw(AcGiWorldDraw* pW);
	virtual Acad::ErrorStatus subGetGripPoints(AcGePoint3dArray &gripPoints, AcDbIntArray &osnapModes, AcDbIntArray &geomIds)const;
	virtual Acad::ErrorStatus subMoveGripPointsAt (const AcDbIntArray &indices, const AcGeVector3d &offset);
	virtual Acad::ErrorStatus   subTransformBy(const AcGeMatrix3d& xform);

	virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* pFiler);
	virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler)const;

	void doRotation(double angle);
	void doRotation(AcGeMatrix3d matrix);
	void doMove(AcGeVector3d offset);

private:
	AcGePoint3d m_Center;
	AcGePoint3d m_p1;
	AcGePoint3d m_p2;
	AcGePoint3d m_p3;
};

