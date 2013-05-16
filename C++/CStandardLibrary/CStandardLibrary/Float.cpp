#include "stdafx.h"
#include <assert.h>
#include <float.h>
#include <math.h>
#include <stdio.h>

void TestFloat()
{
	//double radlog;
	//int digs;
	static int radix = FLT_RADIX;

	printf("FLT_RADIX = %i \n\n", FLT_RADIX);
	printf("DBL_DIG = %5i DBL_MANT_DIG = %6i\n", DBL_DIG, DBL_MANT_DIG);
	printf("DBL_EPSILON = %le \n", DBL_EPSILON);
}