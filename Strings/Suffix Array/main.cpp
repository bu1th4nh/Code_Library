/*==========================================================================================*\
**                        _           _ _   _     _  _         _                            **
**                       | |__  _   _/ | |_| |__ | || |  _ __ | |__                         **
**                       | '_ \| | | | | __| '_ \| || |_| '_ \| '_ \                        **
**                       | |_) | |_| | | |_| | | |__   _| | | | | | |                       **
**                       |_.__/ \__,_|_|\__|_| |_|  |_| |_| |_|_| |_|                       **
\*==========================================================================================*/
//=====================================
/* Implementation for Suffix Array

        * Source: CP3 - Steven X Felix Halim
        * Author: bu1th4nh (Remake), Steven X Felix Halim (Original)
        * Status: tested
        * Date: 2018/11/29
*/
//=====================================
//Libraries and namespaces
//#include <bits/stdc++.h>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
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
#include <tuple>
#include <vector>
#include <utility>

#if __cplusplus >= 201103L
#include <unordered_map>
#include <unordered_set>
#include <random>
#endif // __cplusplus

using namespace std;

// #define DEBUG
// #define OPTIONAL_FEATURE

//=====================================
//Macroes
#define sp ' '
#define el '\n'
#define task ""
#define maxinp ()
#define fi first
#define se second
#define pb push_back
#define whole(x) x.begin(),x.end()
#define whole_1(x) x.begin()+1,x.end()
#define r_whole(x) x.rbegin(),x.rend()
#define FOR(i, x, y) for(auto i=x; i<=y; ++i)
#define FORl(i, x, y) for(auto i=x; i<y; ++i)
#define FORb(i, x, y) for(auto i=x; i>=y; --i)
#define FORlb(i, x, y) for(auto i=x; i>y; --i)
#define MEMS(x, val) memset(x, val, sizeof(x))
#define FILEOP()                        \
{                                       \
    freopen(task".inp", "r", stdin);    \
    freopen(task".out", "w", stdout);   \
}
#define FILEOP_DEBUG()                  \
{                                       \
    freopen(task".inp", "r", stdin);    \
    freopen(task".out", "w", stdout);   \
    freopen(task".err", "w", stderr);   \
}

//Macroes - Optional
#ifdef OPTIONAL_FEATURE
    #define pc(x) putchar(x)
    #define gc() getchar()
#endif


//=====================================
//Main Class
class SuffixArray
{
    typedef pair<int, int> ii;
    typedef vector<int> vi;

    //Settings
    int MAX_CHARACTER;
    bool ENABLE_LCS;


    //Variables
    string t;
    int n, m;

    vi RA, tempRA;                                                  //Rank array and temporary RA
    vi SA, tempSA;                                                  //Suffix array and temporary SA
    vi CntSortArr;                                                  //For counting / radix sort

    vi phi;                                                         //To remember which suffix is behind i-th suffix, to compute LCP
    vi PLCP;                                                        //Permuted LCP array
    vi LCP;                                                         //Longest Common Prefix between suffix T+SA[i-1] and current suffix T+SA[i]



