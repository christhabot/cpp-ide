#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
vector<ll> coins;
vector<vector<ll>> memo;
 
ll limit;
 
ll dp(ll total, ll last)
{
    ll value = 0;
    if(total == limit) return 1;
    if(memo[total][last + 1] != -1) return memo[total][last + 1];
    for(int i = 0; i < coins.size(); i++)
    {
        if((last == -1 || coins[i] >= coins[last]) && total + coins[i] <= limit)
        {
            value += dp(total + coins[i], i);
            value %= 1000000007;
        }
    }
    return memo[total][last+1] = value % 1000000007;
}
 
int main() {
    int amount;
    ll temp;
    cin >> amount >> limit;
    memo.assign(limit + 1, vector<ll>(amount+1, -1));
    for(int i = 0; i < amount; i++)
    {
        cin >> temp;
        coins.push_back(temp);
    }
    cout << dp(0, -1) % 1000000007;
    return 0;
}