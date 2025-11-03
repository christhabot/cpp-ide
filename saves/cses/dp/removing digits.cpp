#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int number;
vector<ll> memo;

ll dp(int i)
{
    ll best = LLONG_MAX;
    if(i == 0) 
    {
        return 0;
    }
    if(i > number || i < 0) 
    {
        printf("huh?");
        return -1;
    }
    if(memo[i] != -1) return memo[i];
    string str = to_string(i);
    for(int l = 0; l < str.size(); l++)
    {
        if(str[l] != '0')
            best = min(best, dp(i-(str[l]-'0')));
    }
    return memo[i] = best+1;
}

int main() 
{
    scanf("%d", &number);
    memo.assign(number+1, -1);
    printf("%lld", dp(number));
}