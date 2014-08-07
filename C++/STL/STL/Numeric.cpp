#include "stdafx.h"

double roundNumeric(double dValue, int iRoundTo = 4)
{
    return double(int(dValue*iRoundTo + (dValue >= 0? 0.5:-0.5)))/iRoundTo;
}

void NumericTest()
{
    float value = 37.777779;
    float rounded = roundNumeric(value, 4);

    printf("%.2f\n", rounded);

    rounded = roundNumeric(1.99, 4);
    printf("%.2f\n", rounded);

    char number[24]; // dummy size, you should take care of the size!
    sprintf(number, "%.2f", 37.777779);
}