// Matrix.cpp : Defines the entry point for the console application.
//

//Given the following Matrix and Vector, what is the result:
//
//3 1 5      6   38
//2 1 4  x   5 = 29
//2 4 3      3   41 
//


#include "stdafx.h"
#include <iostream>
#include <math.h>
#include <assert.h>
using namespace std;

#include <gtest\gtest.h>

class Vector;
// n Order Matrics
class Matrix
{
public:
    Matrix(int* p, int order)
    {
        m_order = order;
        m_data = new int[order*order];
        for(int row = 0; row < m_order; ++row)
       {
           for(int column = 0; column < m_order; ++column)
           {
               m_data[row*m_order + column] = *(p++);
           }
        }
        cout << "Matrix is constructed!"<<endl;
    }

    ~Matrix()
    {
        delete[] m_data;
    }

    void Output()
    {
       cout << "Matrix content: " << endl;
       for(int row = 0; row < m_order; ++row)
       {
           for(int column = 0; column < m_order; ++column)
               cout << m_data[row*m_order + column] << " ";
           cout << endl;
       }
    }

    Vector * Multiply(const Vector & v);

private:
    int * m_data;
    int m_order;
};

// n order Vector
class Vector
{
public:
    Vector(int * p, int length)
    {
        m_order = length;
        m_data = new int[length];
        for(int i = 0; i < length; i++)
            m_data[i] = *(p++);
        cout << "Vector is constructed" << endl;
    } 

    ~Vector()
    {
        delete[] m_data;
    }

    void Output()
    {
        cout << "Vector content: " << endl;
        for(int i = 0; i < m_order; ++i)
            cout << m_data[i] << endl;
        cout << endl;
    }

    bool operator==(Vector & rhs)const
    {
        if(m_order != rhs.m_order)
            return false;
        for(int i = 0; i < m_order; i++)
            if(m_data[i] != rhs.m_data[i])
                return false;
        return true;
    }

    friend Vector * Matrix::Multiply(const Vector &v);

private:
    int * m_data;
    int m_order;
};

Vector * Matrix::Multiply(const Vector & v)
{
    assert(m_order == v.m_order);
    if(m_order != v.m_order)
        return NULL;

    int * r = new int[m_order];
    for(int i = 0; i < m_order; ++i)
        r[i] = 0;
    for(int row = 0; row < m_order; ++row)
        for(int colum = 0; colum < m_order; ++colum)
            r[row] += m_data[row * m_order + colum]*v.m_data[colum];

    cout << "The result after Matrix multiplied Vector:" << endl;
    for(int i = 0; i < m_order; ++i)
        cout << r[i] << endl;

    Vector * rv = new Vector(r, m_order);
    return rv;
}

TEST(MatrixTest, InputOutput)
{
    int ma[] = {3,1,5,
                2,1,4,
                2,4,3};
    Matrix m(ma, 3);
    int va[] = {6, 5, 3};
    Vector v(va, 3);
    m.Output();
    v.Output();
    unique_ptr<Vector> r(m.Multiply(v));
    r->Output();

    int eva[] = {38, 29, 41}; 
    Vector ev(eva, 3);
    ASSERT_TRUE(ev == *r);

    SUCCEED();
}

int _tmain(int argc, _TCHAR* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

