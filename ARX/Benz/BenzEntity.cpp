#include "BenzEntity.h"
#include "acgi.h"
#include <math.h>
#include <dbproxy.h>

#define PI 3.14159265358979323846
#define HALFPI PI / 2.0
#define TWOPI PI * 2

ACRX_DXF_DEFINE_MEMBERS(BenzEntity,\
						AcDbEntity,AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, 
						AcDbProxyEntity::kNoOperation ,BENZENTITY,Benz);

BenzEntity::BenzEntity()
{
}

BenzEntity::BenzEntity(AcGePoint3d center, double radius)
{
	m_Center = center;
	m_p1 = AcGePoint3d(0,radius,0);
	m_p2 = AcGePoint3d(radius*cos(PI*7/6),radius*sin(PI*7/6),0);
	m_p3 = AcGePoint3d(radius*cos(PI*11/6),radius*sin(PI*11/6),0);
}

BenzEntity::~BenzEntity(void)
{
}

Adesk::Boolean 
BenzEntity::subWorldDraw(AcGiWorldDraw* pW)
{
	assertReadEnabled();

	pW->geometry().circle(m_p1,m_p2,m_p3);

	AcGePoint3d pts1[2] = {m_Center, m_p1};
	pW->geometry().worldLine(pts1);

	AcGePoint3d pts2[2] = {m_Center, m_p2};
	pW->geometry().worldLine(pts2);

	AcGePoint3d pts3[2] = {m_Center, m_p3};
	pW->geometry().worldLine(pts3);

	return Adesk::kTrue;
}

//- Grip points protocol
Acad::ErrorStatus BenzEntity::subGetGripPoints (
	AcGePoint3dArray &gripPoints, AcDbIntArray &osnapModes, AcDbIntArray &geomIds
	) const {
		assertReadEnabled () ;
		//----- This method is never called unless you return eNotImplemented 
		//----- from the new getGripPoints() method below (which is the default implementation)

		//clockwise from Upper Right...
		gripPoints.append(m_p1);
		gripPoints.append(m_p2);
		gripPoints.append(m_p3);
		gripPoints.append(m_Center);

		return Acad::eOk;
}

Acad::ErrorStatus BenzEntity::subMoveGripPointsAt (const AcDbIntArray &indices, const AcGeVector3d &offset) {
	assertWriteEnabled () ;
	//----- This method is never called unless you return eNotImplemented 
	//----- from the new moveGripPointsAt() method below (which is the default implementation)

	int gripUsed = indices[0]; // We're only interested in the first grip point...

	AcGePoint3d gripPt;

	switch (gripUsed)
	{
	case 0:
		gripPt = m_p1;
		break;
	case 1:
		gripPt = m_p2;
		break;
	case 2:
		gripPt = m_p3;
		break;

	// Move BenzEntity
	case 3:
		gripPt = m_Center;
		gripPt = gripPt + offset;
		m_Center += offset;
		m_p1 += offset;
		m_p2 += offset;
		m_p3 += offset;
		return Acad::eOk;
	}
	// Don't care which point we rotate, just assign it to one of the three points. The other two can get by rotate.
	gripPt = gripPt + offset;
	m_p1 = gripPt;
	AcGeVector3d vecToMovedGrip = gripPt - m_Center;
	AcGeVector3d vecToMP2 = vecToMovedGrip.rotateBy(PI*2/3,AcGeVector3d(0, 0, 1));
	AcGeVector3d vecToMP3 = vecToMovedGrip.rotateBy(PI*2/3,AcGeVector3d(0, 0, 1));
	m_p2 = m_Center + vecToMP2;
	m_p3 = m_Center + vecToMP3;

	return Acad::eOk;
}

void BenzEntity::doRotation(double angle)
{
	assertWriteEnabled(); 

	AcGeVector3d vecToMovedGrip = m_p1 - m_Center;
	AcGeVector3d vecToMP1 = vecToMovedGrip.rotateBy(angle,AcGeVector3d(0, 0, 1));
	m_p1 = m_Center + vecToMP1;
	AcGeVector3d vecToMP2 = vecToMP1.rotateBy(PI*2/3,AcGeVector3d(0, 0, 1));
	m_p2 = m_Center + vecToMP2;
	AcGeVector3d vecToMP3 = vecToMP2.rotateBy(PI*2/3,AcGeVector3d(0, 0, 1));
	m_p3 = m_Center + vecToMP3;

}

Acad::ErrorStatus BenzEntity::subTransformBy(const AcGeMatrix3d& xform)
{
	assertWriteEnabled(); 

	m_p1.transformBy(xform);
	m_p2.transformBy(xform);
	m_p3.transformBy(xform);
	m_Center.transformBy(xform);

	return Acad::eOk;
}

void BenzEntity::doRotation(AcGeMatrix3d matrix)
{
	assertWriteEnabled(); 

	subTransformBy(matrix);
}

void BenzEntity::doMove(AcGeVector3d offset)
{
	assertWriteEnabled(); 

	m_p1 += offset;
	m_p2 += offset;
	m_p3 += offset;
	m_Center += offset;
}

Acad::ErrorStatus BenzEntity::dwgInFields(AcDbDwgFiler* pFiler)
{
	assertWriteEnabled();
	AcDbEntity::dwgInFields(pFiler);
	pFiler->readPoint3d(&m_p1);
	pFiler->readPoint3d(&m_p2);
	pFiler->readPoint3d(&m_p3);
	pFiler->readPoint3d(&m_Center);
	return pFiler->filerStatus();
}

Acad::ErrorStatus BenzEntity::dwgOutFields(AcDbDwgFiler* pFiler)const
{
	assertReadEnabled();
	AcDbEntity::dwgOutFields(pFiler);
	pFiler->writePoint3d(m_p1);
	pFiler->writePoint3d(m_p2);
	pFiler->writePoint3d(m_p3);
	pFiler->writePoint3d(m_Center);
	return pFiler->filerStatus();
}