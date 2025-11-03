#include "grid.h"
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

long long max_profit(int N, int M, int C, std::vector<std::vector<int>> A)
{
    ll profit = 0;
    int pos = 0;
    int look = 1;
    while(true)
    {
        if(abs(A[0][pos]-A[0][look])-C >=0)
        {
            profit += abs(A[0][pos]-A[0][look])-C;
            pos = look;
            look = pos + 1;
            if(pos = M-1)
                return profit;
        }
        else
        {
            if(look = pos-1)
            {
                return profit + abs(A[0][M-1]-A[0][pos])-C;
            }
            look++;
        }
    }
}
