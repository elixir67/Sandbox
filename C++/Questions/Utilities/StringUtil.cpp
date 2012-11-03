#include "StdAfx.h"
#include "StringUtil.h"

void Reverse(char * pBegin, char * pEnd)
{
    if(!pBegin || !pEnd)
        return;

    while(pBegin < pEnd)
    {
        char temp = *pBegin;
        *pBegin = *pEnd;
        *pEnd = temp;

        ++pBegin;
        --pEnd;
    }
}
