#include "StdAfx.h"
#include "StringUtil.h"
#include <utility>
using namespace std;

void Reverse(char * pBegin, char * pEnd)
{
    if(!pBegin || !pEnd)
        return;

    while(pBegin < pEnd)
    {
        //char temp = *pBegin;
        //*pBegin = *pEnd;
        //*pEnd = temp;
        swap(*pBegin, *pEnd);

        ++pBegin;
        --pEnd;
    }
}
