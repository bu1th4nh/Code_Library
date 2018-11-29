/*==============================================================================================================*\
**                                  _           _ _   _     _  _         _                                      **
**                                 | |__  _   _/ | |_| |__ | || |  _ __ | |__                                   **
**                                 | '_ \| | | | | __| '_ \| || |_| '_ \| '_ \                                  **
**                                 | |_) | |_| | | |_| | | |__   _| | | | | | |                                 **
**                                 |_.__/ \__,_|_|\__|_| |_|  |_| |_| |_|_| |_|                                 **
\*==============================================================================================================*/
//=====================================
//Briefing
/*
    This is an implementation for Matrix
*/
//=====================================
//Libraries and namespaces
//#include <bits/stdc++.h>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <utility>
using namespace std;


//=====================================
//Macros
#define task ""
#define fi first
#define se second
#define maxinp (int)()
#define MODUL (int)(1e9+57)
#define siz(x) (int)(x.size())
#define len(x) (int)(x.length())
#define whole(x) x.begin(), x.end()
#define FOR(i, x, y) for(int i=x; i<=y; ++i)
#define FORl(i, x, y) for(int i=x; i<y; ++i)
#define FORb(i, x, y) for(int i=x; i>=y; --i)
#define FORlb(i, x, y) for(int i=x; i>y; --i)
#define MEMS(x, val) memset(x, val, sizeof(x))
#define FILEOP(x) freopen(x".inp", "r", stdin); freopen(x".out", "w", stdout);

//=====================================
//Typedef
typedef unsigned long long ull;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef long long ll;


//=====================================
//Overview - Matrix implementation with modulo
/*  
    * Author : Nguyen Tien Trung Kien, forked and modified by bu1th4nh.
    * Status : tested on many problems.
*/
//=====================================
//Matrix Class with modulo
template<class T> class Matrix
{
public:

    typedef vector<T> vt;
    typedef vector<vt> vvt;

    vvt a;
    int m, n;
    long long mod;


    //Initialization
    void initialize(int __m, int __n)
    {
        m = __m;
        n = __n;

        a = vvt(m+1, vt(n+1, T()));
    }
    void identity_matrix(int __n)
    {
        m = n = __n;
        a = vvt(n+1, vt(n+1, T()));

        FOR(i, 1, n) a[i][i] = (T)1;
    }

    //Constructors
    Matrix(long long __mod, int __m, int __n, const vvt &__a)
    {
        mod = __mod;
        a = __a;
        n = __n;
        m = __m;
    }
    Matrix(long long __mod, int __m, int __n)
    {
        mod = __mod;
        initialize(__m, __n);
    }
    Matrix(long long __mod, int __n)
    {
        mod = __mod;
        identity_matrix(__n);
    }
    Matrix() {}


    //Operators
    void operator= (const Matrix<T> &x)
    {
        mod = x.mod;
        a = x.a;
        m = x.m;
        n = x.n;
    }
    vt& operator[] (int i)
    {
        return a[i];
    }
    Matrix<T> operator * (const Matrix<T> &other)
    {
        Matrix<T> ret(mod, this->m, other.n);
        FOR(i, 1, this->m)
        {
            FOR(j, 1, other.n)
            {
                FOR(k, 1, this->n)
                {
                    ret.a[i][j] = (ret.a[i][j] + a[i][k] * other.a[k][j]) % mod;
                }
            }
        }
        return ret;
    }
    Matrix<T> operator ^ (long long k)
    {
        Matrix<T> ret(mod, this->n);
        Matrix<T> a = *this;

        if(k == 0) return Matrix(mod, this->n);
        FOR(i, 0, 63)
        {
            if((k >> i) & 1 == 1) ret = ret * a;
            a = a * a;
        }

        return ret;
    }
};


//=====================================
//Matrix Class without modulo
template<class T> class Matrix_without_mod
{
public:

    typedef vector<T> vt;
    typedef vector<vt> vvt;

    vvt a;
    int m, n;


    //Initialization
    void initialize(int __m, int __n)
    {
        m = __m;
        n = __n;

        a = vvt(m+1, vt(n+1, T()));
    }
    void identity_matrix(int __n)
    {
        m = n = __n;
        a = vvt(n+1, vt(n+1, T()));

        FOR(i, 1, n) a[i][i] = (T)1;
    }

    //Constructors
    Matrix_without_mod(int __m, int __n, const vvt &__a)
    {
        a = __a;
        n = __n;
        m = __m;
    }
    Matrix_without_mod(int __m, int __n)
    {
        initialize(__m, __n);
    }
    Matrix_without_mod(int __n)
    {
        identity_matrix(__n);
    }
    Matrix_without_mod() {}


    //Operators
    void operator= (const Matrix_without_mod<T> &x)
    {
        a = x.a;
        m = x.m;
        n = x.n;
    }
    vt& operator[] (int i)
    {
        return a[i];
    }
    Matrix_without_mod<T> operator * (const Matrix_without_mod<T> &other)
    {
        Matrix_without_mod<T> ret(this->m, other.n);
        FOR(i, 1, this->m)
        {
            FOR(j, 1, other.n)
            {
                FOR(k, 1, this->n)
                {
                    ret.a[i][j] = (ret.a[i][j] + a[i][k] * other.a[k][j]);
                }
            }
        }
        return ret;
    }
    Matrix_without_mod<T> operator ^ (long long k)
    {
        Matrix_without_mod<T> ret(this->n);
        Matrix_without_mod<T> a = *this;

        if(k == 0) return Matrix_without_mod(this->n);
        FOR(i, 0, 63)
        {
            if((k >> i) & 1 == 1) ret = ret * a;
            a = a * a;
        }

        return ret;
    }
};






//=====================================
//Functions and procedures
//Main Procedure
int main()
{
    ll n;

    cin >> n;
    FOR(i, 1, n)
    {
        ll kk = i - 1;
        Matrix_without_mod<ll> A(2, 2);
        A[1][1] = 1;
        A[1][2] = 1;
        A[2][1] = 1;
        A[2][2] = 0;
        A = A^kk;
        cout << (A[1][1])*1LL << endl;
    }

    return 0;
}
