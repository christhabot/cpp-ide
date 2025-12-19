#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<ll> vec;

int main() 
{
    ll amountq, amount;
    scanf("%lld", &amountq);
    while(amountq--) 
    {
        scanf("%lld", &amount);
        vec.resize(amount);
        for(ll i = 0; i < amount; i++) 
        {
            scanf("%lld", &vec[i]);
        }
    }
}