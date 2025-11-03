#include "vacation.h"
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int plan_vacation(int N, std::vector<int> L, std::vector<int> R, long long K)
{
    if(K == 0)
    {
        int s = L[0], e = R[0];
        for(int i = 1; i < N; i++)
        {
            if(L[i] > e)
                return 0;
            if(R[i] < s)
                return 0;
            s = max(s, L[i]);
            e = min(e, R[i]);
        }
        return e - s + 1;
    }
    else if(K == 1)
    {
        int dont;
        int s = L[0], e = R[0];
        for(int i = 1; i < N; i++)
        {
            if(L[i] > e)
                return 0;
            if(R[i] < s)
                return 0;
            s = max(s, L[i]);
            e = min(e, R[i]);
        }
        int dontl = 0;
        int dontr = 0;
        for(int i = 0; i < N; i++)
        {
            if(L[i] > s-1)
            {
                dontl++;
                if(R[i] == e)
                    dontl++;
            }
            if(R[i] < e+1)
            {
                dontr++;
                if(L[i] == s)
                    dontr++;
            }
        }
        if(dontl == 1 || dontr == 1)
            e++;
        return e - s + 1;
    }
    else
    {
        ll worst = LLONG_MAX;
        for(int i = 0; i < N; i++)
        {
            worst = min(worst, (ll)(R[i] - L[i] + 1));
        }
        return worst;
    }
}
