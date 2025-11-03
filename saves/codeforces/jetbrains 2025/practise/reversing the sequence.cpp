#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<ll> vec;

int main() 
{
    ll amount;
    scanf("%lld", &amount);
    vec.resize(amount);
    for(ll i = 0; i < amount; i++)
    {
        scanf("%lld", &vec[i]);
    }
    for(ll i = amount-1; i >= 0; i--)
    {
        printf("%lld ", vec[i]);
    }
}