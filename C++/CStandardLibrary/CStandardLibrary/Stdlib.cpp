#include "stdafx.h"
#include <stdlib.h>

void TestDiv()
{
	int a = 3/-2;
	div_t v = div(3, -2);

	printf("%d %d", v.quot, v.rem);
}