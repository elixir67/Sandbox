// Power.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cmath>
#include <limits>

#define NAN
#define FUZZZERO 0.0000001;

bool equal(double num1, double num2);
double PowerWithUnsignedExponent(double base, unsigned int exponent);

double Power(double base, int exponent)
{
    if(equal(base, 0.0) && exponent < 0)
    {
        return std::numeric_limits<double>::quiet_NaN();
    }
    
    unsigned int absExponent = (unsigned int)(exponent);
    if(exponent < 0)
        absExponent = (unsigned int)(-exponent);

    double result = PowerWithUnsignedExponent(base, absExponent);
    if(exponent < 0)
        result = 1.0/result;

    return result;
}

double PowerWithUnsignedExponent(double base, unsigned int exponent)
{
    if(exponent == 0)
        return 1;
    if(exponent == 1)
        return base;

    double result = PowerWithUnsignedExponent(base, exponent >> 1);
    result *= result;
    if((exponent & 0x1) == 1)
        result *= base;

    return result;
}

bool equal(double num1, double num2)
{
    return std::abs(num1- num2) < FUZZZERO;
}

void Test(char * testName, double base, int exponent, double expected)
{
    if(testName)
        printf("%s begins:\t", testName);

    double result = Power(base, exponent);
    if(equal(result, expected))
        printf("passed!\n");
    else
        printf("failed!\n");
}

int _tmain(int argc, _TCHAR* argv[])
{
    Test("Test1", 2, 3, 8);
    Test("Test2", -2, 3, -8);
    Test("Test3", 2, -3, 0.125);
    Test("Test4", 2, 0, 1);
    Test("Test5", 0, 0, 1);
    Test("Test6", 0, 4, 0);
    // Test("Test7", 0, -4, 0); // std::numeric_limits<double>::quiet_NaN()
	return 0;
}