    //--------------------------------------------------------
    //Counting Sort for SA initialization
    void CountingSort(int k)
    {
        int sum = 0;
        CntSortArr = vi(MAX_CHARACTER+5, 0);
        FORl(i, 0, n)
        {
            CntSortArr[ (i + k < n) ? RA[i+k] : 0 ]++;              //Count the frequency of each integer rank
        }
        FORl(i, 0, MAX_CHARACTER)
        {
            int t = CntSortArr[i];
            CntSortArr[i] = sum;
            sum += t;
        }
        FORl(i, 0, n)                                               //Shuffle the SA if necessary
        {
            tempSA[CntSortArr[(SA[i]+k < n) ? RA[SA[i]+k] : 0]++] = SA[i];
        }
        SA = tempSA;
    }
    //Compute Suffix Array
    void initSA()
    {
        int r;
        FORl(i, 0, n) RA[i] = t[i];                                 //Initial Rankings array: RA[i] = t[i]
        FORl(i, 0, n) SA[i] = i;                                    //Initial SA: {0, 1, 2,..., n-1}
        for(int k = 1; k < n; k <<= 1)
        {
            CountingSort(k);                                        //Radix Sort: Sort based on the 2nd item
            CountingSort(0);                                        //then stable sort based on the 1st item
            tempRA[SA[0]] = r = 0;                                  //Re-ranking, start from 0;
            FORl(i, 1, n)
            {
                tempRA[SA[i]] = (RA[SA[i]] == RA[SA[i-1]] && RA[SA[i]+k] == RA[SA[i-1]+k]) ? r : ++r;
                //If same pair => same rank r. Otherwise increase r
            }
            RA = tempRA;
            if(RA[SA[n-1]] == n-1) break;
        }
    }
    //Compute LCP
    void initLCP()
    {
        int L = 0;
        phi[SA[0]] = -1;                                            //Default Value
        FORl(i, 1, n) phi[SA[i]] = SA[i-1];                          //Remember which suffix is behind this suffix

        FORl(i, 0, n)
        {
            if(phi[i] == -1)
            {
                PLCP[i] = 0;
                continue;
            }
            while(t[i+L] == t[phi[i]+L]) ++L;                       //L increased max n times
            PLCP[i] = L; L = max(L-1, 0);                           //L decreased max n times
        }

        FORl(i, 0, n) LCP[i] = PLCP[SA[i]];                         //Compute LCP in O(n)
    }
    //Check owner for LCS
    int owner(int idx)
    {
        return (idx < n-m-1) ? 1 : 2;
    }

public:
    //--------------------------------------------------------
    //String Matching
    ii stringMatching(string p)
    {
        /** \brief String matching in O(m log n)
         *
         * \param p: The Pattern string
         * \return A pair of lower and upper bound of contiguous index matches
         */



        m = p.size();
        int l = 0, r = n-1, mid = l;
        while(l < r)                                                //Find lower bound
        {
            mid = (l + r) / 2;
            int res = strncmp(t.c_str() + SA[mid], p.c_str(), m);   //Try to find P in suffix 'mid'

            if(res >= 0) r = mid;
            else     l = 1 + mid;
        }
        if(strncmp(t.c_str() + SA[l], p.c_str(), m)) return ii(-1, -1);      //If not found


        ii ret; ret.first = l;
        l = 0, r = n-1, mid = l;
        while(l < r)                                                //If the lower bound is found, find upper bound
        {
            mid = (l + r) / 2;
            int res = strncmp(t.c_str() + SA[mid], p.c_str(), m);

            if(res > 0) r = mid;
            else    l = 1 + mid;
        }
        if(strncmp(t.c_str() + SA[r], p.c_str(), m)) --r;           //Special case
        ret.second = r;

        return ret;
    }

    //LCS and LRS
    ii LRS()
    {
        /** \brief Compute the Longest Repeated Substring
         *
         * \return A pair of LRS length and its index
         */

        int idx = 0, maxLCP = -1;
        FORl(i, 1, n) if(LCP[i] > maxLCP)
        {
            maxLCP = LCP[i];
            idx = i;
        }
        return ii(maxLCP, idx);
    }
    ii LCS()
    {
        /** \brief Compute the Longest Common Contiguous Substring in O(n)
         *
         * \return A pair of LCS length and its index
         */

        if(!ENABLE_LCS) return ii(-1, -1);
        int idx = 0, maxLCP = -1;

        FORl(i, 1, n)
        {
            if(owner(SA[i]) != owner(SA[i-1]) && LCP[i] > maxLCP)
            {
                maxLCP = LCP[i];
                idx = i;
            }
        }
        return ii(maxLCP, idx);
    }

    //LCP and SA extraction
    vi extractLCP()
    {
        /** \brief Extract the LCP array */
        return LCP;
    }
    vi extractSA()
    {
        /** \brief Extract the suffix array */
        return SA;
    }


    //Constructor and destructor
    SuffixArray(string S)                                           //Assumed the string doesn't have terminating character
    {
        S += '$';
        t = S;
        n = S.size();

        ENABLE_LCS = false;
        MAX_CHARACTER = max(n, 256);

        RA = tempRA = vi(n, 0);
        SA = tempSA = vi(n, 0);
        phi = LCP = PLCP = vi(n, 0);

        initSA();
        initLCP();
    }
    SuffixArray(string S, string P, bool lcs = 1)                   //Assumed both strings don't have terminating character
    {
        t = S + '$' + P + '#';
        n = t.size();
        m = P.size();

        ENABLE_LCS = lcs;
        MAX_CHARACTER = max(n, 256);

        RA = tempRA = vi(n, 0);
        SA = tempSA = vi(n, 0);
        phi = LCP = PLCP = vi(n, 0);

        initSA();
        initLCP();
    }
    SuffixArray() {}

    ~SuffixArray() {}
};

//=====================================
//Driver Programs
//Driver Program #1: SPOJ_SARRAY
void SPOJ_SARRAY()
{
    string s;
    cin >> s;
    SuffixArray sa(s);
    vector<int> SA = sa.extractSA();

    FORl(i, 1, SA.size()) cout << SA[i] << el;
}


//Driver Program #2: SPOJ_LCS
void SPOJ_LCS()
{
    string s, t;
    cin >> s >> t;
    SuffixArray sa(s, t);

    cout << sa.LCS().first << el;
}


//Main Procedure
int main()
{
    return 0;
}

//=============================================================================//
/**    CTB, you are always in my heart and in my code <3       #30yearsCTB    **/
//=============================================================================//
