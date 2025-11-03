#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

unordered_map<ll, ll> memo;

ll dp(ll i)
{
    if (memo.count(i)) 
    {
        return memo[i];
    }
    if(i % 2 == 0)
    {
        memo.insert( {i, dp(i/2)} );
    }
    else
    {
        memo.insert( {i, i} );
    }
    return memo[i];
}

vector<pair<ll,ll>> pieces;
vector<ll> prefix;

ll get_answer(ll i)
{
    return pieces[upper_bound(prefix.begin(), prefix.end(), i) - prefix.begin() - 1].second;
}

int main() {
    ll amount, amountQ, Q, piece, big = 0;
    ll amountP;
    ll temp;
    scanf("%lld", &amount);
    prefix.push_back(0);
    for(int i = 0; i < amount; i++)
    {
        scanf("%lld", &piece);
        temp = dp(piece);
        pieces.push_back({piece/temp, temp});
        prefix.push_back(prefix.back() + piece/temp);
    }
    scanf("%lld", &amountQ);
    for(int i = 0; i < amountQ; i++)
    {
        scanf("%lld", &Q);
        printf("%lld\n", get_answer(Q-1));
    }
    return 0;
}