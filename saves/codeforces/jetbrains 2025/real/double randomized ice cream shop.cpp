#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

unordered_set<ll> a, b;

int main() 
{
    ll amount, amounts, cur, both = 0;
    scanf("%lld %lld", &amount, &amounts);
    for(ll i = 1; i <= amount; i++)
    {
        a.insert(i);
        b.insert(i);
    }
    for(ll i = 0; i < amounts; i++)
    {
        scanf("%lld", &cur);
        a.erase(cur);
    }
    for(ll i = 0; i < amounts; i++)
    {
        scanf("%lld", &cur);
        b.erase(cur);
    }
    for(ll i = 1; i <= amount; i++)
    {
        if(a.count(i) && b.count(i))
        {
            both++;
        }
    }
    printf("%lld %lld", (amount-amounts)*(amount-amounts)-both, both);
}