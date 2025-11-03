#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<ll> coins;
vector<ll> memo;

ll limit;

ll dp(ll total)
{
    ll value = 0;
    if(total == limit) return 1;
    if(memo[total] != -1) return memo[total];
    for(int i = 0; i < coins.size(); i++)
    {
        if(total + coins[i] <= limit)
        {
            value += dp(total + coins[i]);
        }
    }
    return memo[total] = value % 1000000007;
}

int main() {
    int amount;
    ll temp;
    cin >> amount >> limit;
    memo.assign(limit, -1);
    for(int i = 0; i < amount; i++)
    {
        cin >> temp;
        coins.push_back(temp);
    }
    cout << dp(0) % 1000000007;
    return 0;
}