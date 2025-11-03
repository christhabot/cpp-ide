#include "reactions.h"
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int reactions (int N, std::vector <int> D, std::vector <long long> T)
{
    ll best = LLONG_MIN;
    ll cur, curs;
    for(int i = 0; i < N; i++)
    {
        cur = 0;
        curs = 0;
        for(int j = i; j < N; j++)
        {
            cur += D[j];
            if(cur >= T[j])
            {
                curs++;
            }
        }
        if(curs >= best)
        {
            best = curs;
        }
    }
    return (int)best;
}
