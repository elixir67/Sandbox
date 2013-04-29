#include "stdafx.h"
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <limits.h>

static void prclass(const char * name, int(*fn) (int))
{
	int c;

	fputs(name, stdout);
	fputs(": ", stdout);
	for(c = EOF; c <= UCHAR_MAX; ++c)
		if((*fn)(c))
			fputc(c, stdout);
	fputs("\n", stdout);
}

void testCType()
{
	prclass("ispunct", &ispunct);
	prclass("isdigit", &isdigit);
	prclass("islower", &islower);
	prclass("isalpha", &isalpha);
	prclass("isalnum", &isalnum);

	char *s;
	int c;

	for(s = "0123456789"; *s; ++s)
		assert(isdigit(*s) && isxdigit(*s));
}