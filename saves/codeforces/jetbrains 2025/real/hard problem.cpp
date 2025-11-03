#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<ll> vec;

int main() 
{
    ll amount, sum = 0;
    scanf("%lld", &amount);
    vec.resize(amount);
    for(ll i = 0; i < amount; i++)
    {
        scanf("%lld", &vec[i]);
        sum += vec[i];
    }
    for(ll i = 0; i < amount-2; i++) // first pass: move element to the right
    {
        if(vec[i]*2 >= vec[i+2])
        {
            sum -= vec[i+1];
            sum += vec[amount-1]*2;
            printf("%lld", sum);
            return 0;
        }
    }
    ll maxgap = 0;
    for(ll i = 1; i < amount; i++) // 2nd pass: find biggest gap thing
    {
        maxgap = max(maxgap, (vec[i-1] * 2) - vec[i]);
    }
    printf("%lld", sum+maxgap);
}