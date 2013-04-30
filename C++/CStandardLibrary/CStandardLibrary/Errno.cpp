#include "stdafx.h"
#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <math.h>

void TestErrno()
{
	assert(errno == 0);
	perror("No error reported as");
	errno = ERANGE;
	assert(errno == ERANGE);
	perror("Range error reported as");
	errno = 0;
	assert(errno == 0);
	sqrt(-1.0);
	assert(errno == EDOM);
	perror("Domain error reported as");
	puts("SUCCESS testing <errno.h>");
}