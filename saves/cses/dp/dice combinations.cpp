#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<ll> dp;
int target;

int main() 
{
    ll result;
    scanf("%d", &target);
    dp.assign(target+1, 0);
    dp[0] = 1;
    for(int i = 1; i <= target; i++)
    {
        for(int j = 1; j <= 6; j++)
        {
            if(i-j >= 0)
            {
                dp[i] += dp[i-j];
                dp[i] %= 1000000007;
            }
        }
    }
    printf("%lld", dp[target]);
}