#pragma once
#include "dbmain.h"

class ControlNotify :
	public AcDbObject
{
public:
	ACRX_DECLARE_MEMBERS(ControlNotify);
	ControlNotify(void);
	~ControlNotify(void);
	void eLinkage(AcDbObjectId i){m_Id = i;}
	void modified (const AcDbObject* dbObj);
	virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* pFiler);
	virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler)const;
private:
	AcDbObjectId m_Id;
};

